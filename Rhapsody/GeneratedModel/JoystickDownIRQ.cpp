/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickDownIRQ
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickDownIRQ.cpp
*********************************************************************/

#include "JoystickDownIRQ.h"
#include "JoystickDownButton.h"
//## package LPC1769::JoystickDriver::JoystickDownIRQ



evJoystickDownPressed::evJoystickDownPressed(void) {
    setId(evJoystickDownPressed_JoystickDownIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickDownPressed_JoystickDownIRQ_JoystickDriver_LPC1769_id(14001);

evJoystickDownReleased::evJoystickDownReleased(void) {
    setId(evJoystickDownReleased_JoystickDownIRQ_JoystickDriver_LPC1769_id);
}

const RXF::Event::Id_t evJoystickDownReleased_JoystickDownIRQ_JoystickDriver_LPC1769_id(14002);

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickDownIRQ.cpp
*********************************************************************/
