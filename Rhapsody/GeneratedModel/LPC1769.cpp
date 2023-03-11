/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPC1769
//!	Generated Date	: Mon, 8, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPC1769.cpp
*********************************************************************/

#include "LPC1769.h"
#include "LPCBuilder.h"
#include "LPCAccelerationSensor.h"
#include "LPCEeprom.h"
#include "LPCJoystickDownButton.h"
#include "LPCJoystickLeftButton.h"
#include "LPCJoystickMiddleButton.h"
#include "LPCJoystickRightButton.h"
#include "LPCJoystickUpButton.h"
#include "LPCOledDisplay.h"
//## package LPC1769


LPCBuilder itsLPCBuilder;

void LPC1769_initRelations(void) {
}

bool LPC1769_startBehavior(void) {
    bool done = true;
    if(done == true)
        {
            done = itsLPCBuilder.startBehavior();
        }
    return done;
}

LPC1769_OMInitializer::LPC1769_OMInitializer(void) {
    LPC1769_initRelations();
    (void) LPC1769_startBehavior();
}

LPC1769_OMInitializer::~LPC1769_OMInitializer(void) {
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPC1769.cpp
*********************************************************************/
