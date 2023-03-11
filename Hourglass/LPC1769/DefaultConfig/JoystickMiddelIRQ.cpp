/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickMiddelIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickMiddelIRQ.cpp
*********************************************************************/

#include "JoystickMiddelIRQ.h"
#include "JoystickMiddleButton.h"
//## package LPC1769::JoystickDriver::JoystickMiddelIRQ



evJoystickMiddlePressed::evJoystickMiddlePressed(void) {
    setId(evJoystickMiddlePressed_JoystickMiddelIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickMiddlePressed_JoystickMiddelIRQ_JoystickDriver_LPC1769_id(27201);

evJoystickMiddleReleased::evJoystickMiddleReleased(void) {
    setId(evJoystickMiddleReleased_JoystickMiddelIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickMiddleReleased_JoystickMiddelIRQ_JoystickDriver_LPC1769_id(27202);

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickMiddelIRQ.cpp
*********************************************************************/
