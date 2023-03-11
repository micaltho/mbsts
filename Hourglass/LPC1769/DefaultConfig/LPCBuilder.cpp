/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCBuilder
//!	Generated Date	: Thu, 18, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCBuilder.cpp
*********************************************************************/

#include "RXF_Active.h"
#include "LPCBuilder.h"
//## package LPC1769

//## class LPCBuilder
LPCBuilder::LPCBuilder(RXF::Active* const activeContext) : itsJoystickDownButton(false, 0, 15), itsJoystickUpButton(false, 2, 3), itsJoystickLeftButton(false, 2, 4), itsJoystickRightButton(false, 0, 16), itsJoystickMiddleButton(false, 0, 17), itsDisplayTask(12), itsTimeCounter(1), itsController(0, 10, 10), itsAccelerationMeasuring(10) {
    setActiveContext(activeContext, false);
    
    initRelations();
}

LPCBuilder::~LPCBuilder(void) {
}

LPCInit* LPCBuilder::getItsLPCInit(void) const {
    return (LPCInit*) &itsLPCInit;
}

LPCAccelerationSensor* LPCBuilder::getItsLPCAccelerationSensor(void) const {
    return (LPCAccelerationSensor*) &itsLPCAccelerationSensor;
}

LPCJoystickMiddleButton* LPCBuilder::getItsLPCJoystickMiddleButton(void) const {
    return (LPCJoystickMiddleButton*) &itsLPCJoystickMiddleButton;
}

LPCJoystickRightButton* LPCBuilder::getItsLPCJoystickRightButton(void) const {
    return (LPCJoystickRightButton*) &itsLPCJoystickRightButton;
}

LPCJoystickLeftButton* LPCBuilder::getItsLPCJoystickLeftButton(void) const {
    return (LPCJoystickLeftButton*) &itsLPCJoystickLeftButton;
}

LPCJoystickUpButton* LPCBuilder::getItsLPCJoystickUpButton(void) const {
    return (LPCJoystickUpButton*) &itsLPCJoystickUpButton;
}

LPCJoystickDownButton* LPCBuilder::getItsLPCJoystickDownButton(void) const {
    return (LPCJoystickDownButton*) &itsLPCJoystickDownButton;
}

LPCOledDisplay* LPCBuilder::getItsLPCOledDisplay(void) const {
    return (LPCOledDisplay*) &itsLPCOledDisplay;
}

JoystickDownButton* LPCBuilder::getItsJoystickDownButton(void) const {
    return (JoystickDownButton*) &itsJoystickDownButton;
}

JoystickUpButton* LPCBuilder::getItsJoystickUpButton(void) const {
    return (JoystickUpButton*) &itsJoystickUpButton;
}

JoystickLeftButton* LPCBuilder::getItsJoystickLeftButton(void) const {
    return (JoystickLeftButton*) &itsJoystickLeftButton;
}

JoystickRightButton* LPCBuilder::getItsJoystickRightButton(void) const {
    return (JoystickRightButton*) &itsJoystickRightButton;
}

JoystickMiddleButton* LPCBuilder::getItsJoystickMiddleButton(void) const {
    return (JoystickMiddleButton*) &itsJoystickMiddleButton;
}

DisplayTask* LPCBuilder::getItsDisplayTask(void) const {
    return (DisplayTask*) &itsDisplayTask;
}

TimeCounter* LPCBuilder::getItsTimeCounter(void) const {
    return (TimeCounter*) &itsTimeCounter;
}

Controller* LPCBuilder::getItsController(void) const {
    return (Controller*) &itsController;
}

AccelerationMeasuring* LPCBuilder::getItsAccelerationMeasuring(void) const {
    return (AccelerationMeasuring*) &itsAccelerationMeasuring;
}

LPCEeprom* LPCBuilder::getItsLPCEeprom(void) const {
    return (LPCEeprom*) &itsLPCEeprom;
}

ConfigStorage* LPCBuilder::getItsConfigStorage(void) const {
    return (ConfigStorage*) &itsConfigStorage;
}

bool LPCBuilder::startBehavior(void) {
    bool done = true;
    done = done && itsJoystickDownButton.startBehavior();
    done = done && itsJoystickUpButton.startBehavior();
    done = done && itsJoystickLeftButton.startBehavior();
    done = done && itsJoystickRightButton.startBehavior();
    done = done && itsJoystickMiddleButton.startBehavior();
    done = done && itsDisplayTask.startBehavior();
    done = done && itsTimeCounter.startBehavior();
    done = done && itsController.startBehavior();
    done = done && itsAccelerationMeasuring.startBehavior();
    done = done && itsConfigStorage.startBehavior();
    return done;
}

void LPCBuilder::initRelations(void) {
    itsLPCJoystickDownButton.setItsController(&itsController);
    itsLPCJoystickLeftButton.setItsController(&itsController);
    itsLPCJoystickMiddleButton.setItsController(&itsController);
    itsLPCJoystickRightButton.setItsController(&itsController);
    itsLPCJoystickUpButton.setItsController(&itsController);
    itsJoystickDownButton.setItsJoystickDownHandler(&itsLPCJoystickDownButton);
    itsJoystickLeftButton.setItsJoystickLeftHandler(&itsLPCJoystickLeftButton);
    itsJoystickMiddleButton.setItsJoystickMiddleHandler(&itsLPCJoystickMiddleButton);
    itsJoystickRightButton.setItsJoystickRightHandler(&itsLPCJoystickRightButton);
    itsJoystickUpButton.setItsJoystickUpHandler(&itsLPCJoystickUpButton);
    itsController.setItsDisplayTask(&itsDisplayTask);
    itsDisplayTask.setItsDisplay(&itsLPCOledDisplay);
    itsController.setItsTimeCounter(&itsTimeCounter);
    itsController.setItsAccelerationMeasuring(&itsAccelerationMeasuring);
    itsAccelerationMeasuring.setItsAccelerationData(&itsLPCAccelerationSensor);
    itsController.setItsConfigStorage(&itsConfigStorage);
    itsConfigStorage.setItsEepromData(&itsLPCEeprom);
}

void LPCBuilder::setActiveContext(RXF::Active* const activeContext, bool activeInstance) {
    {
        itsJoystickDownButton.setActiveContext(activeContext, false);
        itsJoystickUpButton.setActiveContext(activeContext, false);
        itsJoystickLeftButton.setActiveContext(activeContext, false);
        itsJoystickRightButton.setActiveContext(activeContext, false);
        itsJoystickMiddleButton.setActiveContext(activeContext, false);
        itsConfigStorage.setActiveContext(activeContext, false);
    }
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCBuilder.cpp
*********************************************************************/
