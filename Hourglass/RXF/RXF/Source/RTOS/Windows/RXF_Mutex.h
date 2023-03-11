/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Windows/RXF_Mutex.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Mutex_H
#define RXF_Mutex_H

#include "Windows.h"
namespace RXF {
    // The function of this class is to avoid race conditions by using concurrency control.
    // Two methods are available: mutex (for threads of different processes, slow) or criticalSection (just for threads of the same process, fast).
    // After creating an object of WST_MTX you can use a mutex with the two operations lock() and unlock().
    // A CriticalSection can be used with the operations  wst_enterCriticalSection() and wst_leaveCriticalSection():
    class Mutex {
    public :
    
        // Internal class of mutex needed for Rhapsody code generation compatibility.
        class OperationLock {
        public :
        
            // Satisfies requirement 2904: Mutex - Lock Operation
            // A Mutex shall be able to lock a user operation on entry.
            // 
            explicit OperationLock(Mutex& aMutex);
            
            // Satisfies requirement 2906: Mutex - Unlock Operation
            // A Mutex shall be able to unlock a user operation on exit automatically.
            // 
            ~OperationLock(void);
            
            ////    Attributes    ////
        
        private :
        
            Mutex& mutex;
        };
        
        // Satisfies requirement 2878: Mutex - Lock
        // A Mutex shall provide an operation to lock a RTOS mutex.
        // 
        void lock(void);
        
        // Satisfies requirement 2879: Mutex - Unlock
        // A Mutex shall provide an operation to unlock a RTOS mutex.
        // 
        void unlock(void);
        
        // Satisfies requirement 3549: Mutex - Initialization
        // A Mutex shall initialize a RTOS mutex on creation.
        // 
        Mutex(void);
        
        // Satisfies requirement 3582: Mutex - Destruction
        // A Mutex shall destroy a RTOS mutex on destruction.
        // 
        ~Mutex(void);
        
        ////    Attributes    ////
    
    private :
    
        HANDLE mutexHandle;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/Windows/RXF_Mutex.h
*********************************************************************/
