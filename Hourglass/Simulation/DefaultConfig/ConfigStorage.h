/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: ConfigStorage
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/ConfigStorage.h
*********************************************************************/

#ifndef ConfigStorage_H
#define ConfigStorage_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Application.h"
#include <oxf/omthread.h>
#include <oxf/omreactive.h>
#include <oxf/state.h>
#include <oxf/event.h>
#include <cstdint>
class EepromData;

//## package Application

//## class ConfigStorage
class ConfigStorage : public OMReactive {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedConfigStorage;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    ConfigStorage(IOxfActive* theActiveContext = 0);
    
    ~ConfigStorage();
    
    ////    Operations    ////
    
    //## operation getConfigdata()
    std::uint8_t getConfigdata();
    
    //## operation setConfigdata(uint8_t)
    void setConfigdata(const std::uint8_t update_LastStartTime);
    
    ////    Additional operations    ////
    
    std::uint8_t getLastStartTime() const;
    
    void setLastStartTime(std::uint8_t p_LastStartTime);
    
    EepromData* getItsEepromData() const;
    
    void setItsEepromData(EepromData* p_EepromData);
    
    virtual bool startBehavior();

protected :

    void initStatechart();
    
    void cleanUpRelations();
    
    ////    Attributes    ////
    
    std::uint8_t LastStartTime;		//## attribute LastStartTime
    
    ////    Relations and components    ////
    
    EepromData* itsEepromData;
    
    ////    Framework operations    ////

public :

    // rootState:
    inline bool rootState_IN() const;
    
    virtual void rootState_entDef();
    
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // InitialState:
    inline bool InitialState_IN() const;
    
    ////    Framework    ////

protected :

    enum ConfigStorage_Enum {
        OMNonState = 0,
        InitialState = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
};

#ifdef _OMINSTRUMENT
class OMAnimatedConfigStorage : virtual public AOMInstance {
    DECLARE_REACTIVE_META(ConfigStorage, OMAnimatedConfigStorage)
    
    ////    Framework operations    ////
    
public :

    virtual void serializeAttributes(AOMSAttributes* aomsAttributes) const;
    
    virtual void serializeRelations(AOMSRelations* aomsRelations) const;
    
    void rootState_serializeStates(AOMSState* aomsState) const;
    
    void InitialState_serializeStates(AOMSState* aomsState) const;
};
#endif // _OMINSTRUMENT

inline bool ConfigStorage::rootState_IN() const {
    return true;
}

inline bool ConfigStorage::InitialState_IN() const {
    return rootState_subState == InitialState;
}

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/ConfigStorage.h
*********************************************************************/
