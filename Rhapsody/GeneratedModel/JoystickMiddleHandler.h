/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickMiddleHandler
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickMiddleHandler.h
*********************************************************************/

#ifndef JoystickMiddleHandler_H
#define JoystickMiddleHandler_H

//## package LPC1769::JoystickDriver

//## class JoystickMiddleHandler
class JoystickMiddleHandler {
    ////    Constructors and destructors    ////
    
public :

    JoystickMiddleHandler(void);
    
    virtual ~JoystickMiddleHandler(void) = 0;
    
    ////    Operations    ////
    
    //## operation onClick()
    virtual void onClick(void) = 0;
    
    //## operation onReleased()
    virtual void onReleased(void) = 0;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickMiddleHandler.h
*********************************************************************/
