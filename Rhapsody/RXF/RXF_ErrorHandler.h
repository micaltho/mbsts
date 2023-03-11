/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ErrorHandler/RXF_ErrorHandler.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_ErrorHandler_H
#define RXF_ErrorHandler_H

#include "RXF_ErrorCodes.h"
#include <cstdint>
namespace RXF {
    class ErrorHandler {
    public :
    
        static void error(const ErrorCode errorCode, const std::int32_t additionalArgument, const bool returnAllowed);
    };
}

#endif
/*********************************************************************
	File Path	: ../Source/ErrorHandler/RXF_ErrorHandler.h
*********************************************************************/
