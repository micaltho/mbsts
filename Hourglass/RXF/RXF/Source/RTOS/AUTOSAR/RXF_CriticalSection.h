/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/AUTOSAR/RXF_CriticalSection.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_CriticalSection_H
#define RXF_CriticalSection_H

#include "RXF_Mutex.h"
namespace RXF {
    class CriticalSection {
    public :
    
        inline void lock(void)
        {
            mutex.lock();
        }
        
        inline void unlock(void)
        {
            mutex.unlock();
        }
        
        ////    Attributes    ////
    
    private :
    
        static Mutex mutex;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/AUTOSAR/RXF_CriticalSection.h
*********************************************************************/
