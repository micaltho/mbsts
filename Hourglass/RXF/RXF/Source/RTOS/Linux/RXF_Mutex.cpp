/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Linux/RXF_Mutex.cpp
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
        int32_t errorStatus = pthread_mutex_lock( &mutexHandle );
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_MUTEX_LOCK_FAILED, errorStatus, true );
        }
    }
    
    void Mutex::unlock(void)
    {
        int32_t errorStatus = pthread_mutex_unlock( &mutexHandle );
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_MUTEX_UNLOCK_FAILED, errorStatus, true );
        }
    }
    
    Mutex::Mutex(void)
    {
        int32_t errorStatus = pthread_mutex_init( &mutexHandle, nullptr );
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_MUTEX_CREATE_FAILED, 0, true );
        }
    }
    
    Mutex::~Mutex(void)
    {
        int32_t errorStatus;
        errorStatus = pthread_mutex_destroy( &mutexHandle );
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_MUTEX_DELETE_FAILED, errorStatus, true );
        }
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/Linux/RXF_Mutex.cpp
*********************************************************************/
