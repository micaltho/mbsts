/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/FreeRTOS/RXF_Task.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Task.h"
#include "RXF_ErrorHandler.h"
namespace RXF {
    /* @MISRA_5-2-8+5-2-9=OFF XD-0000: cast from pointer to pointer */
    void Task::entryPoint(void* const task)
    {
        static_cast<Task*>(task)->startExecute();
    }
    
    /* @MISRA_5-2-8+5-2-9=ON (end of XD-0000) */
    
    void Task::createTask(void)
    {
        BaseType_t errorStatus = xTaskCreate( &entryPoint, name, static_cast<uint16_t>( (stackSize + ( sizeof( StackType_t ) - 1U ) ) / sizeof( StackType_t ) ), this, taskPriority, &taskHandle );
        
        /* @MISRA_5-2-4=OFF XD-0000: C-style cast in FreeRTOS header */
        if( pdPASS != errorStatus )
        {
        	ErrorHandler::error( RXF::ERROR_TASK_CREATE_FAILED, errorStatus, true );
        } 
        /* @MISRA_5-2-4=ON (end of XD-0000) */
    }
    
    void Task::deleteTask(void)
    {
        vTaskDelete( taskHandle );
    }
    
    void Task::sleep(std::uint32_t const milliSeconds)
    {
        /* @MISRA_5-2-4=OFF XD-0000: C-style cast */
        vTaskDelay( milliSeconds / portTICK_PERIOD_MS );       
        /* @MISRA_5-2-4=ON (end of XD-0000) */
    }
    
    void Task::waitForSignal(void)
    {
        /* @MISRA_5-2-4=OFF XD-0000: C-style cast in FreeRTOS header */
        (void) ulTaskNotifyTake( pdFALSE, portMAX_DELAY );    
        /* @MISRA_5-2-4=ON (end of XD-0000) */
    }
    
    void Task::setSignal(void)
    {
        /* @MISRA_5-2-4=OFF XD-0000: C-style cast in FreeRTOS header */
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        /* @MISRA_5-2-4=ON (end of XD-0000) */
        
        /* Notify the task that the transmission is complete. */
        vTaskNotifyGiveFromISR( taskHandle, &xHigherPriorityTaskWoken );
        /*
        xTaskNotifyFromISR( taskHandle,
                            0,
                            eNoAction,
                            &xHigherPriorityTaskWoken );
        */
        
        /* If xHigherPriorityTaskWoken is now set to pdTRUE then a context switch
        should be performed to ensure the interrupt returns directly to the highest
        priority task.  The macro used for this purpose is dependent on the port in
        use and may be called portEND_SWITCHING_ISR(). */
        /* @MISRA_5-2-7+5-2-8,2-13-3,5-2-4,6-2-3=OFF XD-0000: Suppress MISRA deviations inside portYIELD_FROM_ISR macro. */
        portYIELD_FROM_ISR( xHigherPriorityTaskWoken );  
        /* @MISRA_5-2-7+5-2-8,2-13-3,5-2-4,6-2-3=ON (end of XD-0000) */
    }
    
    Task::Task(const RXF::char_t* const aName, Priority::Type const aPriority, Task::StackSize const aStackSize) : name(aName), taskPriority(aPriority), stackSize(aStackSize), status(INITIALIZED), taskHandle(nullptr)
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
	File Path	: ../Source/RTOS/FreeRTOS/RXF_Task.cpp
*********************************************************************/
