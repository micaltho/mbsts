/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/OORTX/RXF_MainTask.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_MainTask.h"
#include "RXF_Config.h"
#include "RXF_Tick.h"
namespace RXF {
    MainTask::MainTask(void) : RXF::Active( MAIN_TASK_QUEUE_SIZE, getQueueMemory() )
    {
    }
    
    void MainTask::start(void)
    {
        getInstance()->execute();
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
	File Path	: ../Source/RTOS/OORTX/RXF_MainTask.cpp
*********************************************************************/
