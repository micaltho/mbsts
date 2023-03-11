/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickRightButton
//!	Generated Date	: Thu, 18, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickRightButton.cpp
*********************************************************************/

#include "LPCJoystickRightButton.h"
#include "Controller.h"
//## package LPC1769

//## class LPCJoystickRightButton
LPCJoystickRightButton::LPCJoystickRightButton(void) : itsController(nullptr) {
}

LPCJoystickRightButton::~LPCJoystickRightButton(void) {
    cleanUpRelations();
}

void LPCJoystickRightButton::onClick(void) {
    //#[ operation onClick()
    itsController->GEN(evStartTimeSetting());
    itsController->GEN(evRaiseStartTime());
    itsController->GEN(evRaiseTimeFactor());
    //#]
}

void LPCJoystickRightButton::onReleased(void) {
    //#[ operation onReleased()
    //#]
}

Controller* LPCJoystickRightButton::getItsController(void) const {
    return itsController;
}

void LPCJoystickRightButton::setItsController(Controller* const p_Controller) {
    itsController = p_Controller;
}

void LPCJoystickRightButton::cleanUpRelations(void) {
    if(itsController != nullptr)
        {
            itsController = nullptr;
        }
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCJoystickRightButton.cpp
*********************************************************************/
