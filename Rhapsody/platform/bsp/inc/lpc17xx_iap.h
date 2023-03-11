/*
 * $Id$     lpc17xx_iap.h
 * @file	lpc17xx_iap.h
 *
 * @brief	contains internal flash in-application-programming routines
 *
 * @version	1.0
 * @date		20.07.2015
 * @author Wuebbelmann
 */
#ifndef LIB_MCU_INC_LPC17XX_IAP_H_
#define LIB_MCU_INC_LPC17XX_IAP_H_

#include <stdint.h>


typedef enum
{
	FLASH_SUCCESS,
	INVALID_ADDRESS,
	INVALID_LENGTH,
	INVALID_SRCALIGNMENT,
	INVALID_DSTALIGNMENT,
	WRITE_ERROR,
	ERASE_ERROR,
	UNKNOWN_ERROR
}  IAPErrorCode;


#define ERASECHAR   0xFF
#define ILLEGAL_ADDRESS UINT32_MAX


#ifdef __cplusplus
extern "C"
{
#endif
IAPErrorCode iap_write2Flash(void *source, void * destination, uint32_t length);
IAPErrorCode iap_eraseFlash (void *destination, uint32_t length);
uint32_t     iap_getSegmentStartAddress(uint32_t segment);
uint32_t     iap_getSegmentSize(uint32_t segment);

#ifdef __cplusplus
}    // end extern "c"
#endif

#endif /* LIB_MCU_INC_LPC17XX_IAP_H_ */
