/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: TimeCounter
//!	Generated Date	: Mon, 1, Aug 2022  
	File Path	: Simulation/DefaultConfig/TimeCounter.h
*********************************************************************/

#ifndef TimeCounter_H
#define TimeCounter_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Application.h"
#include <oxf/omthread.h>
#include <oxf/omreactive.h>
#include <oxf/state.h>
#include <oxf/event.h>
#include <cstdint>
//## package Application

//## class TimeCounter
class TimeCounter : public OMThread, public OMReactive {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedTimeCounter;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    //## operation TimeCounter(uint32_t,uint32_t)
    TimeCounter(const std::uint32_t tickTimeHourglass, const std::uint32_t startTime_ms, IOxfActive* theActiveContext = 0);
    
    TimeCounter(IOxfActive* theActiveContext = 0);
    
    ~TimeCounter();
    
    ////    Operations    ////
    
    //## operation getCurrentTime_ms()
    std::uint32_t getCurrentTime_ms();
    
    //## operation setCurrentTime(uint32_t)
    void setCurrentTime(const std::uint32_t newCurrentTime);
    
    //## operation setStartTime_ms(uint32_t)
    void setStartTime_ms(const std::uint32_t newStartTime_ms);
    
    void tickBackward();
    
    void tickForward();
    
    ////    Additional operations    ////
    
    void setCurrentTime_ms(std::uint32_t p_currentTime_ms);
    
    std::uint32_t getStartTime_ms() const;
    
    std::uint32_t getTickTimeHourglass() const;
    
    void setTickTimeHourglass(std::uint32_t p_tickTimeHourglass);
    
    virtual bool startBehavior();

protected :

    void initStatechart();
    
    void cancelTimeouts();
    
    bool cancelTimeout(const IOxfTimeout* arg);
    
    ////    Attributes    ////
    
    std::uint32_t currentTime_ms;		//## attribute currentTime_ms
    
    std::uint32_t startTime_ms;		//## attribute startTime_ms
    
    std::uint32_t tickTimeHourglass;		//## attribute tickTimeHourglass
    
    ////    Framework operations    ////

public :

    // rootState:
    inline bool rootState_IN() const;
    
    virtual void rootState_entDef();
    
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // Stop:
    inline bool Stop_IN() const;
    
    // runForward:
    inline bool runForward_IN() const;
    
    // runBackward:
    inline bool runBackward_IN() const;
    
    // InitialState:
    inline bool InitialState_IN() const;
    
    ////    Framework    ////

protected :

    enum TimeCounter_Enum {
        OMNonState = 0,
        Stop = 1,
        runForward = 2,
        runBackward = 3,
        InitialState = 4
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
};

#ifdef _OMINSTRUMENT
class OMAnimatedTimeCounter : virtual public AOMInstance {
    DECLARE_REACTIVE_META(TimeCounter, OMAnimatedTimeCounter)
    
    ////    Framework operations    ////
    
public :

    virtual void serializeAttributes(AOMSAttributes* aomsAttributes) const;
    
    void rootState_serializeStates(AOMSState* aomsState) const;
    
    void Stop_serializeStates(AOMSState* aomsState) const;
    
    void runForward_serializeStates(AOMSState* aomsState) const;
    
    void runBackward_serializeStates(AOMSState* aomsState) const;
    
    void InitialState_serializeStates(AOMSState* aomsState) const;
};
#endif // _OMINSTRUMENT

inline bool TimeCounter::rootState_IN() const {
    return true;
}

inline bool TimeCounter::Stop_IN() const {
    return rootState_subState == Stop;
}

inline bool TimeCounter::runForward_IN() const {
    return rootState_subState == runForward;
}

inline bool TimeCounter::runBackward_IN() const {
    return rootState_subState == runBackward;
}

inline bool TimeCounter::InitialState_IN() const {
    return rootState_subState == InitialState;
}

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/TimeCounter.h
*********************************************************************/
