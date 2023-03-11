/*
 * $Id$     lpc17xx_iap.c
 * @file	lpc17xx_iap.c
 *
 * @brief	contains internal flash in-application-programming routines
 *
 * @version	1.0
 * @date		20.07.2015
 * @author Wuebbelmann
 */

#include <string.h>

#include "chip.h"
#include "lpc17xx_iap.h"

// entry address of IAP firmware
#define IAP_LOCATION 0x1FFF1FF1

// setting pointer function
typedef void (*IAP)(unsigned int [],unsigned int[]);

enum IAPCommands
{
	PrepareSectorForWrite  = 50,
	CopyRAMtoFlash         = 51,
	EraseSector            = 52,
	BlankCheckSector       = 53,
	ReadPartID             = 54,
	ReadBootCodeVersion    = 55,
	ReadDeviceSerialNumber = 58,
	Compare                = 56,
	ReinvokeISP            = 57
};

enum IAPStatusCodes
{
	CMD_SUCCESS = 0,
	INVALID_COMMAND,
	SRC_ADDR_ERROR,
	DST_ADDR_ERROR,
	SRC_ADDR_NOT_MAPPED,
	DST_ADDR_NOT_MAPPED,
	COUNT_ERROR,
	INVALID_SECTOR,
	SECTOR_NOT_BLANK,
	SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
	COMPARE_ERROR,
	BUSY
};

typedef struct _sectormap
{
   uint32_t   sectorNumber;
   uint32_t	  sectorSize;
   uint32_t	  startAddress;
   uint32_t	  endAddress;
} SectorMap;


#ifndef __cplusplus
#ifndef bool      // might be defined in stdbool.h,
typedef enum _bool {true = 1==1, false = !true} bool;
#endif
#endif


// local variables:
static unsigned int command[5];
static unsigned int output[5];
static IAP bsp_iap_entry;

static bool isInit = false;

#define MAXSECTORNUM 29
static const SectorMap sectorMap[] =
{
		{0,   4,   0X00000000,  0X00000FFF},
		{1,   4,   0X00001000,  0X00001FFF},
		{2,   4,   0X00002000,  0X00002FFF},
		{3,   4,   0X00003000,  0X00003FFF},
		{4,   4,   0X00004000,  0X00004FFF},
		{5,   4,   0X00005000,  0X00005FFF},
		{6,   4,   0X00006000,  0X00006FFF},
		{7,   4,   0X00007000,  0X00007FFF},
		{8,   4,   0x00008000,  0X00008FFF},
		{9,   4,   0x00009000,  0X00009FFF},
		{10,  4,   0x0000A000,  0X0000AFFF},
		{11,  4,   0x0000B000,  0X0000BFFF},
		{12,  4,   0x0000C000,  0X0000CFFF},
		{13,  4,   0x0000D000,  0X0000DFFF},
		{14,  4,   0x0000E000,  0X0000EFFF},
		{15,  4,   0x0000F000,  0X0000FFFF},
		{16, 32,   0x00010000,  0x00017FFF},
		{17, 32,   0x00018000,  0x0001FFFF},
		{18, 32,   0x00020000,  0x00027FFF},
		{19, 32,   0x00028000,  0x0002FFFF},
		{20, 32,   0x00030000,  0x00037FFF},
		{21, 32,   0x00038000,  0x0003FFFF},
		{22, 32,   0x00040000,  0x00047FFF},
		{23, 32,   0x00048000,  0x0004FFFF},
		{24, 32,   0x00050000,  0x00057FFF},
		{25, 32,   0x00058000,  0x0005FFFF},
		{26, 32,   0x00060000,  0x00067FFF},
		{27, 32,   0x00068000,  0x0006FFFF},
		{28, 32,   0x00070000,  0x00077FFF},
		{29, 32,   0x00078000,  0x0007FFFF},

};


// local functions
static bool iapInit()
{

	bsp_iap_entry=(IAP) IAP_LOCATION;

    command[0] = ReadDeviceSerialNumber;
    bsp_iap_entry (command, output);

	isInit  = true;
	return isInit;
}



static uint32_t getSectorFromAddress(void *addr)
{
   uint32_t address      = (uint32_t) addr;
   uint32_t sectorNumber = UINT32_MAX;
   uint_fast8_t i        = 0;

   for (i = 0; i < sizeof(sectorMap)/sizeof(SectorMap); ++i)
   {
	   if (sectorMap[i].startAddress <= address && sectorMap[i].endAddress >=  address)
	   {
		   sectorNumber = sectorMap[i].sectorNumber;
		   break;
	   }
   }
   return sectorNumber;
}


static IAPErrorCode checkParams(void *source, void * destination, uint32_t length)
{
	IAPErrorCode  xcode = FLASH_SUCCESS;
	uint32_t startSector = getSectorFromAddress(destination);
	uint32_t endSector   = getSectorFromAddress(destination + length);

	if (!isInit)
    {
    	iapInit();
    }

	// parameter check
	if ((uint32_t)destination & 0x3)  xcode = INVALID_DSTALIGNMENT;  // 8 Byte alignment
	if ((uint32_t)source      & 0x3)  xcode = INVALID_SRCALIGNMENT;  // 8 Byte alignment
	if (!length)                      xcode = INVALID_LENGTH;
    if (sectorMap[MAXSECTORNUM].endAddress < (uint32_t)destination + length)
    	                              xcode = INVALID_LENGTH;
	if (MAXSECTORNUM < startSector || MAXSECTORNUM < endSector)
		                              xcode =  INVALID_ADDRESS;
    return xcode;
}




static enum IAPStatusCodes prepareWrite(uint32_t *mDest, uint32_t length)
{
	uint32_t startSector = getSectorFromAddress(mDest);
	uint32_t endSector   = getSectorFromAddress(mDest + (length / sizeof(uint32_t)));

    command[0] = PrepareSectorForWrite;
    command[1] = startSector;
    command[2] = endSector;
    bsp_iap_entry (command, output);

    return output[0];
}


static enum IAPStatusCodes copyRAMtoFlash(void *mDest, void *mSrc, uint32_t numOfByte)
{
    command[0] = CopyRAMtoFlash;
    command[1] = (uint32_t)mDest;
    command[2] = (uint32_t)mSrc;
    command[3] = (uint32_t)numOfByte;
    command[4] = SystemCoreClock/1000;

    bsp_iap_entry (command, output);
    return output[0];
}

IAPErrorCode iap_write2Flash(void *source, void * destination, uint32_t length)
{
	IAPErrorCode xcode = FLASH_SUCCESS;

	enum IAPStatusCodes errorCode = CMD_SUCCESS;
	uint32_t *mSrc  = (uint32_t *)  source;
	uint32_t *mDest  = (uint32_t *) destination;
	uint32_t numOfByte = length;
	uint8_t buffer[256];

	// parameter check
	xcode = checkParams(source, destination, length);
	if (FLASH_SUCCESS != xcode)  return xcode;

	// copy Data in Flash:
    // start with unaligned block:
    if ( ((uint32_t)mDest & 0xFF) || (length < 256) )     // check for 256 Byte boundary
    {
    	uint8_t misaligment = ((uint32_t)mDest & 0xFF);
    	uint8_t dataToWrite = length > 256 - misaligment ? 256 - misaligment : length;

    	memcpy(buffer, mDest - misaligment / sizeof(uint32_t), misaligment);
    	memcpy(buffer+ misaligment, mSrc, dataToWrite);
    	if (dataToWrite < 256 - misaligment)
    	{
    		memset(buffer+ misaligment + dataToWrite, ~(0), 256 - misaligment - dataToWrite);
    	}

    	mSrc +=  dataToWrite / sizeof(uint32_t);
    	mDest = (uint32_t *)((uint32_t)mDest & ~0xFF);
    	numOfByte = 256;
    	length -= dataToWrite;

    	// prepare sectors for write operation
    	errorCode = prepareWrite(mDest,  numOfByte);
        if (CMD_SUCCESS != errorCode) return UNKNOWN_ERROR;

        // and write Data:
        errorCode = copyRAMtoFlash(mDest, buffer, 256);
        if (CMD_SUCCESS != errorCode) return WRITE_ERROR;

        // set destination to next page:
        mDest += 256/sizeof(uint32_t);
    }

    // copy aligned blocks:
    while (length)
    {
    	if (length >= 4096)
    	{
    		numOfByte = 4096;
    		length   -= 4096;
    	}
    	else if (length >= 1024)
    	{
    		numOfByte = 1024;
    		length   -= 1024;
    	}
    	else if (length >= 512)
        {
            numOfByte = 512;
        	length   -= 512;
        }
        else if (length >= 256)
        {
            numOfByte = 256;
            length   -= 256;
         }
         else
         {
        	 // no copy from src to destination possible.
        	 // buffer data and fill padding page bytes with 0XFF
        	 numOfByte = 256;
           	 memcpy(buffer, mSrc, length);
             memset(buffer + length, ~(0), 256 - length);
             mSrc = (uint32_t *)buffer;
        	 length    = 0;
         }

        // prepare sectors for write operation
    	errorCode = prepareWrite(mDest,  numOfByte);
        if (CMD_SUCCESS != errorCode) return UNKNOWN_ERROR;

        // and write Data:
        errorCode = copyRAMtoFlash(mDest, mSrc, numOfByte);
        if (CMD_SUCCESS != errorCode) return WRITE_ERROR;

        mDest += numOfByte / sizeof(uint32_t);
        mSrc  += numOfByte / sizeof(uint32_t);
    }
	return xcode;
}


IAPErrorCode iap_eraseFlash(void * destination, uint32_t length)
{
	IAPErrorCode xcode = FLASH_SUCCESS;
	enum IAPStatusCodes errorCode = CMD_SUCCESS;
	uint32_t *mDest  = (uint32_t *) destination;

	uint32_t startSector = getSectorFromAddress(mDest);
	uint32_t endSector   = getSectorFromAddress(mDest + (length / sizeof(uint32_t)));

	// parameter check
	xcode = checkParams(0, destination, length);
	if (FLASH_SUCCESS != xcode)  return xcode;

    // prepare sectors for erase operation
	errorCode = prepareWrite(mDest,  length);
    // erase command:
    command[0] = EraseSector;
    command[1] = startSector;
    command[2] = endSector;
    command[3] = SystemCoreClock/1000;

    bsp_iap_entry (command, output);
    errorCode = output[0];
    if (CMD_SUCCESS != errorCode) return ERASE_ERROR;

    return FLASH_SUCCESS;

}

uint32_t iap_getSegmentStartAddress(uint32_t segment)
{
	uint32_t address = ILLEGAL_ADDRESS;
	if (MAXSECTORNUM >= segment)
	{
		address = sectorMap[segment].startAddress;
	}
	return address;
}

uint32_t iap_getSegmentSize(uint32_t segment)
{
	uint32_t size = ILLEGAL_ADDRESS;
	if (MAXSECTORNUM >= segment)
	{
		size =sectorMap[segment].endAddress - sectorMap[segment].startAddress + 1;
	}
	return size;
}


