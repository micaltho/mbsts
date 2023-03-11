/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPC1769
//!	Generated Date	: Mon, 8, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPC1769.h
*********************************************************************/

#ifndef LPC1769_H
#define LPC1769_H

class LPCAccelerationSensor;

class LPCBuilder;

class LPCEeprom;

class LPCJoystickDownButton;

class LPCJoystickLeftButton;

class LPCJoystickMiddleButton;

class LPCJoystickRightButton;

class LPCJoystickUpButton;

class LPCOledDisplay;

//## package LPC1769


extern LPCBuilder itsLPCBuilder;

void LPC1769_initRelations(void);

bool LPC1769_startBehavior(void);

class LPC1769_OMInitializer {
    ////    Constructors and destructors    ////
    
public :

    LPC1769_OMInitializer(void);
    
    ~LPC1769_OMInitializer(void);
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPC1769.h
*********************************************************************/
