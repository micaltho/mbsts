/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickRightButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickRightButton.cpp
*********************************************************************/

#include "RXF_Active.h"
#include "JoystickRightButton.h"
#include "JoystickRightHandler.h"
//## package LPC1769::JoystickDriver::JoystickRightIRQ

//## class JoystickRightButton
JoystickRightButton::JoystickRightButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext) : isPressed(isPressed), itsDigitalInOut(port, pin), itsJoystickRightHandler(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState) {
    setActiveContext(activeContext, false);
    
    //#[ operation JoystickRightButton(bool,uint8_t,uint8_t)
    itsDigitalInOut.onInterrupt([&](uint32_t edge){
    if( ( (edge & Platform::BSP::DigitalInOut::EdgeType::FALLING_EDGE) && !this->isPressed)
    || ( (edge & Platform::BSP::DigitalInOut::EdgeType::RISING_EDGE) && this->isPressed) )
    {
    GEN(evJoystickRightPressed());
    }
    else
    {
    GEN(evJoystickRightReleased());
    }
    },
    Platform::BSP::DigitalInOut::EdgeType::ANY_EDGE);
    
    //#]
}

JoystickRightButton::~JoystickRightButton(void) {
    cleanUpRelations();
}

bool JoystickRightButton::getIsPressed(void) const {
    return isPressed;
}

void JoystickRightButton::setIsPressed(const bool p_isPressed) {
    isPressed = p_isPressed;
}

Platform::BSP::DigitalInOut* JoystickRightButton::getItsDigitalInOut(void) const {
    return (Platform::BSP::DigitalInOut*) &itsDigitalInOut;
}

JoystickRightHandler* JoystickRightButton::getItsJoystickRightHandler(void) const {
    return itsJoystickRightHandler;
}

void JoystickRightButton::setItsJoystickRightHandler(JoystickRightHandler* const p_JoystickRightHandler) {
    itsJoystickRightHandler = p_JoystickRightHandler;
}

bool JoystickRightButton::startBehavior(void) {
    bool done = true;
    if(done == true)
        {
            done = RXF::Reactive::startBehavior();
        }
    return done;
}

void JoystickRightButton::cleanUpRelations(void) {
    if(itsJoystickRightHandler != nullptr)
        {
            itsJoystickRightHandler = nullptr;
        }
}

void JoystickRightButton::send_evJoystickRightPressed(void) {
    send( new evJoystickRightPressed()  );
}

void JoystickRightButton::send_evJoystickRightReleased(void) {
    send( new evJoystickRightReleased()  );
}

void JoystickRightButton::rootState_entDef(void) {
    {
        rootState_subState = sReleased;
        rootState_active = sReleased;
    }
}

RXF::Reactive::TakeEventStatus JoystickRightButton::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State sReleased
        case sReleased:
        {
            if(evJoystickRightPressed_JoystickRightIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 1 
                    itsJoystickRightHandler->onClick();
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
            if(evJoystickRightReleased_JoystickRightIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 2 
                    itsJoystickRightHandler->onReleased();
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
	File Path	: LPC1769/DefaultConfig/JoystickRightButton.cpp
*********************************************************************/
