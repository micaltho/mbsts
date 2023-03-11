/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickMiddleButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickMiddleButton.h
*********************************************************************/

#ifndef LPCJoystickMiddleButton_H
#define LPCJoystickMiddleButton_H

#include "LPC1769.h"
#include "JoystickMiddleHandler.h"
class Controller;

//## package LPC1769

//## class LPCJoystickMiddleButton
class LPCJoystickMiddleButton : public JoystickMiddleHandler {
    ////    Constructors and destructors    ////
    
public :

    LPCJoystickMiddleButton(void);
    
    virtual ~LPCJoystickMiddleButton(void);
    
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
	File Path	: LPC1769/DefaultConfig/LPCJoystickMiddleButton.h
*********************************************************************/
