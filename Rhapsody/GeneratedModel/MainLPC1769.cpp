/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: DefaultConfig
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/MainLPC1769.cpp
*********************************************************************/

#include "MainLPC1769.h"
#include "Application.h"
#include "JoystickDownIRQ.h"
#include "JoystickLeftIRQ.h"
#include "JoystickMiddelIRQ.h"
#include "JoystickRightIRQ.h"
#include "JoystickUpIRQ.h"
#include "LPC1769.h"
#include "RXF_MainTask.h"
LPC1769::LPC1769(void) {
    LPC1769_initRelations();
    (void) LPC1769_startBehavior();
}

void RXF::MainTask::execute( void) {
    if(initializeFramework())
        {
            LPC1769 initializer_LPC1769;
            //#[ configuration LPC1769::DefaultConfig 
            //#]
            RXF::Active::execute();
        }
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/MainLPC1769.cpp
*********************************************************************/
