/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: Controller
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/Controller.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#define _OMSTATECHART_ANIMATED

#include "Controller.h"
#include "AccelerationMeasuring.h"
#include "ConfigStorage.h"
#include "DisplayTask.h"
#include "TimeCounter.h"
#define Application_Controller_Controller_SERIALIZE \
    aomsmethod->addAttribute("defaultStartTime", UNKNOWN2STRING(defaultStartTime));\
    aomsmethod->addAttribute("tickTimeController", UNKNOWN2STRING(tickTimeController));\
    aomsmethod->addAttribute("timeFactor", UNKNOWN2STRING(timeFactor));
#define OM_Application_Controller_Controller_1_SERIALIZE OM_NO_OP

#define Application_Controller_raiseStartTime_SERIALIZE OM_NO_OP

#define Application_Controller_raiseTimeFactor_SERIALIZE OM_NO_OP

#define Application_Controller_reduceStartTime_SERIALIZE OM_NO_OP

#define Application_Controller_reduceTimeFactor_SERIALIZE OM_NO_OP

#define Application_Controller_setTime_SERIALIZE aomsmethod->addAttribute("newTime_ms", UNKNOWN2STRING(newTime_ms));

//## package Application

//## class Controller
Controller::Controller(const std::uint32_t defaultStartTime, const std::uint32_t tickTimeController, const std::uint32_t timeFactor, IOxfActive* theActiveContext) : backward_threshold(-50), forward_threshold(50), startTime(defaultStartTime), tickTimeController(tickTimeController), timeFactor(timeFactor) {
    NOTIFY_ACTIVE_CONSTRUCTOR(Controller, Controller(const std::uint32_t,const std::uint32_t,const std::uint32_t), 3, Application_Controller_Controller_SERIALIZE);
    itsTimeCounter = NULL;
    itsDisplayTask = NULL;
    itsConfigStorage = NULL;
    itsAccelerationMeasuring = NULL;
    setActiveContext(this, true);
    initStatechart();
    //#[ operation Controller(uint32_t,uint32_t,uint32_t)
    //#]
}

Controller::Controller(IOxfActive* theActiveContext) : backward_threshold(-50), forward_threshold(50) {
    NOTIFY_ACTIVE_CONSTRUCTOR(Controller, Controller(), 0, OM_Application_Controller_Controller_1_SERIALIZE);
    setActiveContext(this, true);
    itsAccelerationMeasuring = NULL;
    itsConfigStorage = NULL;
    itsDisplayTask = NULL;
    itsTimeCounter = NULL;
    initStatechart();
}

Controller::~Controller() {
    NOTIFY_DESTRUCTOR(~Controller, true);
    cleanUpRelations();
    cancelTimeouts();
}

void Controller::raiseStartTime() {
    NOTIFY_OPERATION(raiseStartTime, raiseStartTime(), 0, Application_Controller_raiseStartTime_SERIALIZE);
    // State action_0
    //#[ state raiseStartTime().action_0.(Entry) 
    startTime += timeFactor;
    //itsEepromData->Store(startTime);
    //#]
    //#[ transition raiseStartTime().2 
    //#]
    if ( startTime >= 4000000 )
    {
        // State action_1
        //#[ state raiseStartTime().action_1.(Entry) 
        startTime = 4000000;
        //itsEepromData->Store(startTime);
        //#]
    }
    return;
    
}

void Controller::raiseTimeFactor() {
    NOTIFY_OPERATION(raiseTimeFactor, raiseTimeFactor(), 0, Application_Controller_raiseTimeFactor_SERIALIZE);
    //#[ transition raiseTimeFactor().1 
    //#]
    if ( timeFactor >= 1000 )
    {
        // State action_2
        //#[ state raiseTimeFactor().action_2.(Entry) 
        timeFactor = 60000;
        //#]
    }
    else
    {
        // State action_3
        //#[ state raiseTimeFactor().action_3.(Entry) 
        timeFactor *= 10;
        
        //#]
    }
    return;
    
}

void Controller::reduceStartTime() {
    NOTIFY_OPERATION(reduceStartTime, reduceStartTime(), 0, Application_Controller_reduceStartTime_SERIALIZE);
    // State action_0
    //#[ state reduceStartTime().action_0.(Entry) 
    startTime -= timeFactor;
    //itsEepromData->Store(startTime);
    //#]
    //#[ transition reduceStartTime().2 
    //#]
    if ( startTime <= timeFactor )
    {
        // State action_1
        //#[ state reduceStartTime().action_1.(Entry) 
        startTime = timeFactor;
        //itsEepromData->Store(startTime);
        //#]
    }
    return;
    
}

void Controller::reduceTimeFactor() {
    NOTIFY_OPERATION(reduceTimeFactor, reduceTimeFactor(), 0, Application_Controller_reduceTimeFactor_SERIALIZE);
    //#[ transition reduceTimeFactor().1 
    //#]
    if ( timeFactor <= 10 )
    {
        // State action_0
        //#[ state reduceTimeFactor().action_0.(Entry) 
        timeFactor = 10;
        //#]
    }
    else
    {
        //#[ transition reduceTimeFactor().3 
        //#]
        if ( timeFactor > 1000 )
        {
            // State action_2
            //#[ state reduceTimeFactor().action_2.(Entry) 
            timeFactor /= 60;
            //#]
        }
        else
        {
            // State action_3
            //#[ state reduceTimeFactor().action_3.(Entry) 
            timeFactor /= 10;
            //#]
        }
    }
    return;
    
}

void Controller::setTime(const std::uint32_t newTime_ms) {
    NOTIFY_OPERATION(setTime, setTime(const std::uint32_t), 1, Application_Controller_setTime_SERIALIZE);
    //#[ operation setTime(uint32_t)
    //#]
}

std::int32_t Controller::getBackward_threshold() const {
    return backward_threshold;
}

void Controller::setBackward_threshold(std::int32_t p_backward_threshold) {
    backward_threshold = p_backward_threshold;
}

std::int32_t Controller::getForward_threshold() const {
    return forward_threshold;
}

void Controller::setForward_threshold(std::int32_t p_forward_threshold) {
    forward_threshold = p_forward_threshold;
}

std::uint32_t Controller::getStartTime() const {
    return startTime;
}

void Controller::setStartTime(std::uint32_t p_startTime) {
    startTime = p_startTime;
}

std::uint32_t Controller::getTickTimeController() const {
    return tickTimeController;
}

void Controller::setTickTimeController(std::uint32_t p_tickTimeController) {
    tickTimeController = p_tickTimeController;
}

std::uint32_t Controller::getTimeFactor() const {
    return timeFactor;
}

void Controller::setTimeFactor(std::uint32_t p_timeFactor) {
    timeFactor = p_timeFactor;
}

AccelerationMeasuring* Controller::getItsAccelerationMeasuring() const {
    return itsAccelerationMeasuring;
}

void Controller::setItsAccelerationMeasuring(AccelerationMeasuring* p_AccelerationMeasuring) {
    itsAccelerationMeasuring = p_AccelerationMeasuring;
    if(p_AccelerationMeasuring != NULL)
        {
            NOTIFY_RELATION_ITEM_ADDED("itsAccelerationMeasuring", p_AccelerationMeasuring, false, true);
        }
    else
        {
            NOTIFY_RELATION_CLEARED("itsAccelerationMeasuring");
        }
}

ConfigStorage* Controller::getItsConfigStorage() const {
    return itsConfigStorage;
}

void Controller::setItsConfigStorage(ConfigStorage* p_ConfigStorage) {
    itsConfigStorage = p_ConfigStorage;
    if(p_ConfigStorage != NULL)
        {
            NOTIFY_RELATION_ITEM_ADDED("itsConfigStorage", p_ConfigStorage, false, true);
        }
    else
        {
            NOTIFY_RELATION_CLEARED("itsConfigStorage");
        }
}

DisplayTask* Controller::getItsDisplayTask() const {
    return itsDisplayTask;
}

void Controller::setItsDisplayTask(DisplayTask* p_DisplayTask) {
    itsDisplayTask = p_DisplayTask;
    if(p_DisplayTask != NULL)
        {
            NOTIFY_RELATION_ITEM_ADDED("itsDisplayTask", p_DisplayTask, false, true);
        }
    else
        {
            NOTIFY_RELATION_CLEARED("itsDisplayTask");
        }
}

TimeCounter* Controller::getItsTimeCounter() const {
    return itsTimeCounter;
}

void Controller::setItsTimeCounter(TimeCounter* p_TimeCounter) {
    itsTimeCounter = p_TimeCounter;
    if(p_TimeCounter != NULL)
        {
            NOTIFY_RELATION_ITEM_ADDED("itsTimeCounter", p_TimeCounter, false, true);
        }
    else
        {
            NOTIFY_RELATION_CLEARED("itsTimeCounter");
        }
}

bool Controller::startBehavior() {
    bool done = false;
    done = OMReactive::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void Controller::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void Controller::cleanUpRelations() {
    if(itsAccelerationMeasuring != NULL)
        {
            NOTIFY_RELATION_CLEARED("itsAccelerationMeasuring");
            itsAccelerationMeasuring = NULL;
        }
    if(itsConfigStorage != NULL)
        {
            NOTIFY_RELATION_CLEARED("itsConfigStorage");
            itsConfigStorage = NULL;
        }
    if(itsDisplayTask != NULL)
        {
            NOTIFY_RELATION_CLEARED("itsDisplayTask");
            itsDisplayTask = NULL;
        }
    if(itsTimeCounter != NULL)
        {
            NOTIFY_RELATION_CLEARED("itsTimeCounter");
            itsTimeCounter = NULL;
        }
}

void Controller::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool Controller::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void Controller::rootState_entDef() {
    {
        NOTIFY_STATE_ENTERED("ROOT");
        NOTIFY_TRANSITION_STARTED("0");
        //#[ transition 0 
        itsConfigStorage->getConfigdata();
        //#]
        NOTIFY_STATE_ENTERED("ROOT.RunHourglass");
        rootState_subState = RunHourglass;
        rootState_active = RunHourglass;
        //#[ state RunHourglass.(Entry) 
        if(itsAccelerationMeasuring->getSmoothAccelerationX() < forward_threshold && itsAccelerationMeasuring->getSmoothAccelerationX() > 5)
        {
        	itsTimeCounter->GEN(evRunForward());
        }
        else if(itsAccelerationMeasuring->getSmoothAccelerationX() < -5 && itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
        {
        	itsTimeCounter->GEN(evRunBackward());
        }
        else if(itsAccelerationMeasuring->getSmoothAccelerationX() > forward_threshold)
        {
        	itsTimeCounter->GEN(evStop());
        }
        else if(itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
        {
        	itsTimeCounter->GEN(evStop());
        }
        
        //#]
        rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.RunHourglass");
        NOTIFY_TRANSITION_TERMINATED("0");
    }
}

IOxfReactive::TakeEventStatus Controller::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Menu
        case Menu:
        {
            res = Menu_handleEvent();
        }
        break;
        // State RunHourglass
        case RunHourglass:
        {
            res = RunHourglass_handleEvent();
        }
        break;
        // State changeStartTime
        case changeStartTime:
        {
            if(IS_EVENT_TYPE_OF(evRaiseStartTime_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("5");
                    NOTIFY_STATE_EXITED("ROOT.changeStartTime");
                    //#[ transition 5 
                    raiseStartTime();
                    itsConfigStorage->setConfigdata(startTime);
                    itsDisplayTask->updateDisplay(3, itsTimeCounter->getCurrentTime_ms(), startTime, 0);
                    //#]
                    NOTIFY_STATE_ENTERED("ROOT.changeStartTime");
                    rootState_subState = changeStartTime;
                    rootState_active = changeStartTime;
                    NOTIFY_TRANSITION_TERMINATED("5");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evGoBack_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("7");
                    NOTIFY_STATE_EXITED("ROOT.changeStartTime");
                    //#[ transition 7 
                    itsTimeCounter->setStartTime_ms(startTime);
                    //#]
                    NOTIFY_STATE_ENTERED("ROOT.Menu");
                    rootState_subState = Menu;
                    rootState_active = Menu;
                    //#[ state Menu.(Entry) 
                    itsDisplayTask->updateDisplay(1, itsTimeCounter->getCurrentTime_ms(), startTime, 0);
                    //#]
                    rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.Menu");
                    NOTIFY_TRANSITION_TERMINATED("7");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evReduceStartTime_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("6");
                    NOTIFY_STATE_EXITED("ROOT.changeStartTime");
                    //#[ transition 6 
                    reduceStartTime();
                    itsConfigStorage->setConfigdata(startTime);
                    itsDisplayTask->updateDisplay(3, itsTimeCounter->getCurrentTime_ms(), startTime, 0);
                    //#]
                    NOTIFY_STATE_ENTERED("ROOT.changeStartTime");
                    rootState_subState = changeStartTime;
                    rootState_active = changeStartTime;
                    NOTIFY_TRANSITION_TERMINATED("6");
                    res = eventConsumed;
                }
            
        }
        break;
        // State changeTimeFactor
        case changeTimeFactor:
        {
            if(IS_EVENT_TYPE_OF(evRaiseTimeFactor_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("10");
                    NOTIFY_STATE_EXITED("ROOT.changeTimeFactor");
                    //#[ transition 10 
                    raiseTimeFactor();
                    itsDisplayTask->updateDisplay(2, itsTimeCounter->getCurrentTime_ms(), timeFactor, 0);
                    //#]
                    NOTIFY_STATE_ENTERED("ROOT.changeTimeFactor");
                    rootState_subState = changeTimeFactor;
                    rootState_active = changeTimeFactor;
                    NOTIFY_TRANSITION_TERMINATED("10");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evReduceTimeFactor_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("11");
                    NOTIFY_STATE_EXITED("ROOT.changeTimeFactor");
                    //#[ transition 11 
                    reduceTimeFactor();
                    itsDisplayTask->updateDisplay(2, itsTimeCounter->getCurrentTime_ms(), timeFactor, 0);
                    //#]
                    NOTIFY_STATE_ENTERED("ROOT.changeTimeFactor");
                    rootState_subState = changeTimeFactor;
                    rootState_active = changeTimeFactor;
                    NOTIFY_TRANSITION_TERMINATED("11");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evGoBack_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("9");
                    NOTIFY_STATE_EXITED("ROOT.changeTimeFactor");
                    NOTIFY_STATE_ENTERED("ROOT.Menu");
                    rootState_subState = Menu;
                    rootState_active = Menu;
                    //#[ state Menu.(Entry) 
                    itsDisplayTask->updateDisplay(1, itsTimeCounter->getCurrentTime_ms(), startTime, 0);
                    //#]
                    rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.Menu");
                    NOTIFY_TRANSITION_TERMINATED("9");
                    res = eventConsumed;
                }
            
        }
        break;
        // State accelerometerSettings
        case accelerometerSettings:
        {
            if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            NOTIFY_TRANSITION_STARTED("16");
                            cancel(rootState_timeout);
                            NOTIFY_STATE_EXITED("ROOT.accelerometerSettings");
                            NOTIFY_STATE_ENTERED("ROOT.accelerometerSettings");
                            rootState_subState = accelerometerSettings;
                            rootState_active = accelerometerSettings;
                            //#[ state accelerometerSettings.(Entry) 
                            itsDisplayTask->updateDisplay(4, itsTimeCounter->getCurrentTime_ms(), startTime,itsAccelerationMeasuring->getSmoothAccelerationX(), itsAccelerationMeasuring->getSmoothAccelerationY(), itsAccelerationMeasuring->getSmoothAccelerationZ());
                            
                            //#]
                            rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.accelerometerSettings");
                            NOTIFY_TRANSITION_TERMINATED("16");
                            res = eventConsumed;
                        }
                }
            else if(IS_EVENT_TYPE_OF(evGoBack_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("15");
                    cancel(rootState_timeout);
                    NOTIFY_STATE_EXITED("ROOT.accelerometerSettings");
                    NOTIFY_STATE_ENTERED("ROOT.Menu");
                    rootState_subState = Menu;
                    rootState_active = Menu;
                    //#[ state Menu.(Entry) 
                    itsDisplayTask->updateDisplay(1, itsTimeCounter->getCurrentTime_ms(), startTime, 0);
                    //#]
                    rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.Menu");
                    NOTIFY_TRANSITION_TERMINATED("15");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(evStartTimeSetting_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("17");
                    cancel(rootState_timeout);
                    NOTIFY_STATE_EXITED("ROOT.accelerometerSettings");
                    //#[ transition 17 
                    itsAccelerationMeasuring->GEN(evCalibrate());
                    //#]
                    NOTIFY_STATE_ENTERED("ROOT.accelerometerSettings");
                    rootState_subState = accelerometerSettings;
                    rootState_active = accelerometerSettings;
                    //#[ state accelerometerSettings.(Entry) 
                    itsDisplayTask->updateDisplay(4, itsTimeCounter->getCurrentTime_ms(), startTime,itsAccelerationMeasuring->getSmoothAccelerationX(), itsAccelerationMeasuring->getSmoothAccelerationY(), itsAccelerationMeasuring->getSmoothAccelerationZ());
                    
                    //#]
                    rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.accelerometerSettings");
                    NOTIFY_TRANSITION_TERMINATED("17");
                    res = eventConsumed;
                }
            
        }
        break;
        default:
            break;
    }
    return res;
}

IOxfReactive::TakeEventStatus Controller::RunHourglass_handleEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
        {
            if(getCurrentEvent() == rootState_timeout)
                {
                    NOTIFY_TRANSITION_STARTED("3");
                    cancel(rootState_timeout);
                    //#[ state RunHourglass.(Exit) 
                    //itsTimeCounter->GEN(evStop());
                    //#]
                    NOTIFY_STATE_EXITED("ROOT.RunHourglass");
                    //#[ transition 3 
                    itsDisplayTask->updateDisplay(0, itsTimeCounter->getCurrentTime_ms(), startTime, 0);
                    //#]
                    NOTIFY_STATE_ENTERED("ROOT.RunHourglass");
                    rootState_subState = RunHourglass;
                    rootState_active = RunHourglass;
                    //#[ state RunHourglass.(Entry) 
                    if(itsAccelerationMeasuring->getSmoothAccelerationX() < forward_threshold && itsAccelerationMeasuring->getSmoothAccelerationX() > 5)
                    {
                    	itsTimeCounter->GEN(evRunForward());
                    }
                    else if(itsAccelerationMeasuring->getSmoothAccelerationX() < -5 && itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
                    {
                    	itsTimeCounter->GEN(evRunBackward());
                    }
                    else if(itsAccelerationMeasuring->getSmoothAccelerationX() > forward_threshold)
                    {
                    	itsTimeCounter->GEN(evStop());
                    }
                    else if(itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
                    {
                    	itsTimeCounter->GEN(evStop());
                    }
                    
                    //#]
                    rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.RunHourglass");
                    NOTIFY_TRANSITION_TERMINATED("3");
                    res = eventConsumed;
                }
        }
    else if(IS_EVENT_TYPE_OF(evReset_Application_id))
        {
            NOTIFY_TRANSITION_STARTED("13");
            cancel(rootState_timeout);
            //#[ state RunHourglass.(Exit) 
            //itsTimeCounter->GEN(evStop());
            //#]
            NOTIFY_STATE_EXITED("ROOT.RunHourglass");
            //#[ transition 13 
            itsTimeCounter->GEN(evResetTime());
            //#]
            NOTIFY_STATE_ENTERED("ROOT.RunHourglass");
            rootState_subState = RunHourglass;
            rootState_active = RunHourglass;
            //#[ state RunHourglass.(Entry) 
            if(itsAccelerationMeasuring->getSmoothAccelerationX() < forward_threshold && itsAccelerationMeasuring->getSmoothAccelerationX() > 5)
            {
            	itsTimeCounter->GEN(evRunForward());
            }
            else if(itsAccelerationMeasuring->getSmoothAccelerationX() < -5 && itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
            {
            	itsTimeCounter->GEN(evRunBackward());
            }
            else if(itsAccelerationMeasuring->getSmoothAccelerationX() > forward_threshold)
            {
            	itsTimeCounter->GEN(evStop());
            }
            else if(itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
            {
            	itsTimeCounter->GEN(evStop());
            }
            
            //#]
            rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.RunHourglass");
            NOTIFY_TRANSITION_TERMINATED("13");
            res = eventConsumed;
        }
    else if(IS_EVENT_TYPE_OF(evMenu_Application_id))
        {
            NOTIFY_TRANSITION_STARTED("1");
            cancel(rootState_timeout);
            //#[ state RunHourglass.(Exit) 
            //itsTimeCounter->GEN(evStop());
            //#]
            NOTIFY_STATE_EXITED("ROOT.RunHourglass");
            //#[ transition 1 
            itsTimeCounter->GEN(evStop());
            //#]
            NOTIFY_STATE_ENTERED("ROOT.Menu");
            rootState_subState = Menu;
            rootState_active = Menu;
            //#[ state Menu.(Entry) 
            itsDisplayTask->updateDisplay(1, itsTimeCounter->getCurrentTime_ms(), startTime, 0);
            //#]
            rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.Menu");
            NOTIFY_TRANSITION_TERMINATED("1");
            res = eventConsumed;
        }
    
    return res;
}

IOxfReactive::TakeEventStatus Controller::Menu_handleEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
        {
            if(getCurrentEvent() == rootState_timeout)
                {
                    NOTIFY_TRANSITION_STARTED("12");
                    cancel(rootState_timeout);
                    NOTIFY_STATE_EXITED("ROOT.Menu");
                    NOTIFY_STATE_ENTERED("ROOT.Menu");
                    rootState_subState = Menu;
                    rootState_active = Menu;
                    //#[ state Menu.(Entry) 
                    itsDisplayTask->updateDisplay(1, itsTimeCounter->getCurrentTime_ms(), startTime, 0);
                    //#]
                    rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.Menu");
                    NOTIFY_TRANSITION_TERMINATED("12");
                    res = eventConsumed;
                }
        }
    else if(IS_EVENT_TYPE_OF(evTimeFactorSetting_Application_id))
        {
            NOTIFY_TRANSITION_STARTED("8");
            cancel(rootState_timeout);
            NOTIFY_STATE_EXITED("ROOT.Menu");
            NOTIFY_STATE_ENTERED("ROOT.changeTimeFactor");
            rootState_subState = changeTimeFactor;
            rootState_active = changeTimeFactor;
            NOTIFY_TRANSITION_TERMINATED("8");
            res = eventConsumed;
        }
    else if(IS_EVENT_TYPE_OF(evGoBack_Application_id))
        {
            NOTIFY_TRANSITION_STARTED("2");
            cancel(rootState_timeout);
            NOTIFY_STATE_EXITED("ROOT.Menu");
            NOTIFY_STATE_ENTERED("ROOT.RunHourglass");
            rootState_subState = RunHourglass;
            rootState_active = RunHourglass;
            //#[ state RunHourglass.(Entry) 
            if(itsAccelerationMeasuring->getSmoothAccelerationX() < forward_threshold && itsAccelerationMeasuring->getSmoothAccelerationX() > 5)
            {
            	itsTimeCounter->GEN(evRunForward());
            }
            else if(itsAccelerationMeasuring->getSmoothAccelerationX() < -5 && itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
            {
            	itsTimeCounter->GEN(evRunBackward());
            }
            else if(itsAccelerationMeasuring->getSmoothAccelerationX() > forward_threshold)
            {
            	itsTimeCounter->GEN(evStop());
            }
            else if(itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
            {
            	itsTimeCounter->GEN(evStop());
            }
            
            //#]
            rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.RunHourglass");
            NOTIFY_TRANSITION_TERMINATED("2");
            res = eventConsumed;
        }
    else if(IS_EVENT_TYPE_OF(evMenu_Application_id))
        {
            NOTIFY_TRANSITION_STARTED("14");
            cancel(rootState_timeout);
            NOTIFY_STATE_EXITED("ROOT.Menu");
            NOTIFY_STATE_ENTERED("ROOT.accelerometerSettings");
            rootState_subState = accelerometerSettings;
            rootState_active = accelerometerSettings;
            //#[ state accelerometerSettings.(Entry) 
            itsDisplayTask->updateDisplay(4, itsTimeCounter->getCurrentTime_ms(), startTime,itsAccelerationMeasuring->getSmoothAccelerationX(), itsAccelerationMeasuring->getSmoothAccelerationY(), itsAccelerationMeasuring->getSmoothAccelerationZ());
            
            //#]
            rootState_timeout = scheduleTimeout(tickTimeController, "ROOT.accelerometerSettings");
            NOTIFY_TRANSITION_TERMINATED("14");
            res = eventConsumed;
        }
    else if(IS_EVENT_TYPE_OF(evStartTimeSetting_Application_id))
        {
            NOTIFY_TRANSITION_STARTED("4");
            cancel(rootState_timeout);
            NOTIFY_STATE_EXITED("ROOT.Menu");
            NOTIFY_STATE_ENTERED("ROOT.changeStartTime");
            rootState_subState = changeStartTime;
            rootState_active = changeStartTime;
            NOTIFY_TRANSITION_TERMINATED("4");
            res = eventConsumed;
        }
    
    return res;
}

#ifdef _OMINSTRUMENT
void OMAnimatedController::serializeAttributes(AOMSAttributes* aomsAttributes) const {
    aomsAttributes->addAttribute("startTime", UNKNOWN2STRING(myReal->startTime));
    aomsAttributes->addAttribute("tickTimeController", UNKNOWN2STRING(myReal->tickTimeController));
    aomsAttributes->addAttribute("timeFactor", UNKNOWN2STRING(myReal->timeFactor));
    aomsAttributes->addAttribute("forward_threshold", UNKNOWN2STRING(myReal->forward_threshold));
    aomsAttributes->addAttribute("backward_threshold", UNKNOWN2STRING(myReal->backward_threshold));
}

void OMAnimatedController::serializeRelations(AOMSRelations* aomsRelations) const {
    aomsRelations->addRelation("itsDisplayTask", false, true);
    if(myReal->itsDisplayTask)
        {
            aomsRelations->ADD_ITEM(myReal->itsDisplayTask);
        }
    aomsRelations->addRelation("itsTimeCounter", false, true);
    if(myReal->itsTimeCounter)
        {
            aomsRelations->ADD_ITEM(myReal->itsTimeCounter);
        }
    aomsRelations->addRelation("itsAccelerationMeasuring", false, true);
    if(myReal->itsAccelerationMeasuring)
        {
            aomsRelations->ADD_ITEM(myReal->itsAccelerationMeasuring);
        }
    aomsRelations->addRelation("itsConfigStorage", false, true);
    if(myReal->itsConfigStorage)
        {
            aomsRelations->ADD_ITEM(myReal->itsConfigStorage);
        }
}

void OMAnimatedController::rootState_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT");
    switch (myReal->rootState_subState) {
        case Controller::Menu:
        {
            Menu_serializeStates(aomsState);
        }
        break;
        case Controller::RunHourglass:
        {
            RunHourglass_serializeStates(aomsState);
        }
        break;
        case Controller::changeStartTime:
        {
            changeStartTime_serializeStates(aomsState);
        }
        break;
        case Controller::changeTimeFactor:
        {
            changeTimeFactor_serializeStates(aomsState);
        }
        break;
        case Controller::accelerometerSettings:
        {
            accelerometerSettings_serializeStates(aomsState);
        }
        break;
        default:
            break;
    }
}

void OMAnimatedController::RunHourglass_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.RunHourglass");
}

void OMAnimatedController::Menu_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.Menu");
}

void OMAnimatedController::changeTimeFactor_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.changeTimeFactor");
}

void OMAnimatedController::changeStartTime_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.changeStartTime");
}

void OMAnimatedController::accelerometerSettings_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.accelerometerSettings");
}

IMPLEMENT_REACTIVE_META_P(Controller, Application, Application, false, OMAnimatedController)
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/Controller.cpp
*********************************************************************/
