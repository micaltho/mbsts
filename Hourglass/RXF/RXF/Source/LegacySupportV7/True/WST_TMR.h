/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/LegacySupportV7/True/WST_TMR.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef WST_TMR_H
#define WST_TMR_H

#include "RXF_Timer.h"
class WST_TMR {
public :

    inline static RXF::Timer::Ticks_t timeToTicks(std::uint32_t const time)
    {
        return RXF::Timer::timeToTicks( time );
    }
};

#endif
/*********************************************************************
	File Path	: ../Source/LegacySupportV7/True/WST_TMR.h
*********************************************************************/
