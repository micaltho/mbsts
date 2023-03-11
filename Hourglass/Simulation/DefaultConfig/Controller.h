/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: Controller
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/Controller.h
*********************************************************************/

#ifndef Controller_H
#define Controller_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Application.h"
#include <oxf/omthread.h>
#include <oxf/omreactive.h>
#include <oxf/state.h>
#include <oxf/event.h>
#include <cstdint>
class AccelerationMeasuring;

class ConfigStorage;

class DisplayTask;

class TimeCounter;

//## package Application

//## class Controller
class Controller : public OMThread, public OMReactive {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedController;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    //## operation Controller(uint32_t,uint32_t,uint32_t)
    Controller(const std::uint32_t defaultStartTime, const std::uint32_t tickTimeController, const std::uint32_t timeFactor, IOxfActive* theActiveContext = 0);
    
    Controller(IOxfActive* theActiveContext = 0);
    
    ~Controller();
    
    ////    Operations    ////
    
    void raiseStartTime();
    
    void raiseTimeFactor();
    
    void reduceStartTime();
    
    void reduceTimeFactor();
    
    //## operation setTime(uint32_t)
    void setTime(const std::uint32_t newTime_ms);
    
    ////    Additional operations    ////
    
    std::int32_t getBackward_threshold() const;
    
    void setBackward_threshold(std::int32_t p_backward_threshold);
    
    std::int32_t getForward_threshold() const;
    
    void setForward_threshold(std::int32_t p_forward_threshold);
    
    std::uint32_t getStartTime() const;
    
    void setStartTime(std::uint32_t p_startTime);
    
    std::uint32_t getTickTimeController() const;
    
    void setTickTimeController(std::uint32_t p_tickTimeController);
    
    std::uint32_t getTimeFactor() const;
    
    void setTimeFactor(std::uint32_t p_timeFactor);
    
    AccelerationMeasuring* getItsAccelerationMeasuring() const;
    
    void setItsAccelerationMeasuring(AccelerationMeasuring* p_AccelerationMeasuring);
    
    ConfigStorage* getItsConfigStorage() const;
    
    void setItsConfigStorage(ConfigStorage* p_ConfigStorage);
    
    DisplayTask* getItsDisplayTask() const;
    
    void setItsDisplayTask(DisplayTask* p_DisplayTask);
    
    TimeCounter* getItsTimeCounter() const;
    
    void setItsTimeCounter(TimeCounter* p_TimeCounter);
    
    virtual bool startBehavior();

protected :

    void initStatechart();
    
    void cleanUpRelations();
    
    void cancelTimeouts();
    
    bool cancelTimeout(const IOxfTimeout* arg);
    
    ////    Attributes    ////
    
    std::int32_t backward_threshold;		//## attribute backward_threshold
    
    std::int32_t forward_threshold;		//## attribute forward_threshold
    
    std::uint32_t startTime;		//## attribute startTime
    
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
    inline bool rootState_IN() const;
    
    virtual void rootState_entDef();
    
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // RunHourglass:
    inline bool RunHourglass_IN() const;
    
    IOxfReactive::TakeEventStatus RunHourglass_handleEvent();
    
    // Menu:
    inline bool Menu_IN() const;
    
    IOxfReactive::TakeEventStatus Menu_handleEvent();
    
    // changeTimeFactor:
    inline bool changeTimeFactor_IN() const;
    
    // changeStartTime:
    inline bool changeStartTime_IN() const;
    
    // accelerometerSettings:
    inline bool accelerometerSettings_IN() const;
    
    ////    Framework    ////

protected :

    enum Controller_Enum {
        OMNonState = 0,
        RunHourglass = 1,
        Menu = 2,
        changeTimeFactor = 3,
        changeStartTime = 4,
        accelerometerSettings = 5
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
};

#ifdef _OMINSTRUMENT
class OMAnimatedController : virtual public AOMInstance {
    DECLARE_REACTIVE_META(Controller, OMAnimatedController)
    
    ////    Framework operations    ////
    
public :

    virtual void serializeAttributes(AOMSAttributes* aomsAttributes) const;
    
    virtual void serializeRelations(AOMSRelations* aomsRelations) const;
    
    void rootState_serializeStates(AOMSState* aomsState) const;
    
    void RunHourglass_serializeStates(AOMSState* aomsState) const;
    
    void Menu_serializeStates(AOMSState* aomsState) const;
    
    void changeTimeFactor_serializeStates(AOMSState* aomsState) const;
    
    void changeStartTime_serializeStates(AOMSState* aomsState) const;
    
    void accelerometerSettings_serializeStates(AOMSState* aomsState) const;
};
#endif // _OMINSTRUMENT

inline bool Controller::rootState_IN() const {
    return true;
}

inline bool Controller::RunHourglass_IN() const {
    return rootState_subState == RunHourglass;
}

inline bool Controller::Menu_IN() const {
    return rootState_subState == Menu;
}

inline bool Controller::changeTimeFactor_IN() const {
    return rootState_subState == changeTimeFactor;
}

inline bool Controller::changeStartTime_IN() const {
    return rootState_subState == changeStartTime;
}

inline bool Controller::accelerometerSettings_IN() const {
    return rootState_subState == accelerometerSettings;
}

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/Controller.h
*********************************************************************/
