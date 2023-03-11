/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickDownButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickDownButton.cpp
*********************************************************************/

#include "RXF_Active.h"
#include "JoystickDownButton.h"
#include "JoystickDownHandler.h"
//## package LPC1769::JoystickDriver::JoystickDownIRQ

//## class JoystickDownButton
JoystickDownButton::JoystickDownButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext) : isPressed(isPressed), itsDigitalInOut(port, pin), itsJoystickDownHandler(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState) {
    setActiveContext(activeContext, false);
    
    //#[ operation JoystickDownButton(bool,uint8_t,uint8_t)
    itsDigitalInOut.onInterrupt([&](uint32_t edge){
    if( ( (edge & Platform::BSP::DigitalInOut::EdgeType::FALLING_EDGE) && !this->isPressed)
    || ( (edge & Platform::BSP::DigitalInOut::EdgeType::RISING_EDGE) && this->isPressed) )
    {
    GEN(evJoystickDownPressed());
    }
    else
    {
    GEN(evJoystickDownReleased());
    }
    },
    Platform::BSP::DigitalInOut::EdgeType::ANY_EDGE);
    
    //#]
}

JoystickDownButton::~JoystickDownButton(void) {
    cleanUpRelations();
}

bool JoystickDownButton::getIsPressed(void) const {
    return isPressed;
}

void JoystickDownButton::setIsPressed(const bool p_isPressed) {
    isPressed = p_isPressed;
}

Platform::BSP::DigitalInOut* JoystickDownButton::getItsDigitalInOut(void) const {
    return (Platform::BSP::DigitalInOut*) &itsDigitalInOut;
}

JoystickDownHandler* JoystickDownButton::getItsJoystickDownHandler(void) const {
    return itsJoystickDownHandler;
}

void JoystickDownButton::setItsJoystickDownHandler(JoystickDownHandler* const p_JoystickDownHandler) {
    itsJoystickDownHandler = p_JoystickDownHandler;
}

bool JoystickDownButton::startBehavior(void) {
    bool done = true;
    if(done == true)
        {
            done = RXF::Reactive::startBehavior();
        }
    return done;
}

void JoystickDownButton::cleanUpRelations(void) {
    if(itsJoystickDownHandler != nullptr)
        {
            itsJoystickDownHandler = nullptr;
        }
}

void JoystickDownButton::send_evJoystickDownPressed(void) {
    send( new evJoystickDownPressed()  );
}

void JoystickDownButton::send_evJoystickDownReleased(void) {
    send( new evJoystickDownReleased()  );
}

void JoystickDownButton::rootState_entDef(void) {
    {
        rootState_subState = sReleased;
        rootState_active = sReleased;
    }
}

RXF::Reactive::TakeEventStatus JoystickDownButton::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State sReleased
        case sReleased:
        {
            if(evJoystickDownPressed_JoystickDownIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 1 
                    itsJoystickDownHandler->onClick();
                    //#]
                    rootState_subState = sPressed;
                    rootState_active = sPressed;
                    res = eventConsumed;
                }
            
        }
        break;
        // State sPressed
        case sPressed:
        {
            if(evJoystickDownReleased_JoystickDownIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 2 
                    itsJoystickDownHandler->onReleased();
                    //#]
                    rootState_subState = sReleased;
                    rootState_active = sReleased;
                    res = eventConsumed;
                }
            
        }
        break;
        default:
            break;
    }
    return res;
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/JoystickDownButton.cpp
*********************************************************************/
