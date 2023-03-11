/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/generic/RXF_ReactiveMacros.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef RXF_ReactiveMacros_H
#define RXF_ReactiveMacros_H

namespace RXF {
    //#[ ignore
    // This file contains macros that Rhapsody uses in its generated code.
    //#]
    
    
    /* @MISRA_16-0-2,16-0-4,16-0-6,16-2-1,16-2-2,16-3-2=OFF ID-0007: Function-like Macros must be used for Rhapsody code generation compatibility. */
    
    
    #define IS_COMPLETED(state) state##_isCompleted()
    #define IS_IN(state) state##_IN()
    
    
    /* @MISRA_16-0-2,16-0-4,16-0-6,16-2-1,16-2-2,16-3-2=ON (end of ID-0007) */
}

#endif
/*********************************************************************
	File Path	: ../Source/generic/RXF_ReactiveMacros.h
*********************************************************************/
