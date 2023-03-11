/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: ConfigStorage
//!	Generated Date	: Wed, 31, Aug 2022  
	File Path	: LPC1769/DefaultConfig/ConfigStorage.cpp
*********************************************************************/

#include "RXF_Active.h"
#include "ConfigStorage.h"
#include "EepromData.h"
//## package Application

//## class ConfigStorage
ConfigStorage::ConfigStorage(RXF::Active* const activeContext) : DefaultStartTime(240), LastStartTime(0), success(false), itsEepromData(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState) {
    setActiveContext(activeContext, false);
    
}

ConfigStorage::~ConfigStorage(void) {
    cleanUpRelations();
}

std::uint32_t ConfigStorage::getConfigdata(void) {
    //#[ operation getConfigdata()
    if(itsEepromData->getConfigdata(LastStartTime)>= 4000000){
    	return 4000000;
    }
    else if(itsEepromData->getConfigdata(LastStartTime)<= 5000){
    	return 5000;
    }
    return LastStartTime=itsEepromData->getConfigdata(LastStartTime);
    
    //#]
}

void ConfigStorage::setConfigdata(std::uint32_t update_LastStartTime) {
    //#[ operation setConfigdata(uint32_t)
    success = itsEepromData->setConfigdata(update_LastStartTime);
    
    /*
    itsEepromData->setConfigdata(update_LastStartTime);
    */
    //#]
}

std::uint32_t ConfigStorage::getDefaultStartTime(void) const {
    return DefaultStartTime;
}

void ConfigStorage::setDefaultStartTime(const std::uint32_t p_DefaultStartTime) {
    DefaultStartTime = p_DefaultStartTime;
}

std::uint32_t ConfigStorage::getLastStartTime(void) const {
    return LastStartTime;
}

void ConfigStorage::setLastStartTime(const std::uint32_t p_LastStartTime) {
    LastStartTime = p_LastStartTime;
}

bool ConfigStorage::getSuccess(void) const {
    return success;
}

void ConfigStorage::setSuccess(const bool p_success) {
    success = p_success;
}

EepromData* ConfigStorage::getItsEepromData(void) const {
    return itsEepromData;
}

void ConfigStorage::setItsEepromData(EepromData* const p_EepromData) {
    itsEepromData = p_EepromData;
}

bool ConfigStorage::startBehavior(void) {
    bool done = false;
    done = RXF::Reactive::startBehavior();
    return done;
}

void ConfigStorage::cleanUpRelations(void) {
    if(itsEepromData != nullptr)
        {
            itsEepromData = nullptr;
        }
}

void ConfigStorage::send_evProgrammStart(void) {
    send( new evProgrammStart()  );
}

void ConfigStorage::send_evConfigSettingsChangend(void) {
    send( new evConfigSettingsChangend()  );
}

void ConfigStorage::rootState_entDef(void) {
    {
        rootState_subState = InitialState;
        rootState_active = InitialState;
    }
}

RXF::Reactive::TakeEventStatus ConfigStorage::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    // State InitialState
    if(rootState_active == InitialState)
        {
            if(evConfigSettingsChangend_Application_id == getCurrentEvent()->getId())
                {
                    rootState_subState = InitialState;
                    rootState_active = InitialState;
                    res = eventConsumed;
                }
            else {
                if(evProgrammStart_Application_id == getCurrentEvent()->getId())
                    {
                        rootState_subState = InitialState;
                        rootState_active = InitialState;
                        res = eventConsumed;
                    }
                }
                
            
        }
    return res;
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/ConfigStorage.cpp
*********************************************************************/
