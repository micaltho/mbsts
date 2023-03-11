/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: DisplayTask
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: LPC1769/DefaultConfig/DisplayTask.h
*********************************************************************/

#ifndef DisplayTask_H
#define DisplayTask_H

#include "Application.h"
#include "RXF_Active.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <cstdint>
class Display;

//## package Application

//## class DisplayTask
class DisplayTask : public RXF::Active, public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation DisplayTask(uint32_t)
    DisplayTask(const std::uint32_t updateTimeDisplay);
    
    DisplayTask(void);
    
    virtual ~DisplayTask(void);
    
    ////    Operations    ////
    
    //## operation init()
    void init(void);
    
    //## operation updateDisplay(uint32_t,uint32_t,uint32_t,int32_t,int32_t,int32_t)
    void updateDisplay(const std::uint32_t update_mode, const std::uint32_t update_currentTime, const std::uint32_t update_configTime, const std::int32_t update_acc_X = 0, const std::int32_t update_acc_Y = 0, const std::int32_t update_acc_Z = 0);
    
    ////    Additional operations    ////
    
    std::int32_t getAcc_X(void) const;
    
    void setAcc_X(const std::int32_t p_acc_X);
    
    std::int32_t getAcc_Y(void) const;
    
    void setAcc_Y(const std::int32_t p_acc_Y);
    
    std::int32_t getAcc_Z(void) const;
    
    void setAcc_Z(const std::int32_t p_acc_Z);
    
    std::uint32_t getConfigTime_ms(void) const;
    
    void setConfigTime_ms(const std::uint32_t p_configTime_ms);
    
    std::uint32_t getCurrentTime_ms(void) const;
    
    void setCurrentTime_ms(const std::uint32_t p_currentTime_ms);
    
    std::uint32_t getMode(void) const;
    
    void setMode(const std::uint32_t p_mode);
    
    std::uint32_t getUpdateTimeDisplay(void) const;
    
    void setUpdateTimeDisplay(const std::uint32_t p_updateTimeDisplay);
    
    Display* getItsDisplay(void) const;
    
    void setItsDisplay(Display* const p_Display);
    
    virtual bool startBehavior(void);

protected :

    void cleanUpRelations(void);

private :

    RXF::Event** getQueueMemory(void);
    
    ////    Attributes    ////

protected :

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
    inline bool rootState_IN(void) const;
    
    // Update:
    inline bool Update_IN(void) const;

protected :

    virtual void rootState_entDef(void);
    
    virtual RXF::Reactive::TakeEventStatus rootState_processEvent(void);
    
    ////    Framework    ////
    
    enum DisplayTask_Enum {
        OMNonState = 0,
        Update = 1
    };

private :

    DisplayTask_Enum rootState_subState;
    
    DisplayTask_Enum rootState_active;
    
    RXF::TimeoutEvent rootState_timeout;
    
    RXF::Event* queueMemory[10U];
};

inline bool DisplayTask::rootState_IN(void) const {
    return true;
}

inline bool DisplayTask::Update_IN(void) const {
    return rootState_subState == Update;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/DisplayTask.h
*********************************************************************/
