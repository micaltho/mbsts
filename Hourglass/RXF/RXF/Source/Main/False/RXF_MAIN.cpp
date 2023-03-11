/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Main/False/RXF_MAIN.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_MAIN.h"
#include "RXF_MainTask.h"
extern "C" {
void RXF_MainTask_start(void)
{
    RXF::MainTask::start();
}
}

/*********************************************************************
	File Path	: ../Source/Main/False/RXF_MAIN.cpp
*********************************************************************/
