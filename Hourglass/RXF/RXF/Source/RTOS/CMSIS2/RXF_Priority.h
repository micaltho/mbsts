/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/CMSIS2/RXF_Priority.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Priority_H
#define RXF_Priority_H

#include <cmsis_os2.h>
namespace RXF {
    namespace Priority {
        
        /* @MISRA_0-1-4,3-4-1=OFF ID-0006: The priorities shall be available for the user. */
        
        
        typedef osPriority_t Type;
        
        constexpr Type HIGHEST = osPriorityRealtime7;
        
        constexpr Type HIGHER = osPriorityRealtime;
        
        constexpr Type HIGH = osPriorityHigh;
        
        constexpr Type ABOVE_NORMAL = osPriorityAboveNormal;
        
        constexpr Type NORMAL = osPriorityNormal;
        
        constexpr Type BELOW_NORMAL = osPriorityBelowNormal;
        
        constexpr Type LOW = osPriorityLow7;
        
        constexpr Type LOWER = osPriorityLow4;
        
        constexpr Type LOWEST = osPriorityLow;
        
        
        /* @MISRA_0-1-4,3-4-1=ON (end of ID-0006) */
    }
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/CMSIS2/RXF_Priority.h
*********************************************************************/
