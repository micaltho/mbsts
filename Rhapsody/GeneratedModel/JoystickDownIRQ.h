/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickDownIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickDownIRQ.h
*********************************************************************/

#ifndef JoystickDownIRQ_H
#define JoystickDownIRQ_H

#include "RXF_Event.h"
class JoystickDownButton;

//## package LPC1769::JoystickDriver::JoystickDownIRQ



class evJoystickDownPressed : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickDownPressed(void);
};

extern const RXF::Event::Id_t evJoystickDownPressed_JoystickDownIRQ_JoystickDriver_LPC1769_id;

class evJoystickDownReleased : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickDownReleased(void);
};

extern const RXF::Event::Id_t evJoystickDownReleased_JoystickDownIRQ_JoystickDriver_LPC1769_id;

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickDownIRQ.h
*********************************************************************/
