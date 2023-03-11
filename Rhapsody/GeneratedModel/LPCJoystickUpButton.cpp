/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickUpButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickUpButton.cpp
*********************************************************************/

#include "LPCJoystickUpButton.h"
#include "Controller.h"
//## package LPC1769

//## class LPCJoystickUpButton
LPCJoystickUpButton::LPCJoystickUpButton(void) : itsController(nullptr) {
}

LPCJoystickUpButton::~LPCJoystickUpButton(void) {
    cleanUpRelations();
}

void LPCJoystickUpButton::onClick(void) {
    //#[ operation onClick()
    itsController->GEN(evGoBack());
    //#]
}

void LPCJoystickUpButton::onReleased(void) {
    //#[ operation onReleased()
    //#]
}

Controller* LPCJoystickUpButton::getItsController(void) const {
    return itsController;
}

void LPCJoystickUpButton::setItsController(Controller* const p_Controller) {
    itsController = p_Controller;
}

void LPCJoystickUpButton::cleanUpRelations(void) {
    if(itsController != nullptr)
        {
            itsController = nullptr;
        }
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCJoystickUpButton.cpp
*********************************************************************/
