/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickLeftIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickLeftIRQ.cpp
*********************************************************************/

#include "JoystickLeftIRQ.h"
#include "JoystickLeftButton.h"
//## package LPC1769::JoystickDriver::JoystickLeftIRQ



evJoystickLeftPressed::evJoystickLeftPressed(void) {
    setId(evJoystickLeftPressed_JoystickLeftIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickLeftPressed_JoystickLeftIRQ_JoystickDriver_LPC1769_id(11401);

evJoystickLeftReleased::evJoystickLeftReleased(void) {
    setId(evJoystickLeftReleased_JoystickLeftIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickLeftReleased_JoystickLeftIRQ_JoystickDriver_LPC1769_id(11402);

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickLeftIRQ.cpp
*********************************************************************/
