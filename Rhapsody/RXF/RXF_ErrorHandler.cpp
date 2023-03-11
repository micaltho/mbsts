/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ErrorHandler/RXF_ErrorHandler.cpp
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#include "RXF_ErrorHandler.h"
namespace RXF {
    void ErrorHandler::error(const ErrorCode errorCode, const std::int32_t additionalArgument, const bool returnAllowed)
    {
        static_cast<void>(additionalArgument);
        
        /* 
        The error handler is called by the RXF if any error is detected. This operation is by default implemented as an endless loop, blocking the framework.
        It is strongly recommended to provide your own error handler implementation, which fits your specific application and environment needs.
        This can be done by aplying the Stereotype  <<RXFErrorHandler>> to a new Package in your user Model. This error handler will override the default one.
        Returning from this function also is a possibility, depending on the impact of a specific error code and the application.
        */
        
        switch(errorCode)
        {
        	case ERROR_REACTIVE_EVENT_NOT_CONSUMED:
        		// The user has do decide himself, if this error is critical.
        		break;
        	default:
        		// By default, the error handler will not return.
        		while(1);
        }
        
        /* If error handler is called with argument returnAllowed false, a return would have major implications.
           Do not delete this while loop. Place your code to safely reboot or shut down your system here. */
        while(!returnAllowed)
        {
        
        }
    }
}

/*********************************************************************
	File Path	: ../Source/ErrorHandler/RXF_ErrorHandler.cpp
*********************************************************************/
