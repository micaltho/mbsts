/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Target/ARM/RXF_CriticalSection.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_CriticalSection_H
#define RXF_CriticalSection_H

#include <cmsis_compiler.h>
#include <cstdint>
namespace RXF {
    class CriticalSection {
    public :
    
        // Satisfies requirement 2863: CriticalSection - Enter
        // A CriticalSection shall provide an operation to enter a critical section.
        // 
        inline void lock(void)
        {
            interruptMask = __get_PRIMASK();
            
            /* Disable Interrupts */
            __set_PRIMASK( 1 );
        }
        
        // Satisfies requirement 2864: CriticalSection - Exit
        // A CriticalSection shall provide an operation to exit a critical section.
        // 
        inline void unlock(void) const
        {
            /* reset interruptMask */
            __set_PRIMASK( interruptMask );
        }
        
        ////    Attributes    ////
    
    private :
    
        std::uint32_t interruptMask;
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/Target/ARM/RXF_CriticalSection.h
*********************************************************************/
