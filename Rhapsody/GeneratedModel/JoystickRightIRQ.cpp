/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickRightIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickRightIRQ.cpp
*********************************************************************/

#include "JoystickRightIRQ.h"
#include "JoystickRightButton.h"
//## package LPC1769::JoystickDriver::JoystickRightIRQ



evJoystickRightPressed::evJoystickRightPressed(void) {
    setId(evJoystickRightPressed_JoystickRightIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickRightPressed_JoystickRightIRQ_JoystickDriver_LPC1769_id(11001);

evJoystickRightReleased::evJoystickRightReleased(void) {
    setId(evJoystickRightReleased_JoystickRightIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickRightReleased_JoystickRightIRQ_JoystickDriver_LPC1769_id(11002);

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickRightIRQ.cpp
*********************************************************************/
