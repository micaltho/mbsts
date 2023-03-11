/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickLeftIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickLeftIRQ.h
*********************************************************************/

#ifndef JoystickLeftIRQ_H
#define JoystickLeftIRQ_H

#include "RXF_Event.h"
class JoystickLeftButton;

//## package LPC1769::JoystickDriver::JoystickLeftIRQ



class evJoystickLeftPressed : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickLeftPressed(void);
};

extern const RXF::Event::Id_t evJoystickLeftPressed_JoystickLeftIRQ_JoystickDriver_LPC1769_id;

class evJoystickLeftReleased : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickLeftReleased(void);
};

extern const RXF::Event::Id_t evJoystickLeftReleased_JoystickLeftIRQ_JoystickDriver_LPC1769_id;

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickLeftIRQ.h
*********************************************************************/
