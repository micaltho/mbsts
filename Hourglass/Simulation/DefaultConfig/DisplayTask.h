/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: DisplayTask
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: Simulation/DefaultConfig/DisplayTask.h
*********************************************************************/

#ifndef DisplayTask_H
#define DisplayTask_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Application.h"
#include <oxf/omthread.h>
#include <oxf/omreactive.h>
#include <oxf/state.h>
#include <oxf/event.h>
#include <cstdint>
class Display;

//## package Application

//## class DisplayTask
class DisplayTask : public OMThread, public OMReactive {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedDisplayTask;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    //## operation DisplayTask(uint32_t)
    DisplayTask(const std::uint32_t updateTimeDisplay, IOxfActive* theActiveContext = 0);
    
    DisplayTask(IOxfActive* theActiveContext = 0);
    
    ~DisplayTask();
    
    ////    Operations    ////
    
    //## operation init()
    void init();
    
    //## operation updateDisplay(uint32_t,uint32_t,uint32_t,int32_t,int32_t,int32_t)
    void updateDisplay(const std::uint32_t update_mode, const std::uint32_t update_currentTime, const std::uint32_t update_configTime, const std::int32_t update_acc_X = 0, const std::int32_t update_acc_Y = 0, const std::int32_t update_acc_Z = 0);
    
    ////    Additional operations    ////
    
    std::int32_t getAcc_X() const;
    
    void setAcc_X(std::int32_t p_acc_X);
    
    std::int32_t getAcc_Y() const;
    
    void setAcc_Y(std::int32_t p_acc_Y);
    
    std::int32_t getAcc_Z() const;
    
    void setAcc_Z(std::int32_t p_acc_Z);
    
    std::uint32_t getConfigTime_ms() const;
    
    void setConfigTime_ms(std::uint32_t p_configTime_ms);
    
    std::uint32_t getCurrentTime_ms() const;
    
    void setCurrentTime_ms(std::uint32_t p_currentTime_ms);
    
    std::uint32_t getMode() const;
    
    void setMode(std::uint32_t p_mode);
    
    std::uint32_t getUpdateTimeDisplay() const;
    
    void setUpdateTimeDisplay(std::uint32_t p_updateTimeDisplay);
    
    Display* getItsDisplay() const;
    
    void setItsDisplay(Display* p_Display);
    
    virtual bool startBehavior();

protected :

    void initStatechart();
    
    void cleanUpRelations();
    
    void cancelTimeouts();
    
    bool cancelTimeout(const IOxfTimeout* arg);
    
    ////    Attributes    ////
    
    std::int32_t acc_X;		//## attribute acc_X
    
    std::int32_t acc_Y;		//## attribute acc_Y
    
    std::int32_t acc_Z;		//## attribute acc_Z
    
    std::uint32_t configTime_ms;		//## attribute configTime_ms
    
    std::uint32_t currentTime_ms;		//## attribute currentTime_ms
    
    std::uint32_t mode;		//## attribute mode
    
    std::uint32_t updateTimeDisplay;		//## attribute updateTimeDisplay
    
    ////    Relations and components    ////
    
    Display* itsDisplay;
    
    ////    Framework operations    ////

public :

    // rootState:
    inline bool rootState_IN() const;
    
    virtual void rootState_entDef();
    
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // Update:
    inline bool Update_IN() const;
    
    ////    Framework    ////

protected :

    enum DisplayTask_Enum {
        OMNonState = 0,
        Update = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
};

#ifdef _OMINSTRUMENT
class OMAnimatedDisplayTask : virtual public AOMInstance {
    DECLARE_REACTIVE_META(DisplayTask, OMAnimatedDisplayTask)
    
    ////    Framework operations    ////
    
public :

    virtual void serializeAttributes(AOMSAttributes* aomsAttributes) const;
    
    virtual void serializeRelations(AOMSRelations* aomsRelations) const;
    
    void rootState_serializeStates(AOMSState* aomsState) const;
    
    void Update_serializeStates(AOMSState* aomsState) const;
};
#endif // _OMINSTRUMENT

inline bool DisplayTask::rootState_IN() const {
    return true;
}

inline bool DisplayTask::Update_IN() const {
    return rootState_subState == Update;
}

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/DisplayTask.h
*********************************************************************/
