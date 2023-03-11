/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * 
 *
 * File Path	: ../Source/OxfInterfaces/IOxfEventSender.h
 *
 * Copyright (C) Willert Software Tools GmbH.
 *
 *****************************************************************************/

#ifndef IOxfEventSender_H
#define IOxfEventSender_H

namespace RXF {
    class Event;
}


/* @MISRA_7-3-1=OFF ID-0005: Class name without namespace needed for OXF compatibility */


// A thin interface specifying the service to send events.
// This can be used for reactive interfaces (interfaces with event receptions) since all they do is accept the event.
class IOxfEventSender {
public :

    // send the specified event to the instance active context queue
    // Argument RXF::Event* const event :
    // The event to send
    // Satisfies requirement 3682: IOxfEventSender - Receive Event
    // The IOxfEventSender interface with send operation shall be provided for OXF compatibility.
    // 
    virtual void send(RXF::Event* const event) = 0;

protected :

    /* @MISRA_0-1-8=OFF ID-0003: The Interface needs a virtual destructor, because it has virtual operations. */
    inline virtual ~IOxfEventSender(void)
    {
    }
    /* @MISRA_0-1-8=ON (end of ID-0003) */

private :

    virtual IOxfEventSender& operator=(const IOxfEventSender& other) = delete;
};


/* @MISRA_7-3-1=ON (end of ID-0005) */

#endif
/*********************************************************************
	File Path	: ../Source/OxfInterfaces/IOxfEventSender.h
*********************************************************************/
