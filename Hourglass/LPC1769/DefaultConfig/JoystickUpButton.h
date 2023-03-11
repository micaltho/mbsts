/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickUpButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickUpButton.h
*********************************************************************/

#ifndef JoystickUpButton_H
#define JoystickUpButton_H

#include "JoystickUpIRQ.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <digitalinout.h>
#include <cstdint>
class JoystickUpHandler;

//## package LPC1769::JoystickDriver::JoystickUpIRQ

//## class JoystickUpButton
class JoystickUpButton : public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation JoystickUpButton(bool,uint8_t,uint8_t)
    JoystickUpButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext = NULL);
    
    virtual ~JoystickUpButton(void);
    
    ////    Additional operations    ////
    
    bool getIsPressed(void) const;
    
    void setIsPressed(const bool p_isPressed);
    
    Platform::BSP::DigitalInOut* getItsDigitalInOut(void) const;
    
    JoystickUpHandler* getItsJoystickUpHandler(void) const;
    
    void setItsJoystickUpHandler(JoystickUpHandler* const p_JoystickUpHandler);
    
    virtual bool startBehavior(void);

protected :

    void cleanUpRelations(void);

public :

    virtual void send_evJoystickUpPressed(void);
    
    virtual void send_evJoystickUpReleased(void);
    
    ////    Attributes    ////

protected :

    bool isPressed;		//## attribute isPressed
    
    ////    Relations and components    ////
    
    Platform::BSP::DigitalInOut itsDigitalInOut;
    
    JoystickUpHandler* itsJoystickUpHandler;
    
    ////    Framework operations    ////

public :

    // rootState:
    inline bool rootState_IN(void) const;
    
    // sReleased:
    inline bool sReleased_IN(void) const;
    
    // sPressed:
    inline bool sPressed_IN(void) const;

protected :

    virtual void rootState_entDef(void);
    
    virtual RXF::Reactive::TakeEventStatus rootState_processEvent(void);
    
    ////    Framework    ////
    
    enum JoystickUpButton_Enum {
        OMNonState = 0,
        sReleased = 1,
        sPressed = 2
    };

private :

    JoystickUpButton_Enum rootState_subState;
    
    JoystickUpButton_Enum rootState_active;
};

inline bool JoystickUpButton::rootState_IN(void) const {
    return true;
}

inline bool JoystickUpButton::sReleased_IN(void) const {
    return rootState_subState == sReleased;
}

inline bool JoystickUpButton::sPressed_IN(void) const {
    return rootState_subState == sPressed;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickUpButton.h
*********************************************************************/
