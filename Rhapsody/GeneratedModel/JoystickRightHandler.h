/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickRightHandler
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickRightHandler.h
*********************************************************************/

#ifndef JoystickRightHandler_H
#define JoystickRightHandler_H

//## package LPC1769::JoystickDriver

//## class JoystickRightHandler
class JoystickRightHandler {
    ////    Constructors and destructors    ////
    
public :

    JoystickRightHandler(void);
    
    virtual ~JoystickRightHandler(void) = 0;
    
    ////    Operations    ////
    
    //## operation onClick()
    virtual void onClick(void) = 0;
    
    //## operation onReleased()
    virtual void onReleased(void) = 0;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickRightHandler.h
*********************************************************************/
