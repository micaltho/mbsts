/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickUpIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickUpIRQ.cpp
*********************************************************************/

#include "JoystickUpIRQ.h"
#include "JoystickUpButton.h"
//## package LPC1769::JoystickDriver::JoystickUpIRQ



evJoystickUpPressed::evJoystickUpPressed(void) {
    setId(evJoystickUpPressed_JoystickUpIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickUpPressed_JoystickUpIRQ_JoystickDriver_LPC1769_id(2601);

evJoystickUpReleased::evJoystickUpReleased(void) {
    setId(evJoystickUpReleased_JoystickUpIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickUpReleased_JoystickUpIRQ_JoystickDriver_LPC1769_id(2602);

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickUpIRQ.cpp
*********************************************************************/
