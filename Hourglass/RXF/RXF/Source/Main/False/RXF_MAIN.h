/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/Main/False/RXF_MAIN.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_MAIN_H
#define RXF_MAIN_H

// This operation is a wrapper for for RXF::MainTask::start() and can be called from a C or C++ context to start the RXF. This Operation will not return. Look at property RXF::DeployerFolders::Main for more detailed information.
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void RXF_MainTask_start(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
/*********************************************************************
	File Path	: ../Source/Main/False/RXF_MAIN.h
*********************************************************************/
