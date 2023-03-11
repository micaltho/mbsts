/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/RTOS/FreeRTOS/RXF_Priority.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_Priority_H
#define RXF_Priority_H

#include <FreeRTOS.h>
#include <task.h>
namespace RXF {
    namespace Priority {
        typedef UBaseType_t Type;
        
        constexpr Type HIGHEST = configMAX_PRIORITIES;
        
        constexpr Type HIGHER = tskIDLE_PRIORITY + 8U;
        
        constexpr Type HIGH = tskIDLE_PRIORITY + 7U;
        
        constexpr Type ABOVE_NORMAL = tskIDLE_PRIORITY + 6U;
        
        constexpr Type NORMAL = tskIDLE_PRIORITY + 5U;
        
        constexpr Type BELOW_NORMAL = tskIDLE_PRIORITY + 4U;
        
        constexpr Type LOW = tskIDLE_PRIORITY + 3U;
        
        constexpr Type LOWER = tskIDLE_PRIORITY + 2U;
        
        constexpr Type LOWEST = tskIDLE_PRIORITY + 1U;
    }
}

#endif
/*********************************************************************
	File Path	: ../Source/RTOS/FreeRTOS/RXF_Priority.h
*********************************************************************/
