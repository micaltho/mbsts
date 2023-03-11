/**
 *  \file      errorlog.h
 *  \brief     Implements C based errorlog.
 *  \details   Errors are stored persistent in internal flash memory.\n
 *             On request, stored errors are printed to stdout.\n
 *             The errorlog might be used in C++ or C projects.\n
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      29.09.2015
 *  \pre
 *  \copyright HS Osnabrueck
 */

#ifndef __ERRORLOG_H__
#define __ERRORLOG_H__

#ifdef __cplusplus
namespace Platform {
namespace BSP {
#endif

/* defines:  */
typedef enum error_e  /// possible error reasons, must be extended if more reasons are needed
{
  NoError = 0,          ///< no error
  UnspecificError,      ///< unspecific error
  TypeError,            ///< data type error
  ProtocolError,        ///< protocol error
  DataError,            ///< invalid data
  RangeError,           ///< data or parameter out of range

  /* flash Errors  */
  IllegalDevice,        ///<  illegal HW device discovered
  TimingError,          ///<  HW access timed out

  /* OS Error Codes */
  CreateError,          ///< Error creating Tasks
  OutOfStackError,      ///< stack Error
  IllegalMboxError,     ///< mailbox error
  SendMessageError,     ///< message error
  TimeOutWarning,       ///< Warning, RTOS timed out

  NumberOfErrors
} Error_e;



#define eventLog(reason) createErrorLog((reason), __FILE__, __LINE__) ///< calls \ref createErrorLog function, passes \ref error_e

/*  public functions: */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * writes event to flash.
 * \warning must never be called directly by user, use \ref eventLog macro!\n
 *          Macro passes file name and line in file to function.
 * @param [in] reason  \ref error_e reason to store in flash
 * @param [in] file    \ref eventLog passes file name
 * @param [in] line    \ref eventLog passes line number
 */
extern void createErrorLog(Error_e reason, const char *file, uint16_t line);
/**
 * prints error history from flash to stdout.
 */
extern void printErrorLog();

#ifdef __cplusplus
}    // extern "C"
}    //namespace BSP
}    //namespace Platform
#endif

#endif
