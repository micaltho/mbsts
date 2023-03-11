/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/CMSIS2/RXF_Mutex.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Mutex_H
#define RXF_Mutex_H

#include <cmsis_os2.h>
namespace RXF {
    // CMIS2 RTOS wrapper for Mutex.
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
    
        // CMSIS2 RTOS mutex handle id.
        osMutexId_t mutexHandle;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/CMSIS2/RXF_Mutex.h
*********************************************************************/
