/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCBuilder
//!	Generated Date	: Mon, 8, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCBuilder.h
*********************************************************************/

#ifndef LPCBuilder_H
#define LPCBuilder_H

#include "LPC1769.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include "AccelerationMeasuring.h"
#include "ConfigStorage.h"
#include "Controller.h"
#include "DisplayTask.h"
#include "JoystickDownButton.h"
#include "JoystickLeftButton.h"
#include "JoystickMiddleButton.h"
#include "JoystickRightButton.h"
#include "JoystickUpButton.h"
#include "LPCAccelerationSensor.h"
#include "LPCEeprom.h"
#include "LPCInit.h"
#include "LPCJoystickDownButton.h"
#include "LPCJoystickLeftButton.h"
#include "LPCJoystickMiddleButton.h"
#include "LPCJoystickRightButton.h"
#include "LPCJoystickUpButton.h"
#include "LPCOledDisplay.h"
#include "TimeCounter.h"
//## package LPC1769

//## class LPCBuilder
class LPCBuilder {
    ////    Constructors and destructors    ////
    
public :

    LPCBuilder(RXF::Active* const activeContext = NULL);
    
    virtual ~LPCBuilder(void);
    
    ////    Additional operations    ////
    
    LPCInit* getItsLPCInit(void) const;
    
    LPCAccelerationSensor* getItsLPCAccelerationSensor(void) const;
    
    LPCJoystickMiddleButton* getItsLPCJoystickMiddleButton(void) const;
    
    LPCJoystickRightButton* getItsLPCJoystickRightButton(void) const;
    
    LPCJoystickLeftButton* getItsLPCJoystickLeftButton(void) const;
    
    LPCJoystickUpButton* getItsLPCJoystickUpButton(void) const;
    
    LPCJoystickDownButton* getItsLPCJoystickDownButton(void) const;
    
    LPCOledDisplay* getItsLPCOledDisplay(void) const;
    
    JoystickDownButton* getItsJoystickDownButton(void) const;
    
    JoystickUpButton* getItsJoystickUpButton(void) const;
    
    JoystickLeftButton* getItsJoystickLeftButton(void) const;
    
    JoystickRightButton* getItsJoystickRightButton(void) const;
    
    JoystickMiddleButton* getItsJoystickMiddleButton(void) const;
    
    DisplayTask* getItsDisplayTask(void) const;
    
    TimeCounter* getItsTimeCounter(void) const;
    
    Controller* getItsController(void) const;
    
    AccelerationMeasuring* getItsAccelerationMeasuring(void) const;
    
    LPCEeprom* getItsLPCEeprom(void) const;
    
    ConfigStorage* getItsConfigStorage(void) const;
    
    virtual bool startBehavior(void);

protected :

    void initRelations(void);
    
    ////    Relations and components    ////
    
    LPCInit itsLPCInit;
    
    LPCAccelerationSensor itsLPCAccelerationSensor;
    
    LPCJoystickMiddleButton itsLPCJoystickMiddleButton;
    
    LPCJoystickRightButton itsLPCJoystickRightButton;
    
    LPCJoystickLeftButton itsLPCJoystickLeftButton;
    
    LPCJoystickUpButton itsLPCJoystickUpButton;
    
    LPCJoystickDownButton itsLPCJoystickDownButton;
    
    LPCOledDisplay itsLPCOledDisplay;
    
    JoystickDownButton itsJoystickDownButton;
    
    JoystickUpButton itsJoystickUpButton;
    
    JoystickLeftButton itsJoystickLeftButton;
    
    JoystickRightButton itsJoystickRightButton;
    
    JoystickMiddleButton itsJoystickMiddleButton;
    
    DisplayTask itsDisplayTask;
    
    TimeCounter itsTimeCounter;
    
    Controller itsController;
    
    AccelerationMeasuring itsAccelerationMeasuring;
    
    LPCEeprom itsLPCEeprom;
    
    ConfigStorage itsConfigStorage;
    
    ////    Framework operations    ////

public :

    void setActiveContext(RXF::Active* const activeContext, bool activeInstance);
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCBuilder.h
*********************************************************************/
