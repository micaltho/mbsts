/******************************************************************
 *****                                                        *****
 *****  Name: errorlog.c                                      *****
 *****  Ver.: 1.0                                             *****
 *****  Date: 2007-04-13                                      *****
 *****  Auth: Juergen. Wuebbelmann                            *****
 *****        FH Osnabrueck                                   *****
 *****        University of applied sciences                  *****
 *****        Germany                                         *****
 *****  Func: Logs ErrorMessages                              *****
 *****                                                        *****
 ******************************************************************/

#include <stdio.h>
#include <string.h>
#include "stdint.h"

#include "errorlog.h"

#include "lpc17xx_iap.h"

#include "chip.h"

#ifndef ISTIMEAVAILABLE
#define ISTIMEAVAILABLE
#endif

#ifdef ISTIMEAVAILABLE
// Real Time Clock
//#include "lpc17xx_iap.h"
#endif

#define isSuccess(x) (NoError == (x))

#define MAGICNUMBER 0xA55A

// where to store data? sectors must not be used otherwise
#define FIRSTLOGSECTOR  26
#define SECONDLOGSECTOR 27

#ifdef __cplusplus
namespace Platform {
namespace BSP {
#endif
/*------------ type definitions --------------*/
typedef struct timeStamp_t     /// Timestamp stored for every logging entry if RTC is available
{
  union   // assure 32 bit alignment!
  {
	struct {
      uint8_t  seconds;         ///< second  (0...59)
      uint8_t  minutes;         ///< minute  (0...59)
      uint8_t  hours;           ///< hour    (0...23)
      uint8_t  dayOfMonth;      ///< day     (1...31)
      uint8_t  month;           ///< month   (1...12)
      uint16_t year;            ///< year    (0 ... xxxx)
	};
	uint32_t dummy[2];          ///< dummy to assure 32 bit alignment
  };
} TimeStamp_t;


typedef struct errorLog_t   /// Structure which is stored in flash for logging purpose
{
  uint16_t    magicNumber;            ///< magic number, check for valid entry
  char        filename[20];           ///< file from which logging was called
  uint16_t    lineNo;                 ///< line number from which logging was called
  TimeStamp_t timeStamp;              ///< \ref TimeStamp_t time of logging
  Error_e     errorReason;            ///< \ref Error_e reason, stored as number
} ErrorLog_t;

typedef struct flashSegHeader_t 
{
  uint32_t magicNumber;
  char     segName[10];
} FlashSegHeader_t;


/*------ Variables -------------------------------*/
static const FlashSegHeader_t logHeader =
{
  0xA5A5A5A5,
  "ErrorLog"
}; 

static const uint32_t firstSector  = FIRSTLOGSECTOR;
static const uint32_t secondSector = SECONDLOGSECTOR;
static       uint32_t segmentSize  = 0;
static       uint32_t activeSector = FIRSTLOGSECTOR;


static bool     isInit       = false;
static uint32_t writeAddress = 0;

/*------ Function declaration---------------------*/
static void     printElement(uint16_t number, ErrorLog_t * slot);
static void     initErrorLog(void);
static bool     isHeader(uint32_t segAddress);
static uint32_t getFreeSlotAddress(uint32_t segStartAdresse);
static uint32_t formatLogSeg(uint32_t sector);
static void     updateWriteAddress(void);

/*------ Function implementation ------------------*/
static void printElement(uint16_t number, ErrorLog_t  * slot)
{
   ErrorLog_t localSlot;

   memcpy(&localSlot, slot, sizeof(ErrorLog_t));
   printf("%5d  ",    number);
   printf("%5d     ", localSlot.errorReason);
   printf("%02d:%02d:%02d %02d.%02d.%04d ",
		   localSlot.timeStamp.hours,
		   localSlot.timeStamp.minutes,
		   localSlot.timeStamp.seconds,
		   localSlot.timeStamp.dayOfMonth,
		   localSlot.timeStamp.month,
		   localSlot.timeStamp.year);
   printf("%9d   ",   localSlot.lineNo);
   printf("%10s\n",   localSlot.filename);
}


static bool isHeader(uint32_t segAddress)
{
  /* check if Segments starts with valid header: */
  bool isHeader = true;

  FlashSegHeader_t * header = (FlashSegHeader_t  *) segAddress;

  if (header->magicNumber != logHeader.magicNumber)
  {
    isHeader = false;
  }

  if (memcmp(header->segName,
             logHeader.segName,
             strlen(logHeader.segName)))
  {
    isHeader = false;
  }
  return isHeader;
}


static uint32_t formatLogSeg(uint32_t sector)
{
  uint32_t  slotAddress = 0;
  Error_e   xcode       = NoError;

  uint32_t  segStartAdresse = iap_getSegmentStartAddress(sector);
  if (ILLEGAL_ADDRESS == segStartAdresse) xcode = RangeError;

  if (isSuccess(xcode))
  {
     if (FLASH_SUCCESS != iap_eraseFlash ((void *)segStartAdresse, 1)) xcode = DataError;
  }

  if (isSuccess(xcode))
  {
      if (FLASH_SUCCESS != iap_write2Flash((uint32_t  *)&logHeader,
                                           (uint32_t  *)segStartAdresse,
                                            sizeof(logHeader)))
          xcode = DataError;
  }
  if (isSuccess(xcode))
  {
    slotAddress = segStartAdresse + sizeof(logHeader);
  }
  else
  {
    slotAddress = 0;
  }
  activeSector = sector;
  return slotAddress;
}


static void updateWriteAddress(void)
{
  uint32_t mask               = segmentSize -1;
  uint32_t addressCheck       = writeAddress & mask;
  uint32_t sectorStartAddress = 0;


  if (isInit)
  {
    if (addressCheck + sizeof(ErrorLog_t) >= segmentSize)
    {
      /* must format new sector */
      /* get address of first sector and check if we are into it: */
      sectorStartAddress = iap_getSegmentStartAddress(firstSector);
      if ( (writeAddress & sectorStartAddress) == sectorStartAddress )
      {
        /* now we are in first sector, change to second: */
        writeAddress = formatLogSeg(secondSector);
      }
      else
      {
        /* now we are in second sector, change to first: */
        writeAddress = formatLogSeg(firstSector);
      }
    }
    else
    {
      writeAddress += sizeof(ErrorLog_t);
    }
  }
}

static uint32_t getFreeSlotAddress(uint32_t segStartAdresse)
{
  uint32_t slotAddress    = 0;
  uint32_t i              = 0;
  ErrorLog_t *  slot      = 0;

  if (isHeader(segStartAdresse))
  {
     slotAddress = segStartAdresse + sizeof(FlashSegHeader_t);
     slot = (ErrorLog_t *) slotAddress;
     while (MAGICNUMBER == slot->magicNumber)
     {
       slot += 1;
       if (slot >= (ErrorLog_t *)(segStartAdresse + segmentSize))
       {
         slotAddress = 0;
         break;
       }
     }
     if (0 != slotAddress)
     {
       /* check if Flash is empty from here on. */
       for (i = (uint32_t)slot; i < segStartAdresse + segmentSize; i++)
       {
          if ((char)ERASECHAR != *((char *)i))
          {
            slotAddress = 0;
            break;
          }
       }
     }

     if (0 != slotAddress)
     {
       slotAddress = (uint32_t)slot;
     }
  }
  return slotAddress;
}


static void initErrorLog(void)
{
  uint32_t nextSlotAdressSeg0  = 0;
  uint32_t nextSlotAdressSeg1  = 0;
  uint32_t sectorStartaddress0 = 0;
  uint32_t sectorStartaddress1 = 0;

  /* assume all sectors have equal size */
  segmentSize = iap_getSegmentSize(firstSector);
  
  sectorStartaddress0 = iap_getSegmentStartAddress(firstSector);
  nextSlotAdressSeg0  = getFreeSlotAddress(sectorStartaddress0);
  sectorStartaddress1 = iap_getSegmentStartAddress(secondSector);
  nextSlotAdressSeg1  = getFreeSlotAddress(sectorStartaddress1);


  /* check whether Flash Segments are used: */
  if (0 == nextSlotAdressSeg0 && 0 == nextSlotAdressSeg1)
  {
    /* format and use segment 0 */
   writeAddress = formatLogSeg(firstSector);
  }
  else if (0 == nextSlotAdressSeg1)
  {
    /* use segment 0. */
    writeAddress = nextSlotAdressSeg0;
  }
  else 
  {
    /* use segment 1 */
    writeAddress = nextSlotAdressSeg1;
  }

  if (ILLEGAL_ADDRESS != segmentSize && 0 != writeAddress)
  {
    isInit = true;
  }

}


void createErrorLog(Error_e reason, const char *file, uint16_t line)
{ 
  ErrorLog_t logStructure;
  char *pathDel;
#ifdef ISTIMEAVAILABLE
  RTC_TIME_T time;
  Chip_RTC_GetFullTime(LPC_RTC, &time);
#endif
  
  if (!isInit)
  {
    initErrorLog();
  }
  if (isInit) /* if initialisation was successful */
  {
    logStructure.magicNumber = MAGICNUMBER;
    logStructure.errorReason = reason;
    logStructure.lineNo      = line;
#ifdef ISTIMEAVAILABLE
    logStructure.timeStamp.seconds    = (uint8_t) time.time[RTC_TIMETYPE_SECOND];
    logStructure.timeStamp.minutes    = (uint8_t) time.time[RTC_TIMETYPE_MINUTE];
    logStructure.timeStamp.hours      = (uint8_t) time.time[RTC_TIMETYPE_HOUR];
    logStructure.timeStamp.dayOfMonth = (uint8_t) time.time[RTC_TIMETYPE_DAYOFMONTH];
    logStructure.timeStamp.month      = (uint8_t) time.time[RTC_TIMETYPE_MONTH];
    logStructure.timeStamp.year       = (uint16_t)time.time[RTC_TIMETYPE_YEAR];
#else
    logStructure.timeStamp.seconds    = 0;
    logStructure.timeStamp.minutes    = 0;
    logStructure.timeStamp.hours      = 0;
    logStructure.timeStamp.dayOfMonth = 0;
    logStructure.timeStamp.month      = 0;
    logStructure.timeStamp.year       = 0;
#endif
    /* just take the basename of file */
    pathDel =  strrchr(file, '/');
    if (NULL != pathDel)
    {
      file = pathDel + 1;
    }
    strncpy(logStructure.filename, file, sizeof(logStructure.filename));

    iap_write2Flash((void  *)&logStructure,
                    (void  *)writeAddress,
                     sizeof(ErrorLog_t));
 
    updateWriteAddress();
  }
}


void printErrorLog()
{
   uint32_t   passiveSector ;
   uint32_t   readAddress = 0;
   /* @NULL@ */
   ErrorLog_t *  slot = 0;
   uint16_t         i    = 0;

  if (!isInit)
  {
    initErrorLog();
  }

  printf("\nNo.     Reason:  TimeStamp:                Line:  File:\n");
  printf("=======================================================\n");

  passiveSector = (activeSector == firstSector ? secondSector: firstSector);
  readAddress = iap_getSegmentStartAddress(passiveSector);
  if (isHeader(readAddress))
  {
     readAddress += sizeof(FlashSegHeader_t);
     slot = (ErrorLog_t *) readAddress;
     while (MAGICNUMBER == slot->magicNumber)
     {
       printElement(i++, slot++);
     }
  }

  readAddress = iap_getSegmentStartAddress(activeSector);
  if (isHeader(readAddress))
  {
    readAddress += sizeof(FlashSegHeader_t);
    slot = (ErrorLog_t *) readAddress;
    while (MAGICNUMBER == slot->magicNumber)
    {
      printElement(i++, slot++);
    }
  }
}

#ifdef __cplusplus
}      //namespace BSP
}      //namespace Platform
#endif

