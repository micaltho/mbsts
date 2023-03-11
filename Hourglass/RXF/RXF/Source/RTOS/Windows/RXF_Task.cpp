/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Windows/RXF_Task.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_ErrorHandler.h"
#include "RXF_Task.h"
namespace RXF {
    unsigned __stdcall Task::entryPoint(void * task)
    {
        static_cast<Task*>(task)->startExecute();
         
        return 0;
    }
    
    void Task::createTask(void)
    {
        event = CreateEventA(NULL, FALSE, FALSE, NULL);
        threadHandle = (HANDLE)_beginthreadex( nullptr, stackSize, &entryPoint, this, 0, &threadID );
        
        if ( nullptr == threadHandle || 0 == threadID )
        {
        	ErrorHandler::error( RXF::ERROR_TASK_CREATE_FAILED, errno, true);
        }    
        
        if ( !SetThreadPriority(threadHandle, taskPriority) )
        {
        	ErrorHandler::error( RXF::ERROR_TASK_CREATE_FAILED, GetLastError(), true );
        }
    }
    
    void Task::deleteTask(void)
    {
    }
    
    void Task::sleep(const std::uint32_t milliseconds)
    {
        Sleep(milliseconds);
    }
    
    void Task::suspend(void)
    {
        WaitForSingleObject(event, INFINITE);
    }
    
    void Task::resume(void)
    {
        SetEvent(event);
    }
    
    void Task::waitForSignal(void)
    {
        WaitForSingleObject(event, INFINITE);
    }
    
    void Task::setSignal(void)
    {
        SetEvent(event);
    }
    
    Task::Task(const RXF::char_t* const aName, Priority::Type const aPriority, Task::StackSize const aStackSize) : name(aName), taskPriority(aPriority), stackSize(aStackSize), status(INITIALIZED)
    {
    }
    
    Task::~Task(void)
    {
        if( ( RUNNING == status ) || ( TERMINATED == status ) )
        {
        	deleteTask();
        }
    }
    
    void Task::startExecute(void)
    {
        // wait for signal from startTask to make sure task handle is initialized correctly before execution starts
        waitForSignal();
        
        execute();
        
        status = DELETED;
        deleteTask();
    }
    
    void Task::startTask(void)
    {
        if( INITIALIZED == status )
        {
        	status = RUNNING;
        	createTask();
        	
        	setSignal();
        }
    }
    
    void Task::endTask(void)
    {
        if( RUNNING == status )
        {  
        	status = TERMINATED;
        
        	// set Signal to wake up execute
        	setSignal();
        }
    }
    
    bool Task::isRunning(void) const
    {
        return RUNNING == status;
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/Windows/RXF_Task.cpp
*********************************************************************/
