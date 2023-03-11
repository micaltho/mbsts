/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickMiddelIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickMiddelIRQ.h
*********************************************************************/

#ifndef JoystickMiddelIRQ_H
#define JoystickMiddelIRQ_H

#include "RXF_Event.h"
class JoystickMiddleButton;

//## package LPC1769::JoystickDriver::JoystickMiddelIRQ



class evJoystickMiddlePressed : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickMiddlePressed(void);
};

extern const RXF::Event::Id_t evJoystickMiddlePressed_JoystickMiddelIRQ_JoystickDriver_LPC1769_id;

class evJoystickMiddleReleased : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evJoystickMiddleReleased(void);
};

extern const RXF::Event::Id_t evJoystickMiddleReleased_JoystickMiddelIRQ_JoystickDriver_LPC1769_id;

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickMiddelIRQ.h
*********************************************************************/
