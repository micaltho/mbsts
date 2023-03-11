/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickDownHandler
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickDownHandler.h
*********************************************************************/

#ifndef JoystickDownHandler_H
#define JoystickDownHandler_H

//## package LPC1769::JoystickDriver

//## class JoystickDownHandler
class JoystickDownHandler {
    ////    Constructors and destructors    ////
    
public :

    JoystickDownHandler(void);
    
    virtual ~JoystickDownHandler(void) = 0;
    
    ////    Operations    ////
    
    //## operation onClick()
    virtual void onClick(void) = 0;
    
    //## operation onReleased()
    virtual void onReleased(void) = 0;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickDownHandler.h
*********************************************************************/
