/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickLeftButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickLeftButton.h
*********************************************************************/

#ifndef JoystickLeftButton_H
#define JoystickLeftButton_H

#include "JoystickLeftIRQ.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <digitalinout.h>
#include <cstdint>
class JoystickLeftHandler;

//## package LPC1769::JoystickDriver::JoystickLeftIRQ

//## class JoystickLeftButton
class JoystickLeftButton : public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation JoystickLeftButton(bool,uint8_t,uint8_t)
    JoystickLeftButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext = NULL);
    
    virtual ~JoystickLeftButton(void);
    
    ////    Additional operations    ////
    
    bool getIsPressed(void) const;
    
    void setIsPressed(const bool p_isPressed);
    
    Platform::BSP::DigitalInOut* getItsDigitalInOut(void) const;
    
    JoystickLeftHandler* getItsJoystickLeftHandler(void) const;
    
    void setItsJoystickLeftHandler(JoystickLeftHandler* const p_JoystickLeftHandler);
    
    virtual bool startBehavior(void);

protected :

    void cleanUpRelations(void);

public :

    virtual void send_evJoystickLeftPressed(void);
    
    virtual void send_evJoystickLeftReleased(void);
    
    ////    Attributes    ////

protected :

    bool isPressed;		//## attribute isPressed
    
    ////    Relations and components    ////
    
    Platform::BSP::DigitalInOut itsDigitalInOut;
    
    JoystickLeftHandler* itsJoystickLeftHandler;
    
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
    
    enum JoystickLeftButton_Enum {
        OMNonState = 0,
        sReleased = 1,
        sPressed = 2
    };

private :

    JoystickLeftButton_Enum rootState_subState;
    
    JoystickLeftButton_Enum rootState_active;
};

inline bool JoystickLeftButton::rootState_IN(void) const {
    return true;
}

inline bool JoystickLeftButton::sReleased_IN(void) const {
    return rootState_subState == sReleased;
}

inline bool JoystickLeftButton::sPressed_IN(void) const {
    return rootState_subState == sPressed;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickLeftButton.h
*********************************************************************/
