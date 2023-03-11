/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/LegacySupportV7/True/WST_TMM.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef WST_TMM_H
#define WST_TMM_H

#include "RXF_Tick.h"
class WST_TMM {
public :

    inline static std::uint32_t getTicks(void)
    {
        return RXF::Tick::getTicks();
    }
};

#endif
/*********************************************************************
	File Path	: ../Source/LegacySupportV7/True/WST_TMM.h
*********************************************************************/
