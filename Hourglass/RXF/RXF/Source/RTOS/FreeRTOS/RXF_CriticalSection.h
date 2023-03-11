/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/FreeRTOS/RXF_CriticalSection.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_CriticalSection_H
#define RXF_CriticalSection_H

#include <FreeRTOS.h>
#include <task.h>
namespace RXF {
    class CriticalSection {
    public :
    
        // Satisfies requirement 2863: CriticalSection - Enter
        // A CriticalSection shall provide an operation to enter a critical section.
        // 
        inline void lock(void)
        {
            interruptMask = taskENTER_CRITICAL_FROM_ISR();
        }
        
        // Satisfies requirement 2864: CriticalSection - Exit
        // A CriticalSection shall provide an operation to exit a critical section.
        // 
        inline void unlock(void) const
        {
            taskEXIT_CRITICAL_FROM_ISR( interruptMask );
        }
        
        ////    Attributes    ////
    
    private :
    
        UBaseType_t interruptMask;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/FreeRTOS/RXF_CriticalSection.h
*********************************************************************/
