/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickMiddleButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickMiddleButton.cpp
*********************************************************************/

#include "RXF_Active.h"
#include "JoystickMiddleButton.h"
#include "JoystickMiddleHandler.h"
//## package LPC1769::JoystickDriver::JoystickMiddelIRQ

//## class JoystickMiddleButton
JoystickMiddleButton::JoystickMiddleButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext) : isPressed(isPressed), itsDigitalInOut(port, pin), itsJoystickMiddleHandler(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState) {
    setActiveContext(activeContext, false);
    
    //#[ operation JoystickMiddleButton(bool,uint8_t,uint8_t)
    itsDigitalInOut.onInterrupt([&](uint32_t edge){
    if( ( (edge & Platform::BSP::DigitalInOut::EdgeType::FALLING_EDGE) && !this->isPressed)
    || ( (edge & Platform::BSP::DigitalInOut::EdgeType::RISING_EDGE) && this->isPressed) )
    {
    GEN(evJoystickMiddlePressed());
    }
    else
    {
    GEN(evJoystickMiddleReleased());
    }
    },
    Platform::BSP::DigitalInOut::EdgeType::ANY_EDGE);
    
    //#]
}

JoystickMiddleButton::~JoystickMiddleButton(void) {
    cleanUpRelations();
}

bool JoystickMiddleButton::getIsPressed(void) const {
    return isPressed;
}

void JoystickMiddleButton::setIsPressed(const bool p_isPressed) {
    isPressed = p_isPressed;
}

Platform::BSP::DigitalInOut* JoystickMiddleButton::getItsDigitalInOut(void) const {
    return (Platform::BSP::DigitalInOut*) &itsDigitalInOut;
}

JoystickMiddleHandler* JoystickMiddleButton::getItsJoystickMiddleHandler(void) const {
    return itsJoystickMiddleHandler;
}

void JoystickMiddleButton::setItsJoystickMiddleHandler(JoystickMiddleHandler* const p_JoystickMiddleHandler) {
    itsJoystickMiddleHandler = p_JoystickMiddleHandler;
}

bool JoystickMiddleButton::startBehavior(void) {
    bool done = true;
    if(done == true)
        {
            done = RXF::Reactive::startBehavior();
        }
    return done;
}

void JoystickMiddleButton::cleanUpRelations(void) {
    if(itsJoystickMiddleHandler != nullptr)
        {
            itsJoystickMiddleHandler = nullptr;
        }
}

void JoystickMiddleButton::send_evJoystickMiddlePressed(void) {
    send( new evJoystickMiddlePressed()  );
}

void JoystickMiddleButton::send_evJoystickMiddleReleased(void) {
    send( new evJoystickMiddleReleased()  );
}

void JoystickMiddleButton::rootState_entDef(void) {
    {
        rootState_subState = sReleased;
        rootState_active = sReleased;
    }
}

RXF::Reactive::TakeEventStatus JoystickMiddleButton::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State sReleased
        case sReleased:
        {
            if(evJoystickMiddlePressed_JoystickMiddelIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 1 
                    itsJoystickMiddleHandler->onClick();
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
            if(evJoystickMiddleReleased_JoystickMiddelIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 2 
                    itsJoystickMiddleHandler->onReleased();
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
	File Path	: LPC1769/DefaultConfig/JoystickMiddleButton.cpp
*********************************************************************/
