/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/OMContainers/OMNullValue.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef OMNullValue_H
#define OMNullValue_H

// Empty value class - used by containers to return non-existing element
template <class Concept> class OMNullValue {
public :

    // Get the empty value
    inline static Concept & get(void)
    {
        static std::int32_t nullSet = 0;
        static std::uint8_t nillValue[sizeof(Concept)];
        if ( nullSet == 0 ) {
        	// need to zero the array 
        	nullSet = 1; 
        	for ( std::uint32_t i = 0U; i < (sizeof(Concept)); ++i ) {
        		nillValue[i] = 0U;
        	}
        }
        /* @MISRA_5-2-7=OFF XD-0001: Cast from pointer to pointer. Needs to be done to be generic. */
        return reinterpret_cast<Concept&>(*nillValue); 
        /* @MISRA_5-2-7=ON (end of XD-0001) */
    }
};

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/OMContainers/OMNullValue.h
*********************************************************************/
