/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickUpHandler
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickUpHandler.h
*********************************************************************/

#ifndef JoystickUpHandler_H
#define JoystickUpHandler_H

//## package LPC1769::JoystickDriver

//## class JoystickUpHandler
class JoystickUpHandler {
    ////    Constructors and destructors    ////
    
public :

    JoystickUpHandler(void);
    
    virtual ~JoystickUpHandler(void) = 0;
    
    ////    Operations    ////
    
    //## operation onClick()
    virtual void onClick(void) = 0;
    
    //## operation onReleased()
    virtual void onReleased(void) = 0;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickUpHandler.h
*********************************************************************/
