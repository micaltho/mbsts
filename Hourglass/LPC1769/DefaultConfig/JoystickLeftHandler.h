/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickLeftHandler
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickLeftHandler.h
*********************************************************************/

#ifndef JoystickLeftHandler_H
#define JoystickLeftHandler_H

//## package LPC1769::JoystickDriver

//## class JoystickLeftHandler
class JoystickLeftHandler {
    ////    Constructors and destructors    ////
    
public :

    JoystickLeftHandler(void);
    
    virtual ~JoystickLeftHandler(void) = 0;
    
    ////    Operations    ////
    
    //## operation onClick()
    virtual void onClick(void) = 0;
    
    //## operation onReleased()
    virtual void onReleased(void) = 0;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickLeftHandler.h
*********************************************************************/
