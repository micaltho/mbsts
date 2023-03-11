/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickRightButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickRightButton.h
*********************************************************************/

#ifndef JoystickRightButton_H
#define JoystickRightButton_H

#include "JoystickRightIRQ.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <digitalinout.h>
#include <cstdint>
class JoystickRightHandler;

//## package LPC1769::JoystickDriver::JoystickRightIRQ

//## class JoystickRightButton
class JoystickRightButton : public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation JoystickRightButton(bool,uint8_t,uint8_t)
    JoystickRightButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext = NULL);
    
    virtual ~JoystickRightButton(void);
    
    ////    Additional operations    ////
    
    bool getIsPressed(void) const;
    
    void setIsPressed(const bool p_isPressed);
    
    Platform::BSP::DigitalInOut* getItsDigitalInOut(void) const;
    
    JoystickRightHandler* getItsJoystickRightHandler(void) const;
    
    void setItsJoystickRightHandler(JoystickRightHandler* const p_JoystickRightHandler);
    
    virtual bool startBehavior(void);

protected :

    void cleanUpRelations(void);

public :

    virtual void send_evJoystickRightPressed(void);
    
    virtual void send_evJoystickRightReleased(void);
    
    ////    Attributes    ////

protected :

    bool isPressed;		//## attribute isPressed
    
    ////    Relations and components    ////
    
    Platform::BSP::DigitalInOut itsDigitalInOut;
    
    JoystickRightHandler* itsJoystickRightHandler;
    
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
    
    enum JoystickRightButton_Enum {
        OMNonState = 0,
        sReleased = 1,
        sPressed = 2
    };

private :

    JoystickRightButton_Enum rootState_subState;
    
    JoystickRightButton_Enum rootState_active;
};

inline bool JoystickRightButton::rootState_IN(void) const {
    return true;
}

inline bool JoystickRightButton::sReleased_IN(void) const {
    return rootState_subState == sReleased;
}

inline bool JoystickRightButton::sPressed_IN(void) const {
    return rootState_subState == sPressed;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickRightButton.h
*********************************************************************/
