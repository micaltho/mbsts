/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickUpIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickUpIRQ.h
*********************************************************************/

#ifndef JoystickUpIRQ_H
#define JoystickUpIRQ_H

#include "RXF_Event.h"
class JoystickUpButton;

//## package LPC1769::JoystickDriver::JoystickUpIRQ



class evJoystickUpPressed : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickUpPressed(void);
};

extern const RXF::Event::Id_t evJoystickUpPressed_JoystickUpIRQ_JoystickDriver_LPC1769_id;

class evJoystickUpReleased : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickUpReleased(void);
};

extern const RXF::Event::Id_t evJoystickUpReleased_JoystickUpIRQ_JoystickDriver_LPC1769_id;

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickUpIRQ.h
*********************************************************************/
