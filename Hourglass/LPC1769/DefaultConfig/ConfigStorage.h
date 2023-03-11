/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: ConfigStorage
//!	Generated Date	: Wed, 17, Aug 2022  
	File Path	: LPC1769/DefaultConfig/ConfigStorage.h
*********************************************************************/

#ifndef ConfigStorage_H
#define ConfigStorage_H

#include "Application.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <cstdint>
class EepromData;

//## package Application

//## class ConfigStorage
class ConfigStorage : public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    ConfigStorage(RXF::Active* const activeContext = NULL);
    
    virtual ~ConfigStorage(void);
    
    ////    Operations    ////
    
    //## operation getConfigdata()
    std::uint32_t getConfigdata(void);
    
    //## operation setConfigdata(uint32_t)
    void setConfigdata(std::uint32_t update_LastStartTime);
    
    ////    Additional operations    ////
    
    std::uint32_t getDefaultStartTime(void) const;
    
    void setDefaultStartTime(const std::uint32_t p_DefaultStartTime);
    
    std::uint32_t getLastStartTime(void) const;
    
    void setLastStartTime(const std::uint32_t p_LastStartTime);
    
    bool getSuccess(void) const;
    
    void setSuccess(const bool p_success);
    
    EepromData* getItsEepromData(void) const;
    
    void setItsEepromData(EepromData* const p_EepromData);
    
    virtual bool startBehavior(void);

protected :

    void cleanUpRelations(void);

public :

    virtual void send_evProgrammStart(void);
    
    virtual void send_evConfigSettingsChangend(void);
    
    ////    Attributes    ////

protected :

    std::uint32_t DefaultStartTime;		//## attribute DefaultStartTime
    
    std::uint32_t LastStartTime;		//## attribute LastStartTime
    
    bool success;		//## attribute success
    
    ////    Relations and components    ////
    
    EepromData* itsEepromData;
    
    ////    Framework operations    ////

public :

    // rootState:
    inline bool rootState_IN(void) const;
    
    // InitialState:
    inline bool InitialState_IN(void) const;

protected :

    virtual void rootState_entDef(void);
    
    virtual RXF::Reactive::TakeEventStatus rootState_processEvent(void);
    
    ////    Framework    ////
    
    enum ConfigStorage_Enum {
        OMNonState = 0,
        InitialState = 1
    };

private :

    ConfigStorage_Enum rootState_subState;
    
    ConfigStorage_Enum rootState_active;
};

inline bool ConfigStorage::rootState_IN(void) const {
    return true;
}

inline bool ConfigStorage::InitialState_IN(void) const {
    return rootState_subState == InitialState;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/ConfigStorage.h
*********************************************************************/
