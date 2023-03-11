/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_Event.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_Config.h"
#include "RXF_ErrorHandler.h"
#include "RXF_MemoryPool.h"
#include "RXF_Event.h"
namespace RXF {
    void Event::destroy(void) const
    {
        if( deleteAfterConsume )
        {
        	delete this;
        }
    }
}

/*********************************************************************
	File Path	: ../Source/generic/RXF_Event.cpp
*********************************************************************/
