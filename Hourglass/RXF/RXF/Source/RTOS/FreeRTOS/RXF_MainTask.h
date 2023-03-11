/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/FreeRTOS/RXF_MainTask.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MainTask_H
#define RXF_MainTask_H

#include "RXF_Active.h"
namespace RXF {
    class MainTask : public Active {
    public :
    
        // Satisfies requirement 2899: MainTask - Start Once
        // The RTOS shall only be started once by the MainTask.
        // 
        // Satisfies requirement 2872: MainTask - Start Execution
        // The MainTask shall provide an operation to start its execution.
        // 
        static void start(void);
    
    private :
    
        // Satisfies requirement 2871: MainTask - Single Instance
        // There shall only exist one MainTask instance.
        // 
        MainTask(void);
    
    public :
    
        // Satisfies requirement 2871: MainTask - Single Instance
        // There shall only exist one MainTask instance.
        // 
        static MainTask* getInstance(void);
    
    private :
    
        // MainTask inherits from Active and this execute overrides the execute of Active.
        // After calling initializeFramework(), this operation executes generated initialization code and starts processing of the main event handling loop by calling the execute() operation of the base class Active.
        // 
        // The Framework Code only contains the specification for this operation, the implementation is generated from the executable component of a user model and is located in Main<ComponentName>.c
        virtual void execute(void);
        
        // As the Kernel has to be started before calling Timer::init(), this operation is called frome from MainTask::execute() context.
        static bool initializeFramework(void);
        
        // This operation returns a pointer to an array of  pointer to events. This memory is used by the message queue to store events.
        static Event** getQueueMemory(void);
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/FreeRTOS/RXF_MainTask.h
*********************************************************************/
