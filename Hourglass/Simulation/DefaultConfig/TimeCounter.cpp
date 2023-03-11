/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: TimeCounter
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: Simulation/DefaultConfig/TimeCounter.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#define _OMSTATECHART_ANIMATED

#include "TimeCounter.h"
#define Application_TimeCounter_TimeCounter_SERIALIZE \
    aomsmethod->addAttribute("tickTimeHourglass", UNKNOWN2STRING(tickTimeHourglass));\
    aomsmethod->addAttribute("startTime_ms", UNKNOWN2STRING(startTime_ms));
#define OM_Application_TimeCounter_TimeCounter_1_SERIALIZE OM_NO_OP

#define Application_TimeCounter_getCurrentTime_ms_SERIALIZE OM_NO_OP

#define Application_TimeCounter_setCurrentTime_SERIALIZE aomsmethod->addAttribute("newCurrentTime", UNKNOWN2STRING(newCurrentTime));

#define Application_TimeCounter_setStartTime_ms_SERIALIZE aomsmethod->addAttribute("newStartTime_ms", UNKNOWN2STRING(newStartTime_ms));

#define Application_TimeCounter_tickBackward_SERIALIZE OM_NO_OP

#define Application_TimeCounter_tickForward_SERIALIZE OM_NO_OP

//## package Application

//## class TimeCounter
TimeCounter::TimeCounter(const std::uint32_t tickTimeHourglass, const std::uint32_t startTime_ms, IOxfActive* theActiveContext) : currentTime_ms(0), startTime_ms(startTime_ms)
 , tickTimeHourglass(tickTimeHourglass) {
    NOTIFY_ACTIVE_CONSTRUCTOR(TimeCounter, TimeCounter(const std::uint32_t,const std::uint32_t), 2, Application_TimeCounter_TimeCounter_SERIALIZE);
    setActiveContext(this, true);
    initStatechart();
    //#[ operation TimeCounter(uint32_t,uint32_t)
    //#]
}

TimeCounter::TimeCounter(IOxfActive* theActiveContext) : currentTime_ms(0) {
    NOTIFY_ACTIVE_CONSTRUCTOR(TimeCounter, TimeCounter(), 0, OM_Application_TimeCounter_TimeCounter_1_SERIALIZE);
    setActiveContext(this, true);
    initStatechart();
}

TimeCounter::~TimeCounter() {
    NOTIFY_DESTRUCTOR(~TimeCounter, true);
    cancelTimeouts();
}

std::uint32_t TimeCounter::getCurrentTime_ms() {
    NOTIFY_OPERATION(getCurrentTime_ms, getCurrentTime_ms(), 0, Application_TimeCounter_getCurrentTime_ms_SERIALIZE);
    //#[ operation getCurrentTime_ms()
    return currentTime_ms;
    //#]
}

void TimeCounter::setCurrentTime(const std::uint32_t newCurrentTime) {
    NOTIFY_OPERATION(setCurrentTime, setCurrentTime(const std::uint32_t), 1, Application_TimeCounter_setCurrentTime_SERIALIZE);
    //#[ operation setCurrentTime(uint32_t)
    currentTime_ms= newCurrentTime;
    //#]
}

void TimeCounter::setStartTime_ms(const std::uint32_t newStartTime_ms) {
    NOTIFY_OPERATION(setStartTime_ms, setStartTime_ms(const std::uint32_t), 1, Application_TimeCounter_setStartTime_ms_SERIALIZE);
    //#[ operation setStartTime_ms(uint32_t)
    startTime_ms = newStartTime_ms;
    //#]
}

void TimeCounter::tickBackward() {
    NOTIFY_OPERATION(tickBackward, tickBackward(), 0, Application_TimeCounter_tickBackward_SERIALIZE);
    // State action_0
    //#[ state tickBackward().action_0.(Entry) 
    currentTime_ms += tickTimeHourglass;
    //#]
    //#[ transition tickBackward().2 
    //#]
    if ( currentTime_ms >= startTime_ms )
    {
        // State action_1
        //#[ state tickBackward().action_1.(Entry) 
        currentTime_ms = startTime_ms;
        //#]
    }
    return;
    
}

void TimeCounter::tickForward() {
    NOTIFY_OPERATION(tickForward, tickForward(), 0, Application_TimeCounter_tickForward_SERIALIZE);
    // State action_0
    //#[ state tickForward().action_0.(Entry) 
    currentTime_ms -= tickTimeHourglass;
    //#]
    //#[ transition tickForward().1 
    //#]
    if ( currentTime_ms == 0 || currentTime_ms > startTime_ms  )
    {
        // State action_1
        //#[ state tickForward().action_1.(Entry) 
        currentTime_ms = 0;
        //#]
    }
    return;
    
}

void TimeCounter::setCurrentTime_ms(std::uint32_t p_currentTime_ms) {
    currentTime_ms = p_currentTime_ms;
}

std::uint32_t TimeCounter::getStartTime_ms() const {
    return startTime_ms;
}

std::uint32_t TimeCounter::getTickTimeHourglass() const {
    return tickTimeHourglass;
}

void TimeCounter::setTickTimeHourglass(std::uint32_t p_tickTimeHourglass) {
    tickTimeHourglass = p_tickTimeHourglass;
}

bool TimeCounter::startBehavior() {
    bool done = false;
    done = OMReactive::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void TimeCounter::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void TimeCounter::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool TimeCounter::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void TimeCounter::rootState_entDef() {
    {
        NOTIFY_STATE_ENTERED("ROOT");
        NOTIFY_TRANSITION_STARTED("0");
        NOTIFY_STATE_ENTERED("ROOT.InitialState");
        rootState_subState = InitialState;
        rootState_active = InitialState;
        //#[ state InitialState.(Entry) 
        currentTime_ms = startTime_ms;
        //#]
        NOTIFY_TRANSITION_TERMINATED("0");
    }
}

IOxfReactive::TakeEventStatus TimeCounter::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State runBackward
        case runBackward:
        {
            if(IS_EVENT_TYPE_OF(evStop_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("2");
                    cancel(rootState_timeout);
                    NOTIFY_STATE_EXITED("ROOT.runBackward");
                    NOTIFY_STATE_ENTERED("ROOT.Stop");
                    rootState_subState = Stop;
                    rootState_active = Stop;
                    NOTIFY_TRANSITION_TERMINATED("2");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            NOTIFY_TRANSITION_STARTED("10");
                            cancel(rootState_timeout);
                            NOTIFY_STATE_EXITED("ROOT.runBackward");
                            //#[ transition 10 
                            tickBackward();
                            //#]
                            NOTIFY_STATE_ENTERED("ROOT.runBackward");
                            rootState_subState = runBackward;
                            rootState_active = runBackward;
                            rootState_timeout = scheduleTimeout(tickTimeHourglass, "ROOT.runBackward");
                            NOTIFY_TRANSITION_TERMINATED("10");
                            res = eventConsumed;
                        }
                }
            else if(IS_EVENT_TYPE_OF(evResetTime_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("8");
                    cancel(rootState_timeout);
                    NOTIFY_STATE_EXITED("ROOT.runBackward");
                    NOTIFY_STATE_ENTERED("ROOT.InitialState");
                    rootState_subState = InitialState;
                    rootState_active = InitialState;
                    //#[ state InitialState.(Entry) 
                    currentTime_ms = startTime_ms;
                    //#]
                    NOTIFY_TRANSITION_TERMINATED("8");
                    res = eventConsumed;
                }
            
        }
        break;
        // State runForward
        case runForward:
        {
            if(IS_EVENT_TYPE_OF(evStop_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("5");
                    cancel(rootState_timeout);
                    NOTIFY_STATE_EXITED("ROOT.runForward");
                    NOTIFY_STATE_ENTERED("ROOT.Stop");
                    rootState_subState = Stop;
                    rootState_active = Stop;
                    NOTIFY_TRANSITION_TERMINATED("5");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            NOTIFY_TRANSITION_STARTED("11");
                            cancel(rootState_timeout);
                            NOTIFY_STATE_EXITED("ROOT.runForward");
                            //#[ transition 11 
                            tickForward();
                            //#]
                            NOTIFY_STATE_ENTERED("ROOT.runForward");
                            rootState_subState = runForward;
                            rootState_active = runForward;
                            rootState_timeout = scheduleTimeout(tickTimeHourglass, "ROOT.runForward");
                            NOTIFY_TRANSITION_TERMINATED("11");
                            res = eventConsumed;
                        }
                }
            else if(IS_EVENT_TYPE_OF(evResetTime_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("9");
                    cancel(rootState_timeout);
                    NOTIFY_STATE_EXITED("ROOT.runForward");
                    NOTIFY_STATE_ENTERED("ROOT.InitialState");
                    rootState_subState = InitialState;
                    rootState_active = InitialState;
                    //#[ state InitialState.(Entry) 
                    currentTime_ms = startTime_ms;
                    //#]
                    NOTIFY_TRANSITION_TERMINATED("9");
                    res = eventConsumed;
                }
            
        }
        break;
        // State Stop
        case Stop:
        {
            if(IS_EVENT_TYPE_OF(evRunBackward_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("3");
                    NOTIFY_STATE_EXITED("ROOT.Stop");
                    NOTIFY_STATE_ENTERED("ROOT.runBackward");
                    rootState_subState = runBackward;
                    rootState_active = runBackward;
                    rootState_timeout = scheduleTimeout(tickTimeHourglass, "ROOT.runBackward");
                    NOTIFY_TRANSITION_TERMINATED("3");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evResetTime_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("7");
                    NOTIFY_STATE_EXITED("ROOT.Stop");
                    NOTIFY_STATE_ENTERED("ROOT.InitialState");
                    rootState_subState = InitialState;
                    rootState_active = InitialState;
                    //#[ state InitialState.(Entry) 
                    currentTime_ms = startTime_ms;
                    //#]
                    NOTIFY_TRANSITION_TERMINATED("7");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evRunForward_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("4");
                    NOTIFY_STATE_EXITED("ROOT.Stop");
                    NOTIFY_STATE_ENTERED("ROOT.runForward");
                    rootState_subState = runForward;
                    rootState_active = runForward;
                    rootState_timeout = scheduleTimeout(tickTimeHourglass, "ROOT.runForward");
                    NOTIFY_TRANSITION_TERMINATED("4");
                    res = eventConsumed;
                }
            
        }
        break;
        // State InitialState
        case InitialState:
        {
            if(IS_EVENT_TYPE_OF(evRunBackward_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("1");
                    NOTIFY_STATE_EXITED("ROOT.InitialState");
                    NOTIFY_STATE_ENTERED("ROOT.runBackward");
                    rootState_subState = runBackward;
                    rootState_active = runBackward;
                    rootState_timeout = scheduleTimeout(tickTimeHourglass, "ROOT.runBackward");
                    NOTIFY_TRANSITION_TERMINATED("1");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evRunForward_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("6");
                    NOTIFY_STATE_EXITED("ROOT.InitialState");
                    NOTIFY_STATE_ENTERED("ROOT.runForward");
                    rootState_subState = runForward;
                    rootState_active = runForward;
                    rootState_timeout = scheduleTimeout(tickTimeHourglass, "ROOT.runForward");
                    NOTIFY_TRANSITION_TERMINATED("6");
                    res = eventConsumed;
                }
            
        }
        break;
        default:
            break;
    }
    return res;
}

#ifdef _OMINSTRUMENT
void OMAnimatedTimeCounter::serializeAttributes(AOMSAttributes* aomsAttributes) const {
    aomsAttributes->addAttribute("tickTimeHourglass", UNKNOWN2STRING(myReal->tickTimeHourglass));
    aomsAttributes->addAttribute("currentTime_ms", UNKNOWN2STRING(myReal->currentTime_ms));
    aomsAttributes->addAttribute("startTime_ms", UNKNOWN2STRING(myReal->startTime_ms));
}

void OMAnimatedTimeCounter::rootState_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT");
    switch (myReal->rootState_subState) {
        case TimeCounter::runBackward:
        {
            runBackward_serializeStates(aomsState);
        }
        break;
        case TimeCounter::runForward:
        {
            runForward_serializeStates(aomsState);
        }
        break;
        case TimeCounter::Stop:
        {
            Stop_serializeStates(aomsState);
        }
        break;
        case TimeCounter::InitialState:
        {
            InitialState_serializeStates(aomsState);
        }
        break;
        default:
            break;
    }
}

void OMAnimatedTimeCounter::Stop_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.Stop");
}

void OMAnimatedTimeCounter::runForward_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.runForward");
}

void OMAnimatedTimeCounter::runBackward_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.runBackward");
}

void OMAnimatedTimeCounter::InitialState_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.InitialState");
}

IMPLEMENT_REACTIVE_META_P(TimeCounter, Application, Application, false, OMAnimatedTimeCounter)
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/TimeCounter.cpp
*********************************************************************/
