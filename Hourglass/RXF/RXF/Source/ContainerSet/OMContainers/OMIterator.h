/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/ContainerSet/OMContainers/OMIterator.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef OMIterator_H
#define OMIterator_H

#include "OMAbstractContainer.h"
#include "RXF_Types.h"
// Iterator on containers derived from OMAbstractContainer
template <class Concept> class OMIterator {
public :

    // Abstract container instantiation used by the iterator
    //## class OMIterator::Container
    typedef OMAbstractContainer<Concept> Container;
    
    // Initialize an empty iterator
    inline OMIterator(void) : thePos(nullptr), theLink(nullptr)
    {
    }
    
    // Initialize an iterator associated with the provided container
    // Argument const Container& aContainer :
    // The iterator context
    inline OMIterator(const Container& aContainer) : thePos(nullptr), theLink(&aContainer) 
    {
        reset();
    }
    
    // Initialize an iterator associated with the provided container
    // Argument const Container* aContainer :
    // The iterator context
    inline OMIterator(const Container* aContainer) : thePos(nullptr), theLink(aContainer)
    {
        reset();
    }
    
    // Copy constructor
    // Argument const OMIterator<Concept> & iter :
    // The iterator to copy
    inline OMIterator(const OMIterator<Concept> & iter) : thePos(iter.thePos), theLink(iter.theLink)
    {
    }
    
    // Copy Constructor
    inline OMIterator(const OMIterator<Concept>* iter) : thePos(iter->thePos), theLink(iter->theLink)
    {
    }
    
    // Assignment operator
    // Argument const OMIterator<Concept> & iter :
    // The iterator to copy
    inline OMIterator<Concept> & operator=(const OMIterator<Concept> & iter)
    {
        theLink = iter.theLink;
        thePos = iter.thePos;
        return (*this);
    }
    
    // Move to the next item in the collection
    inline OMIterator<Concept> & increment(void)
    {
        if (theLink != nullptr) 
        {
        	theLink->getNext(thePos);
        }
        return (*this);
    }
    
    // Get the current item
    inline Concept & value(void) const
    {
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        if (theLink != nullptr) {
           	return theLink->getCurrent(thePos);
        } else {
           	return OMNullValue<Concept>::get();
        }
    }
    
    // Get the current item
    inline Concept & operator*(void) const
    {
        return value();
    }
    
    // Reset the iterator (to the first element in the container)
    inline void reset(void)
    {
        if (theLink != nullptr) {
        	theLink->getFirst(thePos); 
        }
    }
    
    // Reset the iterator to the specified container
    // Argument const Container& newLink :
    // The new context of the iterator
    inline void reset(const Container& newLink)
    {
        theLink = &newLink; 
        reset();
    }
    
    // Advance to the next item in the collection
    inline OMIterator<Concept> & operator++(void)
    {
        return increment(); 
    }
    
    // Advance to the next item in the collection (postfix operator)
    // Argument type has to be int, because operator++ is part of the language standard and assumes int
    // Argument RXF::int_t :
    // C++ postfix ++ operator dummy argument
    inline OMIterator<Concept> operator++(RXF::int_t)
    {
        OMIterator<Concept> T(*this) ;	// save status prior to increment
        (void) increment();
        return T; 
    }
    
    // Cleanup
    inline ~OMIterator(void)
    {
        theLink = nullptr;
    }
    
    // This operator is needed for RXFContainer compatible break conditions.
    inline bool operator!=(const OMIterator& other) const
    {
        return thePos != other.thePos;
    }
    
    // This operator is needed for RXFContainer compatible break conditions.
    inline bool operator==(const OMIterator& other) const
    {
        return thePos == other.thePos;
    }
    
    ////    Attributes    ////

private :

    // The current position of the iterator (in the collection)
    void * thePos;
    
    const Container* theLink;
};

#endif
/*********************************************************************
	File Path	: ../Source/ContainerSet/OMContainers/OMIterator.h
*********************************************************************/
