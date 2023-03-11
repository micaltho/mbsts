/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/CMSIS2/RXF_Task.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_ErrorHandler.h"
#include "RXF_Task.h"
namespace RXF {
    void Task::entryPoint(void* const task)
    {
        /* @MISRA_5-2-8=OFF ID-0101: Cast from pointer to pointer required to bridge RTOS API to RXF interface. */
        static_cast<Task *>(task)->startExecute();
        /* @MISRA_5-2-8=ON */
    }
    
    void Task::createTask(void)
    {
        taskAttr.name = name;
        taskAttr.stack_size = stackSize;
        taskAttr.priority = taskPriority;
        
        taskHandle = osThreadNew( &entryPoint, this, &taskAttr);
        
        if( nullptr == taskHandle )
        {
        	ErrorHandler::error( ERROR_TASK_CREATE_FAILED, 0, true);
        }
    }
    
    void Task::deleteTask(void)
    {
        // This os call can not return a failure, because all failure cases are excluded by review.
        const osStatus_t errorStatus = osThreadTerminate( taskHandle );
        
        ErrorHandler::error( ERROR_TASK_DELETE_FAILED, errorStatus, true);
    }
    
    /* @MISRA_0-1-10=OFF ID-0008: Needed by the monitor as interface for the UML Target Debugger and as wrapper operation for the user. */
    void Task::sleep(std::uint32_t const milliSeconds)
    {
        (void) osDelay( milliSeconds );
    }
    
    /* @MISRA_0-1-10=ON (end of ID-0008) */
    
    void Task::waitForSignal(void)
    {
        const std::uint32_t flagsOrStatus = osThreadFlagsWait( 0x0001U, osFlagsWaitAny, osWaitForever );
        
        // osThreadFlagsWait returns thread flags before clearing or error code if highest bit set.
        
        if( ( flagsOrStatus & 0x80000000U ) > 0U) // highest bit indicates error
        {
        	ErrorHandler::error( ERROR_TASK_SUSPEND_FAILED, static_cast<std::int32_t>(flagsOrStatus), true );
        }
    }
    
    void Task::setSignal(void)
    {
        const std::uint32_t flagsOrStatus = osThreadFlagsSet(taskHandle, 0x0001U);
        
        // osThreadFlagsSet returns thread flags after setting or error code if highest bit set.
        
        if( ( flagsOrStatus & 0x80000000U ) > 0U) // highest bit indicates error
        {
        	ErrorHandler::error( ERROR_TASK_RESUME_FAILED, static_cast<std::int32_t>(flagsOrStatus), true );
        }
    }
    
    Task::Task(const RXF::char_t* const aName, Priority::Type const aPriority, Task::StackSize const aStackSize) : name(aName), taskPriority(aPriority), stackSize(aStackSize), status(INITIALIZED), taskHandle(nullptr), taskAttr( )
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
	File Path	: ../Source/RTOS/CMSIS2/RXF_Task.cpp
*********************************************************************/
