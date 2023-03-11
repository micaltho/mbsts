/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: TimeCounter
//!	Generated Date	: Thu, 18, Aug 2022  
	File Path	: LPC1769/DefaultConfig/TimeCounter.h
*********************************************************************/

#ifndef TimeCounter_H
#define TimeCounter_H

#include "Application.h"
#include "RXF_Active.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <cstdint>
//## package Application

//## class TimeCounter
class TimeCounter : public RXF::Active, public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation TimeCounter(uint32_t)
    TimeCounter(const std::uint32_t tickTimeHourglass);
    
    TimeCounter(void);
    
    virtual ~TimeCounter(void);
    
    ////    Operations    ////
    
    //## operation getCurrentTime_ms()
    std::uint32_t getCurrentTime_ms(void);
    
    //## operation setCurrentTime(uint32_t)
    void setCurrentTime(const std::uint32_t newCurrentTime);
    
    //## operation setStartTime_ms(uint32_t)
    void setStartTime_ms(const std::uint32_t newStartTime_ms);
    
    void tickBackward(void);
    
    void tickForward(void);
    
    ////    Additional operations    ////
    
    void setCurrentTime_ms(const std::uint32_t p_currentTime_ms);
    
    std::uint32_t getStartTime_ms(void) const;
    
    std::uint32_t getTickTimeHourglass(void) const;
    
    void setTickTimeHourglass(const std::uint32_t p_tickTimeHourglass);
    
    virtual bool startBehavior(void);

public :

    virtual void send_evRunBackward(void);
    
    virtual void send_evRunForward(void);
    
    virtual void send_evStop(void);
    
    virtual void send_evResetTime(void);
    
    virtual void send_evStart(void);

private :

    RXF::Event** getQueueMemory(void);
    
    ////    Attributes    ////

protected :

    std::uint32_t currentTime_ms;		//## attribute currentTime_ms
    
    std::uint32_t startTime_ms;		//## attribute startTime_ms
    
    std::uint32_t tickTimeHourglass;		//## attribute tickTimeHourglass
    
    ////    Framework operations    ////

public :

    // rootState:
    inline bool rootState_IN(void) const;
    
    // Stop:
    inline bool Stop_IN(void) const;
    
    // state_4:
    inline bool state_4_IN(void) const;
    
    // runForward:
    inline bool runForward_IN(void) const;
    
    // runBackward:
    inline bool runBackward_IN(void) const;
    
    // InitialState:
    inline bool InitialState_IN(void) const;

protected :

    virtual void rootState_entDef(void);
    
    virtual RXF::Reactive::TakeEventStatus rootState_processEvent(void);
    
    ////    Framework    ////
    
    enum TimeCounter_Enum {
        OMNonState = 0,
        Stop = 1,
        state_4 = 2,
        runForward = 3,
        runBackward = 4,
        InitialState = 5
    };

private :

    TimeCounter_Enum rootState_subState;
    
    TimeCounter_Enum rootState_active;
    
    RXF::TimeoutEvent rootState_timeout;
    
    RXF::Event* queueMemory[10U];
};

inline bool TimeCounter::rootState_IN(void) const {
    return true;
}

inline bool TimeCounter::Stop_IN(void) const {
    return rootState_subState == Stop;
}

inline bool TimeCounter::state_4_IN(void) const {
    return rootState_subState == state_4;
}

inline bool TimeCounter::runForward_IN(void) const {
    return rootState_subState == runForward;
}

inline bool TimeCounter::runBackward_IN(void) const {
    return rootState_subState == runBackward;
}

inline bool TimeCounter::InitialState_IN(void) const {
    return rootState_subState == InitialState;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/TimeCounter.h
*********************************************************************/
