/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickDownButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickDownButton.h
*********************************************************************/

#ifndef LPCJoystickDownButton_H
#define LPCJoystickDownButton_H

#include "LPC1769.h"
#include "JoystickDownHandler.h"
class Controller;

//## package LPC1769

//## class LPCJoystickDownButton
class LPCJoystickDownButton : public JoystickDownHandler {
    ////    Constructors and destructors    ////
    
public :

    LPCJoystickDownButton(void);
    
    virtual ~LPCJoystickDownButton(void);
    
    ////    Operations    ////
    
    //## operation onClick()
    virtual void onClick(void);
    
    //## operation onReleased()
    virtual void onReleased(void);
    
    ////    Additional operations    ////
    
    Controller* getItsController(void) const;
    
    void setItsController(Controller* const p_Controller);

protected :

    void cleanUpRelations(void);
    
    ////    Relations and components    ////
    
    Controller* itsController;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCJoystickDownButton.h
*********************************************************************/
