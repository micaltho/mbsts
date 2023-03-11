/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: DisplayTask
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: Simulation/DefaultConfig/DisplayTask.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#define _OMSTATECHART_ANIMATED

#include "DisplayTask.h"
#include "Display.h"
#define Application_DisplayTask_updateDisplay_SERIALIZE \
    aomsmethod->addAttribute("update_mode", UNKNOWN2STRING(update_mode));\
    aomsmethod->addAttribute("update_currentTime", UNKNOWN2STRING(update_currentTime));\
    aomsmethod->addAttribute("update_configTime", UNKNOWN2STRING(update_configTime));\
    aomsmethod->addAttribute("update_acc_X", UNKNOWN2STRING(update_acc_X));\
    aomsmethod->addAttribute("update_acc_Y", UNKNOWN2STRING(update_acc_Y));\
    aomsmethod->addAttribute("update_acc_Z", UNKNOWN2STRING(update_acc_Z));
#define Application_DisplayTask_DisplayTask_SERIALIZE aomsmethod->addAttribute("updateTimeDisplay", UNKNOWN2STRING(updateTimeDisplay));

#define OM_Application_DisplayTask_DisplayTask_1_SERIALIZE OM_NO_OP

#define Application_DisplayTask_init_SERIALIZE OM_NO_OP

//## package Application

//## class DisplayTask
DisplayTask::DisplayTask(const std::uint32_t updateTimeDisplay, IOxfActive* theActiveContext) : acc_X(0), acc_Y(0), acc_Z(0), updateTimeDisplay(updateTimeDisplay) {
    NOTIFY_ACTIVE_CONSTRUCTOR(DisplayTask, DisplayTask(const std::uint32_t), 1, Application_DisplayTask_DisplayTask_SERIALIZE);
    itsDisplay = NULL;
    setActiveContext(this, true);
    initStatechart();
    //#[ operation DisplayTask(uint32_t)
    //#]
}

DisplayTask::DisplayTask(IOxfActive* theActiveContext) : acc_X(0), acc_Y(0), acc_Z(0) {
    NOTIFY_ACTIVE_CONSTRUCTOR(DisplayTask, DisplayTask(), 0, OM_Application_DisplayTask_DisplayTask_1_SERIALIZE);
    setActiveContext(this, true);
    itsDisplay = NULL;
    initStatechart();
}

DisplayTask::~DisplayTask() {
    NOTIFY_DESTRUCTOR(~DisplayTask, true);
    cleanUpRelations();
    cancelTimeouts();
}

void DisplayTask::init() {
    NOTIFY_OPERATION(init, init(), 0, Application_DisplayTask_init_SERIALIZE);
    //#[ operation init()
    //#]
}

void DisplayTask::updateDisplay(const std::uint32_t update_mode, const std::uint32_t update_currentTime, const std::uint32_t update_configTime, const std::int32_t update_acc_X, const std::int32_t update_acc_Y, const std::int32_t update_acc_Z) {
    NOTIFY_OPERATION(updateDisplay, updateDisplay(const std::uint32_t,const std::uint32_t,const std::uint32_t,const std::int32_t,const std::int32_t,const std::int32_t), 6, Application_DisplayTask_updateDisplay_SERIALIZE);
    //#[ operation updateDisplay(uint32_t,uint32_t,uint32_t,int32_t,int32_t,int32_t)
    mode = update_mode;
    currentTime_ms = update_currentTime;
    configTime_ms = update_configTime;
    acc_X = update_acc_X;
    acc_Y = update_acc_Y;
    acc_Z = update_acc_Z;
    //#]
}

std::int32_t DisplayTask::getAcc_X() const {
    return acc_X;
}

void DisplayTask::setAcc_X(std::int32_t p_acc_X) {
    acc_X = p_acc_X;
}

std::int32_t DisplayTask::getAcc_Y() const {
    return acc_Y;
}

void DisplayTask::setAcc_Y(std::int32_t p_acc_Y) {
    acc_Y = p_acc_Y;
}

std::int32_t DisplayTask::getAcc_Z() const {
    return acc_Z;
}

void DisplayTask::setAcc_Z(std::int32_t p_acc_Z) {
    acc_Z = p_acc_Z;
}

std::uint32_t DisplayTask::getConfigTime_ms() const {
    return configTime_ms;
}

void DisplayTask::setConfigTime_ms(std::uint32_t p_configTime_ms) {
    configTime_ms = p_configTime_ms;
}

std::uint32_t DisplayTask::getCurrentTime_ms() const {
    return currentTime_ms;
}

void DisplayTask::setCurrentTime_ms(std::uint32_t p_currentTime_ms) {
    currentTime_ms = p_currentTime_ms;
}

std::uint32_t DisplayTask::getMode() const {
    return mode;
}

void DisplayTask::setMode(std::uint32_t p_mode) {
    mode = p_mode;
}

std::uint32_t DisplayTask::getUpdateTimeDisplay() const {
    return updateTimeDisplay;
}

void DisplayTask::setUpdateTimeDisplay(std::uint32_t p_updateTimeDisplay) {
    updateTimeDisplay = p_updateTimeDisplay;
}

Display* DisplayTask::getItsDisplay() const {
    return itsDisplay;
}

void DisplayTask::setItsDisplay(Display* p_Display) {
    itsDisplay = p_Display;
    if(p_Display != NULL)
        {
            NOTIFY_RELATION_ITEM_ADDED("itsDisplay", p_Display, false, true);
        }
    else
        {
            NOTIFY_RELATION_CLEARED("itsDisplay");
        }
}

bool DisplayTask::startBehavior() {
    bool done = false;
    done = OMReactive::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void DisplayTask::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void DisplayTask::cleanUpRelations() {
    if(itsDisplay != NULL)
        {
            NOTIFY_RELATION_CLEARED("itsDisplay");
            itsDisplay = NULL;
        }
}

void DisplayTask::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool DisplayTask::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void DisplayTask::rootState_entDef() {
    {
        NOTIFY_STATE_ENTERED("ROOT");
        NOTIFY_TRANSITION_STARTED("0");
        //#[ transition 0 
        itsDisplay->init();
        //#]
        NOTIFY_STATE_ENTERED("ROOT.Update");
        rootState_subState = Update;
        rootState_active = Update;
        rootState_timeout = scheduleTimeout(updateTimeDisplay, "ROOT.Update");
        NOTIFY_TRANSITION_TERMINATED("0");
    }
}

IOxfReactive::TakeEventStatus DisplayTask::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State Update
    if(rootState_active == Update)
        {
            if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            NOTIFY_TRANSITION_STARTED("1");
                            cancel(rootState_timeout);
                            NOTIFY_STATE_EXITED("ROOT.Update");
                            //#[ transition 1 
                            itsDisplay->updateDisplay(mode, currentTime_ms, configTime_ms, acc_X, acc_Y, acc_Z);
                            //#]
                            NOTIFY_STATE_ENTERED("ROOT.Update");
                            rootState_subState = Update;
                            rootState_active = Update;
                            rootState_timeout = scheduleTimeout(updateTimeDisplay, "ROOT.Update");
                            NOTIFY_TRANSITION_TERMINATED("1");
                            res = eventConsumed;
                        }
                }
            
        }
    return res;
}

#ifdef _OMINSTRUMENT
void OMAnimatedDisplayTask::serializeAttributes(AOMSAttributes* aomsAttributes) const {
    aomsAttributes->addAttribute("updateTimeDisplay", UNKNOWN2STRING(myReal->updateTimeDisplay));
    aomsAttributes->addAttribute("configTime_ms", UNKNOWN2STRING(myReal->configTime_ms));
    aomsAttributes->addAttribute("currentTime_ms", UNKNOWN2STRING(myReal->currentTime_ms));
    aomsAttributes->addAttribute("mode", UNKNOWN2STRING(myReal->mode));
    aomsAttributes->addAttribute("acc_X", UNKNOWN2STRING(myReal->acc_X));
    aomsAttributes->addAttribute("acc_Y", UNKNOWN2STRING(myReal->acc_Y));
    aomsAttributes->addAttribute("acc_Z", UNKNOWN2STRING(myReal->acc_Z));
}

void OMAnimatedDisplayTask::serializeRelations(AOMSRelations* aomsRelations) const {
    aomsRelations->addRelation("itsDisplay", false, true);
    if(myReal->itsDisplay)
        {
            aomsRelations->ADD_ITEM(myReal->itsDisplay);
        }
}

void OMAnimatedDisplayTask::rootState_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT");
    if(myReal->rootState_subState == DisplayTask::Update)
        {
            Update_serializeStates(aomsState);
        }
}

void OMAnimatedDisplayTask::Update_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.Update");
}

IMPLEMENT_REACTIVE_META_P(DisplayTask, Application, Application, false, OMAnimatedDisplayTask)
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/DisplayTask.cpp
*********************************************************************/
