/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: ConfigStorage
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/ConfigStorage.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#define _OMSTATECHART_ANIMATED

#include "ConfigStorage.h"
#include "EepromData.h"
#define Application_ConfigStorage_ConfigStorage_SERIALIZE OM_NO_OP

#define Application_ConfigStorage_getConfigdata_SERIALIZE OM_NO_OP

#define Application_ConfigStorage_setConfigdata_SERIALIZE aomsmethod->addAttribute("update_LastStartTime", x2String(update_LastStartTime));

//## package Application

//## class ConfigStorage
ConfigStorage::ConfigStorage(IOxfActive* theActiveContext) {
    NOTIFY_REACTIVE_CONSTRUCTOR(ConfigStorage, ConfigStorage(), 0, Application_ConfigStorage_ConfigStorage_SERIALIZE);
    setActiveContext(theActiveContext, false);
    itsEepromData = NULL;
    initStatechart();
}

ConfigStorage::~ConfigStorage() {
    NOTIFY_DESTRUCTOR(~ConfigStorage, true);
    cleanUpRelations();
}

std::uint8_t ConfigStorage::getConfigdata() {
    NOTIFY_OPERATION(getConfigdata, getConfigdata(), 0, Application_ConfigStorage_getConfigdata_SERIALIZE);
    //#[ operation getConfigdata()
    return LastStartTime;
    //#]
}

void ConfigStorage::setConfigdata(const std::uint8_t update_LastStartTime) {
    NOTIFY_OPERATION(setConfigdata, setConfigdata(const std::uint8_t), 1, Application_ConfigStorage_setConfigdata_SERIALIZE);
    //#[ operation setConfigdata(uint8_t)
    LastStartTime=update_LastStartTime;
    //#]
}

std::uint8_t ConfigStorage::getLastStartTime() const {
    return LastStartTime;
}

void ConfigStorage::setLastStartTime(std::uint8_t p_LastStartTime) {
    LastStartTime = p_LastStartTime;
}

EepromData* ConfigStorage::getItsEepromData() const {
    return itsEepromData;
}

void ConfigStorage::setItsEepromData(EepromData* p_EepromData) {
    itsEepromData = p_EepromData;
    if(p_EepromData != NULL)
        {
            NOTIFY_RELATION_ITEM_ADDED("itsEepromData", p_EepromData, false, true);
        }
    else
        {
            NOTIFY_RELATION_CLEARED("itsEepromData");
        }
}

bool ConfigStorage::startBehavior() {
    bool done = false;
    done = OMReactive::startBehavior();
    return done;
}

void ConfigStorage::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

void ConfigStorage::cleanUpRelations() {
    if(itsEepromData != NULL)
        {
            NOTIFY_RELATION_CLEARED("itsEepromData");
            itsEepromData = NULL;
        }
}

void ConfigStorage::rootState_entDef() {
    {
        NOTIFY_STATE_ENTERED("ROOT");
        NOTIFY_TRANSITION_STARTED("0");
        NOTIFY_STATE_ENTERED("ROOT.InitialState");
        rootState_subState = InitialState;
        rootState_active = InitialState;
        NOTIFY_TRANSITION_TERMINATED("0");
    }
}

IOxfReactive::TakeEventStatus ConfigStorage::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State InitialState
    if(rootState_active == InitialState)
        {
            if(IS_EVENT_TYPE_OF(evConfigSettingsChangend_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("1");
                    NOTIFY_STATE_EXITED("ROOT.InitialState");
                    NOTIFY_STATE_ENTERED("ROOT.InitialState");
                    rootState_subState = InitialState;
                    rootState_active = InitialState;
                    NOTIFY_TRANSITION_TERMINATED("1");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evProgrammStart_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("2");
                    NOTIFY_STATE_EXITED("ROOT.InitialState");
                    NOTIFY_STATE_ENTERED("ROOT.InitialState");
                    rootState_subState = InitialState;
                    rootState_active = InitialState;
                    NOTIFY_TRANSITION_TERMINATED("2");
                    res = eventConsumed;
                }
            
        }
    return res;
}

#ifdef _OMINSTRUMENT
void OMAnimatedConfigStorage::serializeAttributes(AOMSAttributes* aomsAttributes) const {
    aomsAttributes->addAttribute("LastStartTime", x2String(myReal->LastStartTime));
}

void OMAnimatedConfigStorage::serializeRelations(AOMSRelations* aomsRelations) const {
    aomsRelations->addRelation("itsEepromData", false, true);
    if(myReal->itsEepromData)
        {
            aomsRelations->ADD_ITEM(myReal->itsEepromData);
        }
}

void OMAnimatedConfigStorage::rootState_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT");
    if(myReal->rootState_subState == ConfigStorage::InitialState)
        {
            InitialState_serializeStates(aomsState);
        }
}

void OMAnimatedConfigStorage::InitialState_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.InitialState");
}

IMPLEMENT_REACTIVE_META_P(ConfigStorage, Application, Application, false, OMAnimatedConfigStorage)
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/ConfigStorage.cpp
*********************************************************************/
