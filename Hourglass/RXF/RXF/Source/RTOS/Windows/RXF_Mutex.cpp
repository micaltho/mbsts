/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Windows/RXF_Mutex.cpp
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
        WaitForSingleObject( mutexHandle, INFINITE );
    }
    
    void Mutex::unlock(void)
    {
        ReleaseMutex( mutexHandle );
    }
    
    Mutex::Mutex(void) : mutexHandle(nullptr)
    {
        mutexHandle = CreateMutex( nullptr, FALSE, nullptr );
        
        if ( mutexHandle == nullptr )
        {
        	ErrorHandler::error( ERROR_MUTEX_CREATE_FAILED, GetLastError(),true );
        }
    }
    
    Mutex::~Mutex(void)
    {
        CloseHandle( mutexHandle );
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/Windows/RXF_Mutex.cpp
*********************************************************************/
