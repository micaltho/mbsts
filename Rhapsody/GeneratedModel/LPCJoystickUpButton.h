/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickUpButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickUpButton.h
*********************************************************************/

#ifndef LPCJoystickUpButton_H
#define LPCJoystickUpButton_H

#include "LPC1769.h"
#include "JoystickUpHandler.h"
class Controller;

//## package LPC1769

//## class LPCJoystickUpButton
class LPCJoystickUpButton : public JoystickUpHandler {
    ////    Constructors and destructors    ////
    
public :

    LPCJoystickUpButton(void);
    
    virtual ~LPCJoystickUpButton(void);
    
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
	File Path	: LPC1769/DefaultConfig/LPCJoystickUpButton.h
*********************************************************************/
