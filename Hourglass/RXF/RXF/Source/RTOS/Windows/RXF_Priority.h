/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/Windows/RXF_Priority.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Priority_H
#define RXF_Priority_H

#include "Windows.h"
namespace RXF {
    namespace Priority {
        //#[ ignore
        // For documentation on scheduling priorities see https://docs.microsoft.com/en-us/windows/win32/procthread/scheduling-priorities
        //#]
        
        typedef int Type;
        
        constexpr Type HIGHEST = THREAD_PRIORITY_TIME_CRITICAL;
        
        constexpr Type HIGHER = THREAD_PRIORITY_NORMAL + 3;
        
        constexpr Type HIGH = THREAD_PRIORITY_NORMAL + 2;
        
        constexpr Type ABOVE_NORMAL = THREAD_PRIORITY_NORMAL + 1;
        
        constexpr Type NORMAL = THREAD_PRIORITY_NORMAL;
        
        constexpr Type BELOW_NORMAL = THREAD_PRIORITY_NORMAL - 1;
        
        constexpr Type LOW = THREAD_PRIORITY_NORMAL - 2;
        
        constexpr Type LOWER = THREAD_PRIORITY_NORMAL - 3;
        
        constexpr Type LOWEST = THREAD_PRIORITY_IDLE;
    }
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/Windows/RXF_Priority.h
*********************************************************************/
