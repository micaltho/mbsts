/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickRightIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickRightIRQ.h
*********************************************************************/

#ifndef JoystickRightIRQ_H
#define JoystickRightIRQ_H

#include "RXF_Event.h"
class JoystickRightButton;

//## package LPC1769::JoystickDriver::JoystickRightIRQ



class evJoystickRightPressed : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickRightPressed(void);
};

extern const RXF::Event::Id_t evJoystickRightPressed_JoystickRightIRQ_JoystickDriver_LPC1769_id;

class evJoystickRightReleased : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickRightReleased(void);
};

extern const RXF::Event::Id_t evJoystickRightReleased_JoystickRightIRQ_JoystickDriver_LPC1769_id;

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickRightIRQ.h
*********************************************************************/
