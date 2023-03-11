/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Windows/RXF_MainTask.cpp
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
        getInstance()->startDispatching();
        
        HANDLE mainThreadHandle = *getInstance()->getTaskHandle();
        
        WaitForSingleObject( mainThreadHandle, INFINITE );  
        
        CloseHandle( mainThreadHandle );  
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
	File Path	: ../Source/RTOS/Windows/RXF_MainTask.cpp
*********************************************************************/
