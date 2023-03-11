/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickLeftButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickLeftButton.cpp
*********************************************************************/

#include "LPCJoystickLeftButton.h"
#include "Controller.h"
//## package LPC1769

//## class LPCJoystickLeftButton
LPCJoystickLeftButton::LPCJoystickLeftButton(void) : itsController(nullptr) {
}

LPCJoystickLeftButton::~LPCJoystickLeftButton(void) {
    cleanUpRelations();
}

void LPCJoystickLeftButton::onClick(void) {
    //#[ operation onClick()
    itsController->GEN(evTimeFactorSetting());
    itsController->GEN(evReduceStartTime());
    itsController->GEN(evReduceTimeFactor());
    //#]
}

void LPCJoystickLeftButton::onReleased(void) {
    //#[ operation onReleased()
    //#]
}

Controller* LPCJoystickLeftButton::getItsController(void) const {
    return itsController;
}

void LPCJoystickLeftButton::setItsController(Controller* const p_Controller) {
    itsController = p_Controller;
}

void LPCJoystickLeftButton::cleanUpRelations(void) {
    if(itsController != nullptr)
        {
            itsController = nullptr;
        }
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCJoystickLeftButton.cpp
*********************************************************************/
