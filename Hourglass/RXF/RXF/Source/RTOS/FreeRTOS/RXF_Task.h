/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/FreeRTOS/RXF_Task.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Task_H
#define RXF_Task_H

#include <FreeRTOS.h>
#include <task.h>
#include "RXF_Types.h"
#include "RXF_Priority.h"
namespace RXF {
    class Task {
    public :
    
        // 
        // Type for the stack size.
        typedef std::uint32_t StackSize;
        
        // 
        // Enumeration of different states that a task can have.
        enum Status
        {
            INITIALIZED = 0,
            RUNNING = 1,
            TERMINATED = 2,
            DELETED = 3
        };
    
    private :
    
        // static callback function for RTOS task
        static void entryPoint(void* const task);
        
        // Satisfies requirement 139: Task - Execute after startDispatching
        // After startDispatching() is called a Task should start running the execute() operation.
        // 
        void createTask(void);
        
        // Satisfies requirement 100: Task - Deletion after Execution
        // When execute() returns, the Task shall delete itself.
        // 
        void deleteTask(void);
    
    public :
    
        // Satisfies requirement 3741: Task - Sleep
        // A Task shall sleep for given time in milli seconds.
        // 
        static void sleep(std::uint32_t const milliSeconds);
    
    protected :
    
        // Satisfies requirement 2847: Task - Wait for Signal
        // A Task shall provide a mechanism to wait for a signal.
        // 
        void waitForSignal(void);
    
    public :
    
        // Satisfies requirement 2847: Task - Wait for Signal
        // A Task shall provide a mechanism to wait for a signal.
        // 
        void setSignal(void);
        
        // Satisfies requirement 174: Task - Initialization
        // A Task shall be initialized with a given name, priority and stack size.
        // 
        Task(const RXF::char_t* const aName, Priority::Type const aPriority, StackSize const aStackSize);
        
        // Terminates and destroys a task.
        // Satisfies requirement 91: Task - Callable from Extern
        // A Task shall be able to be terminated and deleted from another Task context.
        // 
        virtual ~Task(void);
    
    private :
    
        // Satisfies requirement 100: Task - Deletion after Execution
        // When execute() returns, the Task shall delete itself.
        // 
        // Satisfies requirement 139: Task - Execute after startDispatching
        // After startDispatching() is called a Task should start running the execute() operation.
        // 
        void startExecute(void);
    
    protected :
    
        // Satisfies requirement 124: Task - Entrypoint
        // A realizing class of Task shall provide an execute() operation.
        // 
        virtual void execute(void) = 0;
    
    public :
    
        // Satisfies requirement 139: Task - Execute after startDispatching
        // After startDispatching() is called a Task should start running the execute() operation.
        // 
        // Satisfies requirement 251: Task - Wait for startDispatching
        // A Task shall not start running, until startDispatching() is called.
        // 
        void startTask(void);
        
        // Satisfies requirement 91: Task - Callable from Extern
        // A Task shall be able to be terminated and deleted from another Task context.
        // 
        // Satisfies requirement 98: Task - Termination and Deletion
        // A Task shall be able to terminate and delete itself.
        // 
        void endTask(void);
    
    protected :
    
        // Satisfies requirement 195: Task - Dispatching Status
        // A Task shall be able to provide information about its dispatching status.
        // 
        bool isRunning(void) const;
    
    public :
    
        // Returns the name of the task.
        inline const char_t* getName(void) const
        {
            return name;
        }
        
        ////    Attributes    ////
    
    private :
    
        // Name of the task.
        const char_t* name;
        
        // Priority of the task.
        const Priority::Type taskPriority;
        
        // Stack size of the task.
        const StackSize stackSize;
        
        // Represents the status of the task. See enumeration Status.
        Status status;
        
        TaskHandle_t taskHandle;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/FreeRTOS/RXF_Task.h
*********************************************************************/
