/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: Controller
//!	Generated Date	: Wed, 31, Aug 2022  
	File Path	: LPC1769/DefaultConfig/Controller.cpp
*********************************************************************/

#include "Controller.h"
#include "AccelerationMeasuring.h"
#include "ConfigStorage.h"
#include "DisplayTask.h"
#include "TimeCounter.h"
//## package Application

//## class Controller
Controller::Controller(const std::uint32_t defaultStartTime, const std::uint32_t tickTimeController, const std::uint32_t timeFactor) : RXF::Active("Active",RXF::Priority::ABOVE_NORMAL,1024U,10U,getQueueMemory()), backward_threshold(-30), forward_threshold(30), startTime(defaultStartTime), startTimemax(4000000), startTimemin(5000), tickTimeController(tickTimeController), timeFactor(timeFactor), itsAccelerationMeasuring(nullptr), itsConfigStorage(nullptr), itsDisplayTask(nullptr), itsTimeCounter(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState), rootState_timeout(this) {
    setActiveContext(this, true);
    
    //#[ operation Controller(uint32_t,uint32_t,uint32_t)
    //#]
}

Controller::Controller(void) : RXF::Active("Active",RXF::Priority::ABOVE_NORMAL,1024U,10U,getQueueMemory()), backward_threshold(-30), forward_threshold(30), startTimemax(4000000), startTimemin(5000), tickTimeController(10), itsAccelerationMeasuring(nullptr), itsConfigStorage(nullptr), itsDisplayTask(nullptr), itsTimeCounter(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState), rootState_timeout(this) {
    setActiveContext(this, true);
    
}

Controller::~Controller(void) {
    cleanUpRelations();
}

void Controller::raiseStartTime(void) {
    // State action_0
    //#[ state raiseStartTime().action_0.(Entry) 
    startTime += timeFactor;
    //itsEepromData->Store(startTime);
    //#]
    //#[ transition raiseStartTime().2 
    //#]
    if ( startTime >= startTimemax )
    {
        // State action_1
        //#[ state raiseStartTime().action_1.(Entry) 
        startTime = startTimemax;
        //itsEepromData->Store(startTime);
        //#]
    }
    return;
    
}

void Controller::raiseTimeFactor(void) {
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

void Controller::reduceStartTime(void) {
    // State action_0
    //#[ state reduceStartTime().action_0.(Entry) 
    startTime -= timeFactor;
    //itsEepromData->Store(startTime);
    //#]
    //#[ transition reduceStartTime().2 
    //#]
    if ( startTime <= startTimemin )
    {
        // State action_1
        //#[ state reduceStartTime().action_1.(Entry) 
        startTime = startTimemin;
        //itsEepromData->Store(startTime);
        //#]
    }
    return;
    
}

void Controller::reduceTimeFactor(void) {
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
    //#[ operation setTime(uint32_t)
    //#]
}

std::int32_t Controller::getBackward_threshold(void) const {
    return backward_threshold;
}

void Controller::setBackward_threshold(const std::int32_t p_backward_threshold) {
    backward_threshold = p_backward_threshold;
}

std::int32_t Controller::getForward_threshold(void) const {
    return forward_threshold;
}

void Controller::setForward_threshold(const std::int32_t p_forward_threshold) {
    forward_threshold = p_forward_threshold;
}

std::uint32_t Controller::getStartTime(void) const {
    return startTime;
}

void Controller::setStartTime(const std::uint32_t p_startTime) {
    startTime = p_startTime;
}

std::uint8_t Controller::getStartTimeTest(void) const {
    return startTimeTest;
}

void Controller::setStartTimeTest(const std::uint8_t p_startTimeTest) {
    startTimeTest = p_startTimeTest;
}

std::uint32_t Controller::getStartTimemax(void) const {
    return startTimemax;
}

void Controller::setStartTimemax(const std::uint32_t p_startTimemax) {
    startTimemax = p_startTimemax;
}

std::uint32_t Controller::getStartTimemin(void) const {
    return startTimemin;
}

void Controller::setStartTimemin(const std::uint32_t p_startTimemin) {
    startTimemin = p_startTimemin;
}

std::uint32_t Controller::getTickTimeController(void) const {
    return tickTimeController;
}

void Controller::setTickTimeController(const std::uint32_t p_tickTimeController) {
    tickTimeController = p_tickTimeController;
}

std::uint32_t Controller::getTimeFactor(void) const {
    return timeFactor;
}

void Controller::setTimeFactor(const std::uint32_t p_timeFactor) {
    timeFactor = p_timeFactor;
}

AccelerationMeasuring* Controller::getItsAccelerationMeasuring(void) const {
    return itsAccelerationMeasuring;
}

void Controller::setItsAccelerationMeasuring(AccelerationMeasuring* const p_AccelerationMeasuring) {
    itsAccelerationMeasuring = p_AccelerationMeasuring;
}

ConfigStorage* Controller::getItsConfigStorage(void) const {
    return itsConfigStorage;
}

void Controller::setItsConfigStorage(ConfigStorage* const p_ConfigStorage) {
    itsConfigStorage = p_ConfigStorage;
}

DisplayTask* Controller::getItsDisplayTask(void) const {
    return itsDisplayTask;
}

void Controller::setItsDisplayTask(DisplayTask* const p_DisplayTask) {
    itsDisplayTask = p_DisplayTask;
}

TimeCounter* Controller::getItsTimeCounter(void) const {
    return itsTimeCounter;
}

void Controller::setItsTimeCounter(TimeCounter* const p_TimeCounter) {
    itsTimeCounter = p_TimeCounter;
}

bool Controller::startBehavior(void) {
    bool done = false;
    done = RXF::Reactive::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void Controller::cleanUpRelations(void) {
    if(itsAccelerationMeasuring != nullptr)
        {
            itsAccelerationMeasuring = nullptr;
        }
    if(itsConfigStorage != nullptr)
        {
            itsConfigStorage = nullptr;
        }
    if(itsDisplayTask != nullptr)
        {
            itsDisplayTask = nullptr;
        }
    if(itsTimeCounter != nullptr)
        {
            itsTimeCounter = nullptr;
        }
}

void Controller::send_evMenu(void) {
    send( new evMenu()  );
}

void Controller::send_evMenuExit(void) {
    send( new evMenuExit()  );
}

void Controller::send_evRaiseStartTime(void) {
    send( new evRaiseStartTime()  );
}

void Controller::send_evReduceStartTime(void) {
    send( new evReduceStartTime()  );
}

void Controller::send_evRaiseTimeFactor(void) {
    send( new evRaiseTimeFactor()  );
}

void Controller::send_evReduceTimeFactor(void) {
    send( new evReduceTimeFactor()  );
}

void Controller::send_evStartTimeSetting(void) {
    send( new evStartTimeSetting()  );
}

void Controller::send_evTimeFactorSetting(void) {
    send( new evTimeFactorSetting()  );
}

void Controller::send_evGoBack(void) {
    send( new evGoBack()  );
}

void Controller::send_evReset(void) {
    send( new evReset()  );
}

void Controller::send_evCalibrate(void) {
    send( new evCalibrate()  );
}

void Controller::send_evGoBackToRunHourglass(void) {
    send( new evGoBackToRunHourglass()  );
}

void Controller::send_evResetTime(void) {
    send( new evResetTime()  );
}

RXF::Event** Controller::getQueueMemory(void) {
    return queueMemory;
}

void Controller::rootState_entDef(void) {
    {
        //#[ transition 0 
        startTime=itsConfigStorage->getConfigdata();
        itsTimeCounter->setStartTime_ms(startTime);
        itsTimeCounter->GEN(evStart());
        itsDisplayTask->updateDisplay(0, itsTimeCounter->getCurrentTime_ms(), startTime);
        //#]
        rootState_subState = RunHourglass;
        rootState_active = RunHourglass;
        //#[ state RunHourglass.(Entry) 
        if(itsAccelerationMeasuring->getSmoothAccelerationX() > forward_threshold)
        {
        	itsTimeCounter->GEN(evRunBackward());
        }
        else if(itsAccelerationMeasuring->getSmoothAccelerationX() < backward_threshold)
        {
        	itsTimeCounter->GEN(evRunForward());
        }
        else if(itsAccelerationMeasuring->getSmoothAccelerationX() < forward_threshold)
        {
        	itsTimeCounter->GEN(evStop());
        }
        else if(itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
        {
        	itsTimeCounter->GEN(evStop());
        }
        
        //#]
        rootState_timeout.start(tickTimeController);
    }
}

RXF::Reactive::TakeEventStatus Controller::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State Menu
        case Menu:
        {
            if(evTimeFactorSetting_Application_id == getCurrentEvent()->getId())
                {
                    rootState_subState = changeTimeFactor;
                    rootState_active = changeTimeFactor;
                    res = eventConsumed;
                }
            else {
                if(evGoBack_Application_id == getCurrentEvent()->getId())
                    {
                        rootState_subState = RunHourglass;
                        rootState_active = RunHourglass;
                        //#[ state RunHourglass.(Entry) 
                        if(itsAccelerationMeasuring->getSmoothAccelerationX() > forward_threshold)
                        {
                        	itsTimeCounter->GEN(evRunBackward());
                        }
                        else if(itsAccelerationMeasuring->getSmoothAccelerationX() < backward_threshold)
                        {
                        	itsTimeCounter->GEN(evRunForward());
                        }
                        else if(itsAccelerationMeasuring->getSmoothAccelerationX() < forward_threshold)
                        {
                        	itsTimeCounter->GEN(evStop());
                        }
                        else if(itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
                        {
                        	itsTimeCounter->GEN(evStop());
                        }
                        
                        //#]
                        rootState_timeout.start(tickTimeController);
                        res = eventConsumed;
                    }
                else {
                    if(evMenu_Application_id == getCurrentEvent()->getId())
                        {
                            rootState_subState = accelerometerSettings;
                            rootState_active = accelerometerSettings;
                            //#[ state accelerometerSettings.(Entry) 
                            itsDisplayTask->updateDisplay(4, itsTimeCounter->getCurrentTime_ms(), startTime,itsAccelerationMeasuring->getSmoothAccelerationX(), itsAccelerationMeasuring->getSmoothAccelerationY(), itsAccelerationMeasuring->getSmoothAccelerationZ());
                            
                            //#]
                            rootState_timeout.start(tickTimeController);
                            res = eventConsumed;
                        }
                    else {
                        if(evStartTimeSetting_Application_id == getCurrentEvent()->getId())
                            {
                                rootState_subState = changeStartTime;
                                rootState_active = changeStartTime;
                                res = eventConsumed;
                            }
                        }
                        
                    }
                    
                }
                
            
        }
        break;
        // State RunHourglass
        case RunHourglass:
        {
            if(RXF::Event::TIMEOUT_EVENT_ID == getCurrentEvent()->getId())
                {
                    if(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) )
                        {
                            rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                            //#[ state RunHourglass.(Exit) 
                            //itsTimeCounter->GEN(evStop());
                            //#]
                            //#[ transition 3 
                            itsDisplayTask->updateDisplay(0, itsTimeCounter->getCurrentTime_ms(), startTime);
                            //#]
                            rootState_subState = RunHourglass;
                            rootState_active = RunHourglass;
                            //#[ state RunHourglass.(Entry) 
                            if(itsAccelerationMeasuring->getSmoothAccelerationX() > forward_threshold)
                            {
                            	itsTimeCounter->GEN(evRunBackward());
                            }
                            else if(itsAccelerationMeasuring->getSmoothAccelerationX() < backward_threshold)
                            {
                            	itsTimeCounter->GEN(evRunForward());
                            }
                            else if(itsAccelerationMeasuring->getSmoothAccelerationX() < forward_threshold)
                            {
                            	itsTimeCounter->GEN(evStop());
                            }
                            else if(itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
                            {
                            	itsTimeCounter->GEN(evStop());
                            }
                            
                            //#]
                            rootState_timeout.start(tickTimeController);
                            res = eventConsumed;
                        }
                }
            else {
                if(evReset_Application_id == getCurrentEvent()->getId())
                    {
                        rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                        //#[ state RunHourglass.(Exit) 
                        //itsTimeCounter->GEN(evStop());
                        //#]
                        //#[ transition 12 
                        itsTimeCounter->GEN(evResetTime());
                        //#]
                        rootState_subState = RunHourglass;
                        rootState_active = RunHourglass;
                        //#[ state RunHourglass.(Entry) 
                        if(itsAccelerationMeasuring->getSmoothAccelerationX() > forward_threshold)
                        {
                        	itsTimeCounter->GEN(evRunBackward());
                        }
                        else if(itsAccelerationMeasuring->getSmoothAccelerationX() < backward_threshold)
                        {
                        	itsTimeCounter->GEN(evRunForward());
                        }
                        else if(itsAccelerationMeasuring->getSmoothAccelerationX() < forward_threshold)
                        {
                        	itsTimeCounter->GEN(evStop());
                        }
                        else if(itsAccelerationMeasuring->getSmoothAccelerationX() > backward_threshold)
                        {
                        	itsTimeCounter->GEN(evStop());
                        }
                        
                        //#]
                        rootState_timeout.start(tickTimeController);
                        res = eventConsumed;
                    }
                else {
                    if(evMenu_Application_id == getCurrentEvent()->getId())
                        {
                            rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                            //#[ state RunHourglass.(Exit) 
                            //itsTimeCounter->GEN(evStop());
                            //#]
                            //#[ transition 1 
                            itsTimeCounter->GEN(evStop());
                            //#]
                            rootState_subState = Menu;
                            rootState_active = Menu;
                            //#[ state Menu.(Entry) 
                            itsDisplayTask->updateDisplay(1, itsTimeCounter->getCurrentTime_ms(), startTime);
                            //#]
                            res = eventConsumed;
                        }
                    }
                    
                }
                
            
        }
        break;
        // State changeStartTime
        case changeStartTime:
        {
            if(evRaiseStartTime_Application_id == getCurrentEvent()->getId())
                {
                    //#[ transition 5 
                    raiseStartTime();
                    itsDisplayTask->updateDisplay(3, itsTimeCounter->getCurrentTime_ms(), startTime);
                    //#]
                    rootState_subState = changeStartTime;
                    rootState_active = changeStartTime;
                    res = eventConsumed;
                }
            else {
                if(evGoBack_Application_id == getCurrentEvent()->getId())
                    {
                        //#[ transition 7 
                        itsConfigStorage->setConfigdata(startTime);
                        itsTimeCounter->setCurrentTime(startTime);
                        itsTimeCounter->setStartTime_ms(startTime);
                        //#]
                        rootState_subState = Menu;
                        rootState_active = Menu;
                        //#[ state Menu.(Entry) 
                        itsDisplayTask->updateDisplay(1, itsTimeCounter->getCurrentTime_ms(), startTime);
                        //#]
                        res = eventConsumed;
                    }
                else {
                    if(evReduceStartTime_Application_id == getCurrentEvent()->getId())
                        {
                            //#[ transition 6 
                            reduceStartTime();
                            itsDisplayTask->updateDisplay(3, itsTimeCounter->getCurrentTime_ms(), startTime);
                            //#]
                            rootState_subState = changeStartTime;
                            rootState_active = changeStartTime;
                            res = eventConsumed;
                        }
                    }
                    
                }
                
            
        }
        break;
        // State changeTimeFactor
        case changeTimeFactor:
        {
            if(evRaiseTimeFactor_Application_id == getCurrentEvent()->getId())
                {
                    //#[ transition 10 
                    raiseTimeFactor();
                    itsDisplayTask->updateDisplay(2, itsTimeCounter->getCurrentTime_ms(), timeFactor);
                    //#]
                    rootState_subState = changeTimeFactor;
                    rootState_active = changeTimeFactor;
                    res = eventConsumed;
                }
            else {
                if(evReduceTimeFactor_Application_id == getCurrentEvent()->getId())
                    {
                        //#[ transition 11 
                        reduceTimeFactor();
                        itsDisplayTask->updateDisplay(2, itsTimeCounter->getCurrentTime_ms(), timeFactor);
                        //#]
                        rootState_subState = changeTimeFactor;
                        rootState_active = changeTimeFactor;
                        res = eventConsumed;
                    }
                else {
                    if(evGoBack_Application_id == getCurrentEvent()->getId())
                        {
                            rootState_subState = Menu;
                            rootState_active = Menu;
                            //#[ state Menu.(Entry) 
                            itsDisplayTask->updateDisplay(1, itsTimeCounter->getCurrentTime_ms(), startTime);
                            //#]
                            res = eventConsumed;
                        }
                    }
                    
                }
                
            
        }
        break;
        // State accelerometerSettings
        case accelerometerSettings:
        {
            if(RXF::Event::TIMEOUT_EVENT_ID == getCurrentEvent()->getId())
                {
                    if(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) )
                        {
                            rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                            rootState_subState = accelerometerSettings;
                            rootState_active = accelerometerSettings;
                            //#[ state accelerometerSettings.(Entry) 
                            itsDisplayTask->updateDisplay(4, itsTimeCounter->getCurrentTime_ms(), startTime,itsAccelerationMeasuring->getSmoothAccelerationX(), itsAccelerationMeasuring->getSmoothAccelerationY(), itsAccelerationMeasuring->getSmoothAccelerationZ());
                            
                            //#]
                            rootState_timeout.start(tickTimeController);
                            res = eventConsumed;
                        }
                }
            else {
                if(evGoBack_Application_id == getCurrentEvent()->getId())
                    {
                        rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                        rootState_subState = Menu;
                        rootState_active = Menu;
                        //#[ state Menu.(Entry) 
                        itsDisplayTask->updateDisplay(1, itsTimeCounter->getCurrentTime_ms(), startTime);
                        //#]
                        res = eventConsumed;
                    }
                else {
                    if(evStartTimeSetting_Application_id == getCurrentEvent()->getId())
                        {
                            rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                            //#[ transition 16 
                            
                            itsAccelerationMeasuring->GEN(evCalibrate());
                            //#]
                            rootState_subState = accelerometerSettings;
                            rootState_active = accelerometerSettings;
                            //#[ state accelerometerSettings.(Entry) 
                            itsDisplayTask->updateDisplay(4, itsTimeCounter->getCurrentTime_ms(), startTime,itsAccelerationMeasuring->getSmoothAccelerationX(), itsAccelerationMeasuring->getSmoothAccelerationY(), itsAccelerationMeasuring->getSmoothAccelerationZ());
                            
                            //#]
                            rootState_timeout.start(tickTimeController);
                            res = eventConsumed;
                        }
                    }
                    
                }
                
            
        }
        break;
        default:
            break;
    }
    return res;
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/Controller.cpp
*********************************************************************/
