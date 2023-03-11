/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/CMSIS2/RXF_Mutex.cpp
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
        const osStatus_t status = osMutexAcquire( mutexHandle, osWaitForever );
        if ( osOK != status )
        {
        	ErrorHandler::error( ERROR_MUTEX_LOCK_FAILED, status , true);
        }
    }
    
    void Mutex::unlock(void)
    {
        const osStatus_t status = osMutexRelease( mutexHandle );
        if ( osOK != status )
        {
        	ErrorHandler::error( ERROR_MUTEX_UNLOCK_FAILED, status, true );
        }
    }
    
    Mutex::Mutex(void)
    {
        const osMutexAttr_t mutex_attr = {
          "",                         				// human readable mutex name
          osMutexRecursive | osMutexPrioInherit,    // attr_bits
          nullptr,                                     // memory for control block   
          0U                                      	// size for control block
          };
        
        mutexHandle = osMutexNew( &mutex_attr );
        
        if( nullptr == mutexHandle )
        {
        	ErrorHandler::error( ERROR_MUTEX_CREATE_FAILED, 0, true );
        }
    }
    
    Mutex::~Mutex(void)
    {
        const osStatus_t status = osMutexDelete( mutexHandle );
        mutexHandle = nullptr;
        if ( osOK != status )
        {
        	ErrorHandler::error( ERROR_MUTEX_DELETE_FAILED, status, true );
        }
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/CMSIS2/RXF_Mutex.cpp
*********************************************************************/
