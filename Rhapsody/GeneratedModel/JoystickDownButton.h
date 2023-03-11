/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickDownButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickDownButton.h
*********************************************************************/

#ifndef JoystickDownButton_H
#define JoystickDownButton_H

#include "JoystickDownIRQ.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <digitalinout.h>
#include <cstdint>
class JoystickDownHandler;

//## package LPC1769::JoystickDriver::JoystickDownIRQ

//## class JoystickDownButton
class JoystickDownButton : public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation JoystickDownButton(bool,uint8_t,uint8_t)
    JoystickDownButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext = NULL);
    
    virtual ~JoystickDownButton(void);
    
    ////    Additional operations    ////
    
    bool getIsPressed(void) const;
    
    void setIsPressed(const bool p_isPressed);
    
    Platform::BSP::DigitalInOut* getItsDigitalInOut(void) const;
    
    JoystickDownHandler* getItsJoystickDownHandler(void) const;
    
    void setItsJoystickDownHandler(JoystickDownHandler* const p_JoystickDownHandler);
    
    virtual bool startBehavior(void);

protected :

    void cleanUpRelations(void);

public :

    virtual void send_evJoystickDownPressed(void);
    
    virtual void send_evJoystickDownReleased(void);
    
    ////    Attributes    ////

protected :

    bool isPressed;		//## attribute isPressed
    
    ////    Relations and components    ////
    
    Platform::BSP::DigitalInOut itsDigitalInOut;
    
    JoystickDownHandler* itsJoystickDownHandler;
    
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
    
    enum JoystickDownButton_Enum {
        OMNonState = 0,
        sReleased = 1,
        sPressed = 2
    };

private :

    JoystickDownButton_Enum rootState_subState;
    
    JoystickDownButton_Enum rootState_active;
};

inline bool JoystickDownButton::rootState_IN(void) const {
    return true;
}

inline bool JoystickDownButton::sReleased_IN(void) const {
    return rootState_subState == sReleased;
}

inline bool JoystickDownButton::sPressed_IN(void) const {
    return rootState_subState == sPressed;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickDownButton.h
*********************************************************************/
