/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/CMSIS2/RXF_MainTask.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_MainTask.h"
#include "RXF_Config.h"
#include "RXF_Tick.h"
namespace RXF {
    void MainTask::start(void)
    {
        if( osKernelGetState() == osKernelInactive )
        {
        	const osStatus_t status = osKernelInitialize();
        	
        	if( osOK != status )
        	{
        		RXF::ErrorHandler::error( ERROR_MAIN_TASK_RTOS_INIT_FAILED, status, true );
        	}
        }
        
        // start dispatching of MainTask needs to have the kernel initialized before.
        getInstance()->startDispatching();
        
        
        if ( osKernelGetState() == osKernelReady )
        {
        	const osStatus_t status = osKernelStart();
        	
        	if( osOK != status )
        	{
        		RXF::ErrorHandler::error( ERROR_MAIN_TASK_RTOS_INIT_FAILED, status, true );
        	}
        }
    }
    
    MainTask::MainTask(void) : RXF::Active( "Main Task", MAIN_TASK_PRIORITY, MAIN_TASK_STACK_SIZE, MAIN_TASK_QUEUE_SIZE, getQueueMemory() )
    {
    }
    
    MainTask* MainTask::getInstance(void)
    {
        static MainTask mainTaskInstance;
        return &mainTaskInstance;
    }
    
    bool MainTask::initializeFramework(void)
    {
        Tick::init();
        return true;
    }
    
    Event** MainTask::getQueueMemory(void)
    {
        static Event* mainTaskQueueMemory[MAIN_TASK_QUEUE_SIZE];
        return mainTaskQueueMemory;
    }
}

/*********************************************************************
	File Path	: ../Source/RTOS/CMSIS2/RXF_MainTask.cpp
*********************************************************************/
