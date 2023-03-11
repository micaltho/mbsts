/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: AccelerationMeasuring
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: LPC1769/DefaultConfig/AccelerationMeasuring.cpp
*********************************************************************/

#include "AccelerationMeasuring.h"
#include "AccelerationData.h"
//## package Application

//## class AccelerationMeasuring
AccelerationMeasuring::AccelerationMeasuring(const std::uint32_t tickTimeAcceleration) : RXF::Active("Active",RXF::Priority::NORMAL,1024U,10U,getQueueMemory()), accelerationX0(0), accelerationY0(0), accelerationZ0(0), avgAccelerationX(0), avgAccelerationY(0), avgAccelerationZ(0), currentAccelerationX(0), currentAccelerationY(0), currentAccelerationZ(0), intervall(10), n(0), smoothAccelerationX(0), smoothAccelerationY(0), smoothAccelerationZ(0), tickTimeAcceleration(tickTimeAcceleration), itsAccelerationData(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState), rootState_timeout(this) {
    setActiveContext(this, true);
    
    //#[ operation AccelerationMeasuring(uint32_t)
    //#]
}

AccelerationMeasuring::AccelerationMeasuring(void) : RXF::Active("Active",RXF::Priority::NORMAL,1024U,10U,getQueueMemory()), accelerationX0(0), accelerationY0(0), accelerationZ0(0), avgAccelerationX(0), avgAccelerationY(0), avgAccelerationZ(0), currentAccelerationX(0), currentAccelerationY(0), currentAccelerationZ(0), intervall(10), n(0), smoothAccelerationX(0), smoothAccelerationY(0), smoothAccelerationZ(0), itsAccelerationData(nullptr), rootState_subState(OMNonState), rootState_active(OMNonState), rootState_timeout(this) {
    setActiveContext(this, true);
    
}

AccelerationMeasuring::~AccelerationMeasuring(void) {
    cleanUpRelations();
}

void AccelerationMeasuring::calibrate(void) {
    //#[ operation calibrate()
    accelerationX0 = itsAccelerationData->readAccelerationX();
    accelerationY0 = itsAccelerationData->readAccelerationY();
    accelerationZ0 = itsAccelerationData->readAccelerationZ();
    //#]
}

std::int32_t AccelerationMeasuring::getSmoothAccelerationX(void) {
    //#[ operation getSmoothAccelerationX()
    return smoothAccelerationX;
    //#]
}

std::int32_t AccelerationMeasuring::getSmoothAccelerationY(void) {
    //#[ operation getSmoothAccelerationY()
    return smoothAccelerationY;
    //#]
}

std::int32_t AccelerationMeasuring::getSmoothAccelerationZ(void) {
    //#[ operation getSmoothAccelerationZ()
    return smoothAccelerationZ;
    //#]
}

void AccelerationMeasuring::measure(void) {
    // State action_0
    //#[ state measure().action_0.(Entry) 
    itsAccelerationData->readXYZ();
    currentAccelerationX = itsAccelerationData->readAccelerationX() - accelerationX0;
    currentAccelerationY = itsAccelerationData->readAccelerationY() - accelerationY0;
    currentAccelerationZ = itsAccelerationData->readAccelerationZ() - accelerationZ0;
    avgAccelerationX += currentAccelerationX;
    avgAccelerationY += currentAccelerationY;
    avgAccelerationZ += currentAccelerationZ;
    ++n;
    
    //#]
    //#[ transition measure().2 
    //#]
    if ( n == intervall )
    {
        // State action_1
        //#[ state measure().action_1.(Entry) 
        smoothAccelerationX = avgAccelerationX/intervall;
        smoothAccelerationY  = avgAccelerationY/intervall;
        smoothAccelerationZ  = avgAccelerationY/intervall;
        n = 0;
        avgAccelerationX = 0; 
        avgAccelerationY = 0;
        avgAccelerationY = 0;
        
        
        
        //#]
    }
    return;
    
}

std::int32_t AccelerationMeasuring::getAccelerationX0(void) const {
    return accelerationX0;
}

void AccelerationMeasuring::setAccelerationX0(const std::int32_t p_accelerationX0) {
    accelerationX0 = p_accelerationX0;
}

std::int32_t AccelerationMeasuring::getAccelerationY0(void) const {
    return accelerationY0;
}

void AccelerationMeasuring::setAccelerationY0(const std::int32_t p_accelerationY0) {
    accelerationY0 = p_accelerationY0;
}

std::int32_t AccelerationMeasuring::getAccelerationZ0(void) const {
    return accelerationZ0;
}

void AccelerationMeasuring::setAccelerationZ0(const std::int32_t p_accelerationZ0) {
    accelerationZ0 = p_accelerationZ0;
}

std::int32_t AccelerationMeasuring::getAvgAccelerationX(void) const {
    return avgAccelerationX;
}

void AccelerationMeasuring::setAvgAccelerationX(const std::int32_t p_avgAccelerationX) {
    avgAccelerationX = p_avgAccelerationX;
}

std::int32_t AccelerationMeasuring::getAvgAccelerationY(void) const {
    return avgAccelerationY;
}

void AccelerationMeasuring::setAvgAccelerationY(const std::int32_t p_avgAccelerationY) {
    avgAccelerationY = p_avgAccelerationY;
}

std::int32_t AccelerationMeasuring::getAvgAccelerationZ(void) const {
    return avgAccelerationZ;
}

void AccelerationMeasuring::setAvgAccelerationZ(const std::int32_t p_avgAccelerationZ) {
    avgAccelerationZ = p_avgAccelerationZ;
}

std::int32_t AccelerationMeasuring::getCurrentAccelerationX(void) const {
    return currentAccelerationX;
}

void AccelerationMeasuring::setCurrentAccelerationX(const std::int32_t p_currentAccelerationX) {
    currentAccelerationX = p_currentAccelerationX;
}

std::int32_t AccelerationMeasuring::getCurrentAccelerationY(void) const {
    return currentAccelerationY;
}

void AccelerationMeasuring::setCurrentAccelerationY(const std::int32_t p_currentAccelerationY) {
    currentAccelerationY = p_currentAccelerationY;
}

std::int32_t AccelerationMeasuring::getCurrentAccelerationZ(void) const {
    return currentAccelerationZ;
}

void AccelerationMeasuring::setCurrentAccelerationZ(const std::int32_t p_currentAccelerationZ) {
    currentAccelerationZ = p_currentAccelerationZ;
}

std::int32_t AccelerationMeasuring::getIntervall(void) const {
    return intervall;
}

void AccelerationMeasuring::setIntervall(const std::int32_t p_intervall) {
    intervall = p_intervall;
}

std::uint32_t AccelerationMeasuring::getN(void) const {
    return n;
}

void AccelerationMeasuring::setN(const std::uint32_t p_n) {
    n = p_n;
}

void AccelerationMeasuring::setSmoothAccelerationX(const std::int32_t p_smoothAccelerationX) {
    smoothAccelerationX = p_smoothAccelerationX;
}

void AccelerationMeasuring::setSmoothAccelerationY(const std::int32_t p_smoothAccelerationY) {
    smoothAccelerationY = p_smoothAccelerationY;
}

void AccelerationMeasuring::setSmoothAccelerationZ(const std::int32_t p_smoothAccelerationZ) {
    smoothAccelerationZ = p_smoothAccelerationZ;
}

std::uint32_t AccelerationMeasuring::getTickTimeAcceleration(void) const {
    return tickTimeAcceleration;
}

void AccelerationMeasuring::setTickTimeAcceleration(const std::uint32_t p_tickTimeAcceleration) {
    tickTimeAcceleration = p_tickTimeAcceleration;
}

AccelerationData* AccelerationMeasuring::getItsAccelerationData(void) const {
    return itsAccelerationData;
}

void AccelerationMeasuring::setItsAccelerationData(AccelerationData* const p_AccelerationData) {
    itsAccelerationData = p_AccelerationData;
}

bool AccelerationMeasuring::startBehavior(void) {
    bool done = false;
    done = RXF::Reactive::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void AccelerationMeasuring::cleanUpRelations(void) {
    if(itsAccelerationData != nullptr)
        {
            itsAccelerationData = nullptr;
        }
}

void AccelerationMeasuring::send_evCalibrate(void) {
    send( new evCalibrate()  );
}

RXF::Event** AccelerationMeasuring::getQueueMemory(void) {
    return queueMemory;
}

void AccelerationMeasuring::rootState_entDef(void) {
    {
        rootState_subState = sMeasure;
        rootState_active = sMeasure;
        rootState_timeout.start(tickTimeAcceleration);
    }
}

RXF::Reactive::TakeEventStatus AccelerationMeasuring::rootState_processEvent(void) {
    RXF::Reactive::TakeEventStatus res = eventNotConsumed;
    // State sMeasure
    if(rootState_active == sMeasure)
        {
            if(evCalibrate_Application_id == getCurrentEvent()->getId())
                {
                    rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                    //#[ transition 2 
                    calibrate();
                    //#]
                    rootState_subState = sMeasure;
                    rootState_active = sMeasure;
                    rootState_timeout.start(tickTimeAcceleration);
                    res = eventConsumed;
                }
            else {
                if(RXF::Event::TIMEOUT_EVENT_ID == getCurrentEvent()->getId())
                    {
                        if(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) )
                            {
                                rootState_timeout.cancel(getCurrentEvent() == static_cast<RXF::Event*>(&rootState_timeout) );
                                //#[ transition 1 
                                measure();
                                //#]
                                rootState_subState = sMeasure;
                                rootState_active = sMeasure;
                                rootState_timeout.start(tickTimeAcceleration);
                                res = eventConsumed;
                            }
                    }
                }
                
            
        }
    return res;
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/AccelerationMeasuring.cpp
*********************************************************************/
