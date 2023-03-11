/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/AUTOSAR/RXF_Priority.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Priority_H
#define RXF_Priority_H

#include "RXF_Types.h"
namespace RXF {
    namespace Priority {
        typedef unsigned int Type;
        static constexpr Type HIGHEST = 99;
        
        constexpr Type HIGHER = 80;
        
        constexpr Type HIGH = 70;
        
        constexpr Type ABOVE_NORMAL = 60;
        
        constexpr Type NORMAL = 50;
        
        constexpr Type BELOW_NORMAL = 40;
        
        constexpr Type LOW = 30;
        
        constexpr Type LOWER = 20;
        
        constexpr Type LOWEST = 1;
    }
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/AUTOSAR/RXF_Priority.h
*********************************************************************/
