/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCJoystickLeftButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCJoystickLeftButton.h
*********************************************************************/

#ifndef LPCJoystickLeftButton_H
#define LPCJoystickLeftButton_H

#include "LPC1769.h"
#include "JoystickLeftHandler.h"
class Controller;

//## package LPC1769

//## class LPCJoystickLeftButton
class LPCJoystickLeftButton : public JoystickLeftHandler {
    ////    Constructors and destructors    ////
    
public :

    LPCJoystickLeftButton(void);
    
    virtual ~LPCJoystickLeftButton(void);
    
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
	File Path	: LPC1769/DefaultConfig/LPCJoystickLeftButton.h
*********************************************************************/
