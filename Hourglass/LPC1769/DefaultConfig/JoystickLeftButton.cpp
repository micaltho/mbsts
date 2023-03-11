/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: JoystickLeftButton
//!	Generated Date	: Wed, 3, Aug 2022  
	File Path	: LPC1769/DefaultConfig/JoystickLeftButton.cpp
*********************************************************************/

#include "RXF_Active.h"
#include "JoystickLeftButton.h"
#include "JoystickLeftHandler.h"
//## package LPC1769::JoystickDriver::JoystickLeftIRQ

//## class JoystickLeftButton
JoystickLeftButton::JoystickLeftButton(bool isPressed, const std::uint8_t port, const std::uint8_t pin, RXF::Active* const activeContext) : isPressed(isPressed), itsDigitalInOut(port, pin), itsJoystickLeftHandler(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState) {
    setActiveContext(activeContext, false);
    
    //#[ operation JoystickLeftButton(bool,uint8_t,uint8_t)
    itsDigitalInOut.onInterrupt([&](uint32_t edge){
    if( ( (edge & Platform::BSP::DigitalInOut::EdgeType::FALLING_EDGE) && !this->isPressed)
    || ( (edge & Platform::BSP::DigitalInOut::EdgeType::RISING_EDGE) && this->isPressed) )
    {
    GEN(evJoystickLeftPressed());
    }
    else
    {
    GEN(evJoystickLeftReleased());
    }
    },
    Platform::BSP::DigitalInOut::EdgeType::ANY_EDGE);
    
    //#]
}

JoystickLeftButton::~JoystickLeftButton(void) {
    cleanUpRelations();
}

bool JoystickLeftButton::getIsPressed(void) const {
    return isPressed;
}

void JoystickLeftButton::setIsPressed(const bool p_isPressed) {
    isPressed = p_isPressed;
}

Platform::BSP::DigitalInOut* JoystickLeftButton::getItsDigitalInOut(void) const {
    return (Platform::BSP::DigitalInOut*) &itsDigitalInOut;
}

JoystickLeftHandler* JoystickLeftButton::getItsJoystickLeftHandler(void) const {
    return itsJoystickLeftHandler;
}

void JoystickLeftButton::setItsJoystickLeftHandler(JoystickLeftHandler* const p_JoystickLeftHandler) {
    itsJoystickLeftHandler = p_JoystickLeftHandler;
}

bool JoystickLeftButton::startBehavior(void) {
    bool done = true;
    if(done == true)
        {
            done = RXF::Reactive::startBehavior();
        }
    return done;
}

void JoystickLeftButton::cleanUpRelations(void) {
    if(itsJoystickLeftHandler != nullptr)
        {
            itsJoystickLeftHandler = nullptr;
        }
}

void JoystickLeftButton::send_evJoystickLeftPressed(void) {
    send( new evJoystickLeftPressed()  );
}

void JoystickLeftButton::send_evJoystickLeftReleased(void) {
    send( new evJoystickLeftReleased()  );
}

void JoystickLeftButton::rootState_entDef(void) {
    {
        rootState_subState = sReleased;
        rootState_active = sReleased;
    }
}

RXF::Reactive::TakeEventStatus JoystickLeftButton::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State sReleased
        case sReleased:
        {
            if(evJoystickLeftPressed_JoystickLeftIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 1 
                    itsJoystickLeftHandler->onClick();
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
            if(evJoystickLeftReleased_JoystickLeftIRQ_JoystickDriver_LPC1769_id == getCurrentEvent()->getId())
                {
                    //#[ transition 2 
                    itsJoystickLeftHandler->onReleased();
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
	File Path	: LPC1769/DefaultConfig/JoystickLeftButton.cpp
*********************************************************************/
