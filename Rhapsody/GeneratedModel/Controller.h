/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: Controller
//!	Generated Date	: Wed, 31, Aug 2022  
	File Path	: LPC1769/DefaultConfig/Controller.h
*********************************************************************/

#ifndef Controller_H
#define Controller_H

#include "Application.h"
#include "RXF_Active.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <cstdint>
class AccelerationMeasuring;

class ConfigStorage;

class DisplayTask;

class TimeCounter;

//## package Application

//## class Controller
class Controller : public RXF::Active, public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation Controller(uint32_t,uint32_t,uint32_t)
    Controller(const std::uint32_t defaultStartTime, const std::uint32_t tickTimeController, const std::uint32_t timeFactor);
    
    Controller(void);
    
    virtual ~Controller(void);
    
    ////    Operations    ////
    
    void raiseStartTime(void);
    
    void raiseTimeFactor(void);
    
    void reduceStartTime(void);
    
    void reduceTimeFactor(void);
    
    //## operation setTime(uint32_t)
    void setTime(const std::uint32_t newTime_ms);
    
    ////    Additional operations    ////
    
    std::int32_t getBackward_threshold(void) const;
    
    void setBackward_threshold(const std::int32_t p_backward_threshold);
    
    std::int32_t getForward_threshold(void) const;
    
    void setForward_threshold(const std::int32_t p_forward_threshold);
    
    std::uint32_t getStartTime(void) const;
    
    void setStartTime(const std::uint32_t p_startTime);
    
    std::uint8_t getStartTimeTest(void) const;
    
    void setStartTimeTest(const std::uint8_t p_startTimeTest);
    
    std::uint32_t getStartTimemax(void) const;
    
    void setStartTimemax(const std::uint32_t p_startTimemax);
    
    std::uint32_t getStartTimemin(void) const;
    
    void setStartTimemin(const std::uint32_t p_startTimemin);
    
    std::uint32_t getTickTimeController(void) const;
    
    void setTickTimeController(const std::uint32_t p_tickTimeController);
    
    std::uint32_t getTimeFactor(void) const;
    
    void setTimeFactor(const std::uint32_t p_timeFactor);
    
    AccelerationMeasuring* getItsAccelerationMeasuring(void) const;
    
    void setItsAccelerationMeasuring(AccelerationMeasuring* const p_AccelerationMeasuring);
    
    ConfigStorage* getItsConfigStorage(void) const;
    
    void setItsConfigStorage(ConfigStorage* const p_ConfigStorage);
    
    DisplayTask* getItsDisplayTask(void) const;
    
    void setItsDisplayTask(DisplayTask* const p_DisplayTask);
    
    TimeCounter* getItsTimeCounter(void) const;
    
    void setItsTimeCounter(TimeCounter* const p_TimeCounter);
    
    virtual bool startBehavior(void);

protected :

    void cleanUpRelations(void);

public :

    virtual void send_evMenu(void);
    
    virtual void send_evMenuExit(void);
    
    virtual void send_evRaiseStartTime(void);
    
    virtual void send_evReduceStartTime(void);
    
    virtual void send_evRaiseTimeFactor(void);
    
    virtual void send_evReduceTimeFactor(void);
    
    virtual void send_evStartTimeSetting(void);
    
    virtual void send_evTimeFactorSetting(void);
    
    virtual void send_evGoBack(void);
    
    virtual void send_evReset(void);
    
    virtual void send_evCalibrate(void);
    
    virtual void send_evGoBackToRunHourglass(void);
    
    virtual void send_evResetTime(void);

private :

    RXF::Event** getQueueMemory(void);
    
    ////    Attributes    ////

protected :

    std::int32_t backward_threshold;		//## attribute backward_threshold
    
    std::int32_t forward_threshold;		//## attribute forward_threshold
    
    std::uint32_t startTime;		//## attribute startTime
    
    std::uint8_t startTimeTest;		//## attribute startTimeTest
    
    std::uint32_t startTimemax;		//## attribute startTimemax
    
    std::uint32_t startTimemin;		//## attribute startTimemin
    
    std::uint32_t tickTimeController;		//## attribute tickTimeController
    
    std::uint32_t timeFactor;		//## attribute timeFactor
    
    ////    Relations and components    ////
    
    AccelerationMeasuring* itsAccelerationMeasuring;
    
    ConfigStorage* itsConfigStorage;
    
    DisplayTask* itsDisplayTask;
    
    TimeCounter* itsTimeCounter;
    
    ////    Framework operations    ////

public :

    // rootState:
    inline bool rootState_IN(void) const;
    
    // RunHourglass:
    inline bool RunHourglass_IN(void) const;
    
    // Menu:
    inline bool Menu_IN(void) const;
    
    // changeTimeFactor:
    inline bool changeTimeFactor_IN(void) const;
    
    // changeStartTime:
    inline bool changeStartTime_IN(void) const;
    
    // accelerometerSettings:
    inline bool accelerometerSettings_IN(void) const;

protected :

    virtual void rootState_entDef(void);
    
    virtual RXF::Reactive::TakeEventStatus rootState_processEvent(void);
    
    ////    Framework    ////
    
    enum Controller_Enum {
        OMNonState = 0,
        RunHourglass = 1,
        Menu = 2,
        changeTimeFactor = 3,
        changeStartTime = 4,
        accelerometerSettings = 5
    };

private :

    Controller_Enum rootState_subState;
    
    Controller_Enum rootState_active;
    
    RXF::TimeoutEvent rootState_timeout;
    
    RXF::Event* queueMemory[10U];
};

inline bool Controller::rootState_IN(void) const {
    return true;
}

inline bool Controller::RunHourglass_IN(void) const {
    return rootState_subState == RunHourglass;
}

inline bool Controller::Menu_IN(void) const {
    return rootState_subState == Menu;
}

inline bool Controller::changeTimeFactor_IN(void) const {
    return rootState_subState == changeTimeFactor;
}

inline bool Controller::changeStartTime_IN(void) const {
    return rootState_subState == changeStartTime;
}

inline bool Controller::accelerometerSettings_IN(void) const {
    return rootState_subState == accelerometerSettings;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/Controller.h
*********************************************************************/
