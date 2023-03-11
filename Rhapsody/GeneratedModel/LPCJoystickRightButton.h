/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickRightButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickRightButton.h
*********************************************************************/

#ifndef LPCJoystickRightButton_H
#define LPCJoystickRightButton_H

#include "LPC1769.h"
#include "JoystickRightHandler.h"
class Controller;

//## package LPC1769

//## class LPCJoystickRightButton
class LPCJoystickRightButton : public JoystickRightHandler {
    ////    Constructors and destructors    ////
    
public :

    LPCJoystickRightButton(void);
    
    virtual ~LPCJoystickRightButton(void);
    
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
	File Path	: LPC1769/DefaultConfig/LPCJoystickRightButton.h
*********************************************************************/
