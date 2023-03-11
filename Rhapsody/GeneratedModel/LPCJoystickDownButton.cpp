/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickDownButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickDownButton.cpp
*********************************************************************/

#include "LPCJoystickDownButton.h"
#include "Controller.h"
//## package LPC1769

//## class LPCJoystickDownButton
LPCJoystickDownButton::LPCJoystickDownButton(void) : itsController(nullptr) {
}

LPCJoystickDownButton::~LPCJoystickDownButton(void) {
    cleanUpRelations();
}

void LPCJoystickDownButton::onClick(void) {
    //#[ operation onClick()
    itsController->GEN(evMenu());
    //#]
}

void LPCJoystickDownButton::onReleased(void) {
    //#[ operation onReleased()
    //#]
}

Controller* LPCJoystickDownButton::getItsController(void) const {
    return itsController;
}

void LPCJoystickDownButton::setItsController(Controller* const p_Controller) {
    itsController = p_Controller;
}

void LPCJoystickDownButton::cleanUpRelations(void) {
    if(itsController != nullptr)
        {
            itsController = nullptr;
        }
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCJoystickDownButton.cpp
*********************************************************************/
