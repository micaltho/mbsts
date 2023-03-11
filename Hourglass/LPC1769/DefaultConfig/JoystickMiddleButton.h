/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickMiddleButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickMiddleButton.h
*********************************************************************/

#ifndef JoystickMiddleButton_H
#define JoystickMiddleButton_H

#include "JoystickMiddelIRQ.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <digitalinout.h>
#include <cstdint>
class JoystickMiddleHandler;

//## package LPC1769::JoystickDriver::JoystickMiddelIRQ

//## class JoystickMiddleButton
class JoystickMiddleButton : public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation JoystickMiddleButton(bool,uint8_t,uint8_t)
    JoystickMiddleButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext = NULL);
    
    virtual ~JoystickMiddleButton(void);
    
    ////    Additional operations    ////
    
    bool getIsPressed(void) const;
    
    void setIsPressed(const bool p_isPressed);
    
    Platform::BSP::DigitalInOut* getItsDigitalInOut(void) const;
    
    JoystickMiddleHandler* getItsJoystickMiddleHandler(void) const;
    
    void setItsJoystickMiddleHandler(JoystickMiddleHandler* const p_JoystickMiddleHandler);
    
    virtual bool startBehavior(void);

protected :

    void cleanUpRelations(void);

public :

    virtual void send_evJoystickMiddlePressed(void);
    
    virtual void send_evJoystickMiddleReleased(void);
    
    ////    Attributes    ////

protected :

    bool isPressed;		//## attribute isPressed
    
    ////    Relations and components    ////
    
    Platform::BSP::DigitalInOut itsDigitalInOut;
    
    JoystickMiddleHandler* itsJoystickMiddleHandler;
    
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
    
    enum JoystickMiddleButton_Enum {
        OMNonState = 0,
        sReleased = 1,
        sPressed = 2
    };

private :

    JoystickMiddleButton_Enum rootState_subState;
    
    JoystickMiddleButton_Enum rootState_active;
};

inline bool JoystickMiddleButton::rootState_IN(void) const {
    return true;
}

inline bool JoystickMiddleButton::sReleased_IN(void) const {
    return rootState_subState == sReleased;
}

inline bool JoystickMiddleButton::sPressed_IN(void) const {
    return rootState_subState == sPressed;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickMiddleButton.h
*********************************************************************/
