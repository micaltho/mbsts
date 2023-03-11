/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: DisplayTask
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: LPC1769/DefaultConfig/DisplayTask.cpp
*********************************************************************/

#include "DisplayTask.h"
#include "Display.h"
//## package Application

//## class DisplayTask
DisplayTask::DisplayTask(const std::uint32_t updateTimeDisplay) : RXF::Active("Active",RXF::Priority::NORMAL,1024U,10U,getQueueMemory()), acc_X(0), acc_Y(0), acc_Z(0), updateTimeDisplay(updateTimeDisplay), itsDisplay(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState), rootState_timeout(this) {
    setActiveContext(this, true);
    
    //#[ operation DisplayTask(uint32_t)
    //#]
}

DisplayTask::DisplayTask(void) : RXF::Active("Active",RXF::Priority::NORMAL,1024U,10U,getQueueMemory()), acc_X(0), acc_Y(0), acc_Z(0), itsDisplay(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState), rootState_timeout(this) {
    setActiveContext(this, true);
    
}

DisplayTask::~DisplayTask(void) {
    cleanUpRelations();
}

void DisplayTask::init(void) {
    //#[ operation init()
    //#]
}

void DisplayTask::updateDisplay(const std::uint32_t update_mode, const std::uint32_t update_currentTime, const std::uint32_t update_configTime, const std::int32_t update_acc_X, const std::int32_t update_acc_Y, const std::int32_t update_acc_Z) {
    //#[ operation updateDisplay(uint32_t,uint32_t,uint32_t,int32_t,int32_t,int32_t)
    mode = update_mode;
    currentTime_ms = update_currentTime;
    configTime_ms = update_configTime;
    acc_X = update_acc_X;
    acc_Y = update_acc_Y;
    acc_Z = update_acc_Z;
    //#]
}

std::int32_t DisplayTask::getAcc_X(void) const {
    return acc_X;
}

void DisplayTask::setAcc_X(const std::int32_t p_acc_X) {
    acc_X = p_acc_X;
}

std::int32_t DisplayTask::getAcc_Y(void) const {
    return acc_Y;
}

void DisplayTask::setAcc_Y(const std::int32_t p_acc_Y) {
    acc_Y = p_acc_Y;
}

std::int32_t DisplayTask::getAcc_Z(void) const {
    return acc_Z;
}

void DisplayTask::setAcc_Z(const std::int32_t p_acc_Z) {
    acc_Z = p_acc_Z;
}

std::uint32_t DisplayTask::getConfigTime_ms(void) const {
    return configTime_ms;
}

void DisplayTask::setConfigTime_ms(const std::uint32_t p_configTime_ms) {
    configTime_ms = p_configTime_ms;
}

std::uint32_t DisplayTask::getCurrentTime_ms(void) const {
    return currentTime_ms;
}

void DisplayTask::setCurrentTime_ms(const std::uint32_t p_currentTime_ms) {
    currentTime_ms = p_currentTime_ms;
}

std::uint32_t DisplayTask::getMode(void) const {
    return mode;
}

void DisplayTask::setMode(const std::uint32_t p_mode) {
    mode = p_mode;
}

std::uint32_t DisplayTask::getUpdateTimeDisplay(void) const {
    return updateTimeDisplay;
}

void DisplayTask::setUpdateTimeDisplay(const std::uint32_t p_updateTimeDisplay) {
    updateTimeDisplay = p_updateTimeDisplay;
}

Display* DisplayTask::getItsDisplay(void) const {
    return itsDisplay;
}

void DisplayTask::setItsDisplay(Display* const p_Display) {
    itsDisplay = p_Display;
}

bool DisplayTask::startBehavior(void) {
    bool done = false;
    done = RXF::Reactive::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void DisplayTask::cleanUpRelations(void) {
    if(itsDisplay != nullptr)
        {
            itsDisplay = nullptr;
        }
}

RXF::Event** DisplayTask::getQueueMemory(void) {
    return queueMemory;
}

void DisplayTask::rootState_entDef(void) {
    {
        //#[ transition 0 
        itsDisplay->init();
        //#]
        rootState_subState = Update;
        rootState_active = Update;
        rootState_timeout.start(updateTimeDisplay);
    }
}

RXF::Reactive::TakeEventStatus DisplayTask::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    // State Update
    if(rootState_active == Update)
        {
            if(RXF::Event::TIMEOUT_EVENT_ID == getCurrentEvent()->getId())
                {
                    if(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) )
                        {
                            rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                            //#[ transition 1 
                            itsDisplay->updateDisplay(mode, currentTime_ms, configTime_ms, acc_X, acc_Y, acc_Z);
                            //#]
                            rootState_subState = Update;
                            rootState_active = Update;
                            rootState_timeout.start(updateTimeDisplay);
                            res = eventConsumed;
                        }
                }
            
        }
    return res;
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/DisplayTask.cpp
*********************************************************************/
