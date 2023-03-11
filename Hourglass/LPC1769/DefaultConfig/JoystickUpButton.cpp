/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickUpButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickUpButton.cpp
*********************************************************************/

#include "RXF_Active.h"
#include "JoystickUpButton.h"
#include "JoystickUpHandler.h"
//## package LPC1769::JoystickDriver::JoystickUpIRQ

//## class JoystickUpButton
JoystickUpButton::JoystickUpButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext) : isPressed(isPressed), itsDigitalInOut(port, pin), itsJoystickUpHandler(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState) {
    setActiveContext(activeContext, false);
    
    //#[ operation JoystickUpButton(bool,uint8_t,uint8_t)
    itsDigitalInOut.onInterrupt([&](uint32_t edge){
    if( ( (edge & Platform::BSP::DigitalInOut::EdgeType::FALLING_EDGE) && !this->isPressed)
    || ( (edge & Platform::BSP::DigitalInOut::EdgeType::RISING_EDGE) && this->isPressed) )
    {
    GEN(evJoystickUpPressed());
    }
    else
    {
    GEN(evJoystickUpReleased());
    }
    },
    Platform::BSP::DigitalInOut::EdgeType::ANY_EDGE);
    
    //#]
}

JoystickUpButton::~JoystickUpButton(void) {
    cleanUpRelations();
}

bool JoystickUpButton::getIsPressed(void) const {
    return isPressed;
}

void JoystickUpButton::setIsPressed(const bool p_isPressed) {
    isPressed = p_isPressed;
}

Platform::BSP::DigitalInOut* JoystickUpButton::getItsDigitalInOut(void) const {
    return (Platform::BSP::DigitalInOut*) &itsDigitalInOut;
}

JoystickUpHandler* JoystickUpButton::getItsJoystickUpHandler(void) const {
    return itsJoystickUpHandler;
}

void JoystickUpButton::setItsJoystickUpHandler(JoystickUpHandler* const p_JoystickUpHandler) {
    itsJoystickUpHandler = p_JoystickUpHandler;
}

bool JoystickUpButton::startBehavior(void) {
    bool done = true;
    if(done == true)
        {
            done = RXF::Reactive::startBehavior();
        }
    return done;
}

void JoystickUpButton::cleanUpRelations(void) {
    if(itsJoystickUpHandler != nullptr)
        {
            itsJoystickUpHandler = nullptr;
        }
}

void JoystickUpButton::send_evJoystickUpPressed(void) {
    send( new evJoystickUpPressed()  );
}

void JoystickUpButton::send_evJoystickUpReleased(void) {
    send( new evJoystickUpReleased()  );
}

void JoystickUpButton::rootState_entDef(void) {
    {
        rootState_subState = sReleased;
        rootState_active = sReleased;
    }
}

RXF::Reactive::TakeEventStatus JoystickUpButton::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State sReleased
        case sReleased:
        {
            if(evJoystickUpPressed_JoystickUpIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 1 
                    itsJoystickUpHandler->onClick();
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
            if(evJoystickUpReleased_JoystickUpIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 2 
                    itsJoystickUpHandler->onReleased();
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
	File Path	: LPC1769/DefaultConfig/JoystickUpButton.cpp
*********************************************************************/
