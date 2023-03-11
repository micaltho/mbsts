/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickMiddleButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickMiddleButton.cpp
*********************************************************************/

#include "LPCJoystickMiddleButton.h"
#include "Controller.h"
//## package LPC1769

//## class LPCJoystickMiddleButton
LPCJoystickMiddleButton::LPCJoystickMiddleButton(void) : itsController(nullptr) {
}

LPCJoystickMiddleButton::~LPCJoystickMiddleButton(void) {
    cleanUpRelations();
}

void LPCJoystickMiddleButton::onClick(void) {
    //#[ operation onClick()
    itsController->GEN(evReset());
    //#]
}

void LPCJoystickMiddleButton::onReleased(void) {
    //#[ operation onReleased()
    //#]
}

Controller* LPCJoystickMiddleButton::getItsController(void) const {
    return itsController;
}

void LPCJoystickMiddleButton::setItsController(Controller* const p_Controller) {
    itsController = p_Controller;
}

void LPCJoystickMiddleButton::cleanUpRelations(void) {
    if(itsController != nullptr)
        {
            itsController = nullptr;
        }
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCJoystickMiddleButton.cpp
*********************************************************************/
