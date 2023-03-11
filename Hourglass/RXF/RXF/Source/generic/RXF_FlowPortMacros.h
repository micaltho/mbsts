/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_FlowPortMacros.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_FlowPortMacros_H
#define RXF_FlowPortMacros_H

namespace RXF {
    #define FLOW_DATA_SEND(flowPort, servicePortName, relayFunc, serializeFunc) OUT_PORT(servicePortName)->relayFunc(flowPort);
    #define FLOW_DATA_RECEIVE(argName, argValue, serializeFunc) 
    #define FLOW_GEN(PORT, EVENT) OUT_PORT(PORT##_SP)->GEN(EVENT)
    #define FLOW_DATA_POP
}

#endif
/*********************************************************************
	File Path	: ../Source/generic/RXF_FlowPortMacros.h
*********************************************************************/
