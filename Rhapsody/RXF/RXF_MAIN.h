/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Main/True/RXF_MAIN.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MAIN_H
#define RXF_MAIN_H

#include "RXF_Types.h"
namespace RXF {
    class MainTask;
}

// The RXF owns the main by default. If you need to integrate the RXF in an existing main, look at property RXF::DeployerFolders::Main for more detailed information.
RXF::int_t main(void);

#endif
/*********************************************************************
	File Path	: ../Source/Main/True/RXF_MAIN.h
*********************************************************************/
