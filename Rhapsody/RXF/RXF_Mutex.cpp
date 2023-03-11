/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/FreeRTOS/RXF_Mutex.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Mutex.h"
#include "RXF_ErrorHandler.h"
namespace RXF {
    Mutex::OperationLock::OperationLock(Mutex& aMutex) : mutex(aMutex)
    {
        mutex.lock();
    }
    
    Mutex::OperationLock::~OperationLock(void)
    {
        mutex.unlock();
    }
    
    void Mutex::lock(void)
    {
        /* @MISRA_5-2-8+5-2-9,4-10-2,5-2-4=OFF XD-0000: cast from pointer to pointer, implizit conversion from 0 to pointer, C-style cast */
        BaseType_t status = xSemaphoreTake( mutexHandle, portMAX_DELAY ); 
        /* @MISRA_5-2-8+5-2-9,4-10-2,5-2-4=ON (end of XD-0000) */
        /* @MISRA_5-2-4=OFF XD-0000: C-style cast */
        if ( pdTRUE != status )
        {
        	ErrorHandler::error( ERROR_MUTEX_LOCK_FAILED, status, true );
        }   
        /* @MISRA_5-2-4=ON (end of XD-0000) */ 
        
    }
    
    void Mutex::unlock(void)
    {
        /* @MISRA_5-2-8+5-2-9,4-10-2,5-2-4=OFF XD-0000: cast from pointer to pointer, implizit conversion from 0 to pointer, C-style cast */
        BaseType_t status = xSemaphoreGive( mutexHandle );
        /* @MISRA_5-2-8+5-2-9,4-10-2,5-2-4=ON (end of XD-0000) */
        /* @MISRA_5-2-4=OFF XD-0000: C-style cast */
        if ( pdTRUE != status )
        {
        	ErrorHandler::error( ERROR_MUTEX_UNLOCK_FAILED, status, true );
        }
        /* @MISRA_5-2-4=ON (end of XD-0000) */
    }
    
    Mutex::Mutex(void)
    {
        /* @MISRA_5-2-4=OFF XD-0000: C-style cast */
        mutexHandle = xSemaphoreCreateMutex();
        /* @MISRA_5-2-4=ON (end of XD-0000) */
        if( nullptr == mutexHandle )
        {
        	ErrorHandler::error( ERROR_MUTEX_CREATE_FAILED, 0, true );
        }
    }
    
    Mutex::~Mutex(void)
    {
        /* @MISRA_5-2-8+5-2-9,5-2-4=OFF XD-0000: cast from pointer to pointer, C-style cast */
        vSemaphoreDelete(mutexHandle);  
        /* @MISRA_5-2-8+5-2-9,5-2-4=ON (end of XD-0000) */    
        mutexHandle = nullptr;
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/FreeRTOS/RXF_Mutex.cpp
*********************************************************************/
