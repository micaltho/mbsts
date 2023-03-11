/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/OMContainers/OMAbstractContainer.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef OMAbstractContainer_H
#define OMAbstractContainer_H

#include "OMNullValue.h"
template <class Concept> class OMIterator;

// A generic type-safe container, Used by OMIterator<> to iterate over the derived containers.
template <class Concept> class OMAbstractContainer {
public :

    ////    Friend List    ////
    
    friend  class OMIterator<Concept>;
    
    
    // Virtual destructor to enable polymorphic deletion
    inline virtual ~OMAbstractContainer(void)
    {
    }

protected :

    // Get the element at the given position (called by the iterator)
    // Argument void * pos :
    // The current iterator position
    virtual Concept & getCurrent(void * pos) const = 0;
    
    // Set the initial position for the iterator
    // Argument void*& pos :
    // The position to set
    virtual void getFirst(void*& pos) const = 0;
    
    // Update the provided position to the next position in the container
    // Argument void*& pos :
    // The position to update
    virtual void getNext(void*& pos) const = 0;
};

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/OMContainers/OMAbstractContainer.h
*********************************************************************/
