/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/AUTOSAR/RXF_Task.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/
 
#include <sys/resource.h>

#include <errno.h>
#include <signal.h>
#include "RXF_Task.h"
#include "RXF_ErrorHandler.h"
namespace RXF {
    void * Task::entryPoint(void * const task)
    {
        /* @MISRA_5-2-8+5-2-9=OFF XD-0000: Cast from pointer to pointer to access the this ptr from the Task class. */
        Task * myTask = static_cast<Task*>(task);
        /* @MISRA_5-2-8+5-2-9=ON (end of XD-0000) */
        int_t errorStatus = pthread_setname_np( myTask->taskHandle, myTask->name);
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_TASK_CREATE_FAILED, errorStatus, true );
        }
        myTask->startExecute();
        
        return nullptr;
    }
    
    void Task::createTask(void)
    {
        int_t errorStatus = 0;
        
        // Initialise suspend signal
        (void) signal( SIGUSR1, &suspendHandler );
        
        // Initialize segnalSemaphore
        errorStatus = ( 0 != errorStatus ) ? errorStatus : sem_init(&signalSemaphore, 0, 0);
        
        pthread_attr_t attr;
        struct sched_param param;
        param.__sched_priority = taskPriority;
        	
        int schedulingPolicy = SCHED_OTHER;
        
        // set scheduling Policy to SCHED_FIFO if priority is not 0 and priority is in limits
        if( 0 != taskPriority)
        {
        	struct rlimit limits;
        	getrlimit(RLIMIT_RTPRIO,&limits);
        
        	//printf("Priority limits: soft=%lld; hard=%lld\n", (long long) limits.rlim_cur, (long long) limits.rlim_max);
        	
        	// if priority exeeds limit, use default priority 0
        	if( taskPriority > limits.rlim_cur )
        	{
        		param.__sched_priority = 0;
        	}
        	else
        	{	
        		schedulingPolicy = SCHED_FIFO;
        	}
        
        }
        
        errorStatus = ( 0 != errorStatus ) ? errorStatus : pthread_attr_init(&attr);
        errorStatus = ( 0 != errorStatus ) ? errorStatus : pthread_attr_setstacksize( &attr, PTHREAD_STACK_MIN + static_cast<size_t>(stackSize) );
        errorStatus = ( 0 != errorStatus ) ? errorStatus : pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
        errorStatus = ( 0 != errorStatus ) ? errorStatus : pthread_attr_setinheritsched( &attr, PTHREAD_EXPLICIT_SCHED );
        errorStatus = ( 0 != errorStatus ) ? errorStatus : pthread_attr_setschedpolicy( &attr, schedulingPolicy );
        errorStatus = ( 0 != errorStatus ) ? errorStatus : pthread_attr_setschedparam( &attr, &param );
        
        /* @MISRA_5-2-8+5-2-9=OFF XD-0000: Cast from pointer to pointer to provide the this ptr to the task. */
        errorStatus = ( 0 != errorStatus ) ? errorStatus : pthread_create( &taskHandle, &attr, &entryPoint, static_cast<void*>(this) );
        /* @MISRA_5-2-8+5-2-9=ON (end of XD-0000) */
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_TASK_CREATE_FAILED, errorStatus, true );
        }
    }
    
    void Task::deleteTask(void) const
    {
        int_t errorStatus = pthread_cancel( taskHandle );
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_TASK_DELETE_FAILED, errno, true );
        }
    }
    
    void Task::sleep(const std::uint32_t milliSeconds)
    {
        int32_t time_ns = static_cast<int32_t>( milliSeconds ) * 1000 * 1000 ;
        struct timespec sleeptime = { 0, time_ns };
        static_cast<void>( nanosleep(&sleeptime, nullptr ) );
    }
    
    void Task::suspend(void) const
    {
        int_t errorStatus = pthread_kill( taskHandle, static_cast<int_t>(SIGUSR1) );
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_TASK_SUSPEND_FAILED, errno, true );
        }
    }
    
    void Task::suspendHandler(const int_t)
    {
        // Suspend calling thread and wait for signal SIGUSR2
        int_t errorStatus = sigpause( SIGUSR2 );
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_TASK_SUSPEND_FAILED, errno, true );
        }
    }
    
    void Task::resume(void) const
    {
        // Send signal SIGUSR1 to resume suspended thread
        int_t errorStatus = pthread_kill( taskHandle, SIGUSR2 );
        
        if( 0 != errorStatus )
        {
        	ErrorHandler::error( ERROR_TASK_RESUME_FAILED, errno, true );
        }
    }
    
    void Task::waitForSignal(void)
    {
        sem_wait( &signalSemaphore );
    }
    
    void Task::setSignal(void)
    {
        sem_post( &signalSemaphore );
    }
    
    Task::Task(const RXF::char_t* const aName, Priority::Type const aPriority, Task::StackSize const aStackSize) : name(aName), taskPriority(aPriority), stackSize(aStackSize), status(INITIALIZED), taskHandle(0)
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
	File Path	: ../Source/RTOS/AUTOSAR/RXF_Task.cpp
*********************************************************************/
