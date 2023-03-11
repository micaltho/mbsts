/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: TimeCounter
//!	Generated Date	: Thu, 18, Aug 2022  
	File Path	: LPC1769/DefaultConfig/TimeCounter.cpp
*********************************************************************/

#include "TimeCounter.h"
//## package Application

//## class TimeCounter
TimeCounter::TimeCounter(const std::uint32_t tickTimeHourglass) : RXF::Active("Active",RXF::Priority::NORMAL,1024U,10U,getQueueMemory()), currentTime_ms(0), tickTimeHourglass(tickTimeHourglass)
 , rootState_subState(OMNonState), rootState_active(OMNonState), rootState_timeout(this) {
    setActiveContext(this, true);
    
    //#[ operation TimeCounter(uint32_t)
    //#]
}

TimeCounter::TimeCounter(void) : RXF::Active("Active",RXF::Priority::NORMAL,1024U,10U,getQueueMemory()), currentTime_ms(0), rootState_subState(OMNonState), rootState_active(OMNonState), rootState_timeout(this) {
    setActiveContext(this, true);
    
}

TimeCounter::~TimeCounter(void) {
}

std::uint32_t TimeCounter::getCurrentTime_ms(void) {
    //#[ operation getCurrentTime_ms()
    return currentTime_ms;
    //#]
}

void TimeCounter::setCurrentTime(const std::uint32_t newCurrentTime) {
    //#[ operation setCurrentTime(uint32_t)
    currentTime_ms= newCurrentTime;
    //#]
}

void TimeCounter::setStartTime_ms(const std::uint32_t newStartTime_ms) {
    //#[ operation setStartTime_ms(uint32_t)
    startTime_ms = newStartTime_ms;
    //#]
}

void TimeCounter::tickBackward(void) {
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

void TimeCounter::tickForward(void) {
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

void TimeCounter::setCurrentTime_ms(const std::uint32_t p_currentTime_ms) {
    currentTime_ms = p_currentTime_ms;
}

std::uint32_t TimeCounter::getStartTime_ms(void) const {
    return startTime_ms;
}

std::uint32_t TimeCounter::getTickTimeHourglass(void) const {
    return tickTimeHourglass;
}

void TimeCounter::setTickTimeHourglass(const std::uint32_t p_tickTimeHourglass) {
    tickTimeHourglass = p_tickTimeHourglass;
}

bool TimeCounter::startBehavior(void) {
    bool done = false;
    done = RXF::Reactive::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void TimeCounter::send_evRunBackward(void) {
    send( new evRunBackward()  );
}

void TimeCounter::send_evRunForward(void) {
    send( new evRunForward()  );
}

void TimeCounter::send_evStop(void) {
    send( new evStop()  );
}

void TimeCounter::send_evResetTime(void) {
    send( new evResetTime()  );
}

void TimeCounter::send_evStart(void) {
    send( new evStart()  );
}

RXF::Event** TimeCounter::getQueueMemory(void) {
    return queueMemory;
}

void TimeCounter::rootState_entDef(void) {
    {
        rootState_subState = state_4;
        rootState_active = state_4;
    }
}

RXF::Reactive::TakeEventStatus TimeCounter::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State runBackward
        case runBackward:
        {
            if(evStop_Application_id == getCurrentEvent()->getId())
                {
                    rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                    rootState_subState = Stop;
                    rootState_active = Stop;
                    res = eventConsumed;
                }
            else {
                if(RXF::Event::TIMEOUT_EVENT_ID == getCurrentEvent()->getId())
                    {
                        if(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) )
                            {
                                rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                                //#[ transition 10 
                                tickBackward();
                                //#]
                                rootState_subState = runBackward;
                                rootState_active = runBackward;
                                rootState_timeout.start(tickTimeHourglass);
                                res = eventConsumed;
                            }
                    }
                else {
                    if(evResetTime_Application_id == getCurrentEvent()->getId())
                        {
                            rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                            rootState_subState = InitialState;
                            rootState_active = InitialState;
                            //#[ state InitialState.(Entry) 
                            currentTime_ms = startTime_ms;
                            //#]
                            res = eventConsumed;
                        }
                    }
                    
                }
                
            
        }
        break;
        // State runForward
        case runForward:
        {
            if(evStop_Application_id == getCurrentEvent()->getId())
                {
                    rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                    rootState_subState = Stop;
                    rootState_active = Stop;
                    res = eventConsumed;
                }
            else {
                if(RXF::Event::TIMEOUT_EVENT_ID == getCurrentEvent()->getId())
                    {
                        if(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) )
                            {
                                rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                                //#[ transition 11 
                                tickForward();
                                //#]
                                rootState_subState = runForward;
                                rootState_active = runForward;
                                rootState_timeout.start(tickTimeHourglass);
                                res = eventConsumed;
                            }
                    }
                else {
                    if(evResetTime_Application_id == getCurrentEvent()->getId())
                        {
                            rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                            rootState_subState = InitialState;
                            rootState_active = InitialState;
                            //#[ state InitialState.(Entry) 
                            currentTime_ms = startTime_ms;
                            //#]
                            res = eventConsumed;
                        }
                    }
                    
                }
                
            
        }
        break;
        // State Stop
        case Stop:
        {
            if(evRunBackward_Application_id == getCurrentEvent()->getId())
                {
                    rootState_subState = runBackward;
                    rootState_active = runBackward;
                    rootState_timeout.start(tickTimeHourglass);
                    res = eventConsumed;
                }
            else {
                if(evResetTime_Application_id == getCurrentEvent()->getId())
                    {
                        rootState_subState = InitialState;
                        rootState_active = InitialState;
                        //#[ state InitialState.(Entry) 
                        currentTime_ms = startTime_ms;
                        //#]
                        res = eventConsumed;
                    }
                else {
                    if(evRunForward_Application_id == getCurrentEvent()->getId())
                        {
                            rootState_subState = runForward;
                            rootState_active = runForward;
                            rootState_timeout.start(tickTimeHourglass);
                            res = eventConsumed;
                        }
                    }
                    
                }
                
            
        }
        break;
        // State InitialState
        case InitialState:
        {
            if(evRunBackward_Application_id == getCurrentEvent()->getId())
                {
                    rootState_subState = runBackward;
                    rootState_active = runBackward;
                    rootState_timeout.start(tickTimeHourglass);
                    res = eventConsumed;
                }
            else {
                if(evRunForward_Application_id == getCurrentEvent()->getId())
                    {
                        rootState_subState = runForward;
                        rootState_active = runForward;
                        rootState_timeout.start(tickTimeHourglass);
                        res = eventConsumed;
                    }
                }
                
            
        }
        break;
        // State state_4
        case state_4:
        {
            if(evStart_Application_id == getCurrentEvent()->getId())
                {
                    //#[ transition 12 
                    currentTime_ms = startTime_ms;
                    //#]
                    rootState_subState = InitialState;
                    rootState_active = InitialState;
                    //#[ state InitialState.(Entry) 
                    currentTime_ms = startTime_ms;
                    //#]
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
	File Path	: LPC1769/DefaultConfig/TimeCounter.cpp
*********************************************************************/
