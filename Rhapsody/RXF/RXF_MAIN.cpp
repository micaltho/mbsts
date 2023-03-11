/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Main/True/RXF_MAIN.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_MAIN.h"
#include "RXF_MainTask.h"
/* @MISRA_15-3-2=OFF ID-0005: The RXF does not use exceptions. Therefor no try and catch is needed. */
RXF::int_t main(void)
{
    RXF::MainTask::start();	
    
    return 0;
}

/* @MISRA_15-3-2=ON (end of ID-0005) */

/*********************************************************************
	File Path	: ../Source/Main/True/RXF_MAIN.cpp
*********************************************************************/
