/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: AccelerationMeasuring
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/AccelerationMeasuring.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#define _OMSTATECHART_ANIMATED

#include "AccelerationMeasuring.h"
#include "AccelerationData.h"
#define Application_AccelerationMeasuring_AccelerationMeasuring_SERIALIZE aomsmethod->addAttribute("tickTimeAcceleration", UNKNOWN2STRING(tickTimeAcceleration));

#define OM_Application_AccelerationMeasuring_AccelerationMeasuring_1_SERIALIZE OM_NO_OP

#define Application_AccelerationMeasuring_calibrate_SERIALIZE OM_NO_OP

#define Application_AccelerationMeasuring_getSmoothAccelerationX_SERIALIZE OM_NO_OP

#define Application_AccelerationMeasuring_getSmoothAccelerationY_SERIALIZE OM_NO_OP

#define Application_AccelerationMeasuring_getSmoothAccelerationZ_SERIALIZE OM_NO_OP

#define Application_AccelerationMeasuring_measure_SERIALIZE OM_NO_OP

//## package Application

//## class AccelerationMeasuring
AccelerationMeasuring::AccelerationMeasuring(const std::uint32_t tickTimeAcceleration, IOxfActive* theActiveContext) : accelerationX0(0), accelerationY0(0), accelerationZ0(0), avgAccelerationX(0), avgAccelerationY(0), avgAccelerationZ(0), currentAccelerationX(0), currentAccelerationY(0), currentAccelerationZ(0), intervall(10), n(0), smoothAccelerationX(0), smoothAccelerationY(0), smoothAccelerationZ(0), tickTimeAcceleration(tickTimeAcceleration) {
    NOTIFY_ACTIVE_CONSTRUCTOR(AccelerationMeasuring, AccelerationMeasuring(const std::uint32_t), 1, Application_AccelerationMeasuring_AccelerationMeasuring_SERIALIZE);
    itsAccelerationData = NULL;
    setActiveContext(this, true);
    initStatechart();
    //#[ operation AccelerationMeasuring(uint32_t)
    //#]
}

AccelerationMeasuring::AccelerationMeasuring(IOxfActive* theActiveContext) : accelerationX0(0), accelerationY0(0), accelerationZ0(0), avgAccelerationX(0), avgAccelerationY(0), avgAccelerationZ(0), currentAccelerationX(0), currentAccelerationY(0), currentAccelerationZ(0), intervall(10), n(0), smoothAccelerationX(0), smoothAccelerationY(0), smoothAccelerationZ(0) {
    NOTIFY_ACTIVE_CONSTRUCTOR(AccelerationMeasuring, AccelerationMeasuring(), 0, OM_Application_AccelerationMeasuring_AccelerationMeasuring_1_SERIALIZE);
    setActiveContext(this, true);
    itsAccelerationData = NULL;
    initStatechart();
}

AccelerationMeasuring::~AccelerationMeasuring() {
    NOTIFY_DESTRUCTOR(~AccelerationMeasuring, true);
    cleanUpRelations();
    cancelTimeouts();
}

void AccelerationMeasuring::calibrate() {
    NOTIFY_OPERATION(calibrate, calibrate(), 0, Application_AccelerationMeasuring_calibrate_SERIALIZE);
    //#[ operation calibrate()
    accelerationX0 = itsAccelerationData->readAccelerationX();
    accelerationY0 = itsAccelerationData->readAccelerationY();
    accelerationZ0 = itsAccelerationData->readAccelerationZ();
    //#]
}

std::int32_t AccelerationMeasuring::getSmoothAccelerationX() {
    NOTIFY_OPERATION(getSmoothAccelerationX, getSmoothAccelerationX(), 0, Application_AccelerationMeasuring_getSmoothAccelerationX_SERIALIZE);
    //#[ operation getSmoothAccelerationX()
    return smoothAccelerationX;
    //#]
}

std::int32_t AccelerationMeasuring::getSmoothAccelerationY() {
    NOTIFY_OPERATION(getSmoothAccelerationY, getSmoothAccelerationY(), 0, Application_AccelerationMeasuring_getSmoothAccelerationY_SERIALIZE);
    //#[ operation getSmoothAccelerationY()
    return smoothAccelerationY;
    //#]
}

std::int32_t AccelerationMeasuring::getSmoothAccelerationZ() {
    NOTIFY_OPERATION(getSmoothAccelerationZ, getSmoothAccelerationZ(), 0, Application_AccelerationMeasuring_getSmoothAccelerationZ_SERIALIZE);
    //#[ operation getSmoothAccelerationZ()
    return smoothAccelerationZ;
    //#]
}

void AccelerationMeasuring::measure() {
    NOTIFY_OPERATION(measure, measure(), 0, Application_AccelerationMeasuring_measure_SERIALIZE);
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

std::int32_t AccelerationMeasuring::getAccelerationX0() const {
    return accelerationX0;
}

void AccelerationMeasuring::setAccelerationX0(std::int32_t p_accelerationX0) {
    accelerationX0 = p_accelerationX0;
}

std::int32_t AccelerationMeasuring::getAccelerationY0() const {
    return accelerationY0;
}

void AccelerationMeasuring::setAccelerationY0(std::int32_t p_accelerationY0) {
    accelerationY0 = p_accelerationY0;
}

std::int32_t AccelerationMeasuring::getAccelerationZ0() const {
    return accelerationZ0;
}

void AccelerationMeasuring::setAccelerationZ0(std::int32_t p_accelerationZ0) {
    accelerationZ0 = p_accelerationZ0;
}

std::int32_t AccelerationMeasuring::getAvgAccelerationX() const {
    return avgAccelerationX;
}

void AccelerationMeasuring::setAvgAccelerationX(std::int32_t p_avgAccelerationX) {
    avgAccelerationX = p_avgAccelerationX;
}

std::int32_t AccelerationMeasuring::getAvgAccelerationY() const {
    return avgAccelerationY;
}

void AccelerationMeasuring::setAvgAccelerationY(std::int32_t p_avgAccelerationY) {
    avgAccelerationY = p_avgAccelerationY;
}

std::int32_t AccelerationMeasuring::getAvgAccelerationZ() const {
    return avgAccelerationZ;
}

void AccelerationMeasuring::setAvgAccelerationZ(std::int32_t p_avgAccelerationZ) {
    avgAccelerationZ = p_avgAccelerationZ;
}

std::int32_t AccelerationMeasuring::getCurrentAccelerationX() const {
    return currentAccelerationX;
}

void AccelerationMeasuring::setCurrentAccelerationX(std::int32_t p_currentAccelerationX) {
    currentAccelerationX = p_currentAccelerationX;
}

std::int32_t AccelerationMeasuring::getCurrentAccelerationY() const {
    return currentAccelerationY;
}

void AccelerationMeasuring::setCurrentAccelerationY(std::int32_t p_currentAccelerationY) {
    currentAccelerationY = p_currentAccelerationY;
}

std::int32_t AccelerationMeasuring::getCurrentAccelerationZ() const {
    return currentAccelerationZ;
}

void AccelerationMeasuring::setCurrentAccelerationZ(std::int32_t p_currentAccelerationZ) {
    currentAccelerationZ = p_currentAccelerationZ;
}

std::int32_t AccelerationMeasuring::getIntervall() const {
    return intervall;
}

void AccelerationMeasuring::setIntervall(std::int32_t p_intervall) {
    intervall = p_intervall;
}

std::uint32_t AccelerationMeasuring::getN() const {
    return n;
}

void AccelerationMeasuring::setN(std::uint32_t p_n) {
    n = p_n;
}

void AccelerationMeasuring::setSmoothAccelerationX(std::int32_t p_smoothAccelerationX) {
    smoothAccelerationX = p_smoothAccelerationX;
}

void AccelerationMeasuring::setSmoothAccelerationY(std::int32_t p_smoothAccelerationY) {
    smoothAccelerationY = p_smoothAccelerationY;
}

void AccelerationMeasuring::setSmoothAccelerationZ(std::int32_t p_smoothAccelerationZ) {
    smoothAccelerationZ = p_smoothAccelerationZ;
}

std::uint32_t AccelerationMeasuring::getTickTimeAcceleration() const {
    return tickTimeAcceleration;
}

void AccelerationMeasuring::setTickTimeAcceleration(std::uint32_t p_tickTimeAcceleration) {
    tickTimeAcceleration = p_tickTimeAcceleration;
}

AccelerationData* AccelerationMeasuring::getItsAccelerationData() const {
    return itsAccelerationData;
}

void AccelerationMeasuring::setItsAccelerationData(AccelerationData* p_AccelerationData) {
    itsAccelerationData = p_AccelerationData;
    if(p_AccelerationData != NULL)
        {
            NOTIFY_RELATION_ITEM_ADDED("itsAccelerationData", p_AccelerationData, false, true);
        }
    else
        {
            NOTIFY_RELATION_CLEARED("itsAccelerationData");
        }
}

bool AccelerationMeasuring::startBehavior() {
    bool done = false;
    done = OMReactive::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void AccelerationMeasuring::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void AccelerationMeasuring::cleanUpRelations() {
    if(itsAccelerationData != NULL)
        {
            NOTIFY_RELATION_CLEARED("itsAccelerationData");
            itsAccelerationData = NULL;
        }
}

void AccelerationMeasuring::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool AccelerationMeasuring::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void AccelerationMeasuring::rootState_entDef() {
    {
        NOTIFY_STATE_ENTERED("ROOT");
        NOTIFY_TRANSITION_STARTED("0");
        NOTIFY_STATE_ENTERED("ROOT.sMeasure");
        rootState_subState = sMeasure;
        rootState_active = sMeasure;
        rootState_timeout = scheduleTimeout(tickTimeAcceleration, "ROOT.sMeasure");
        NOTIFY_TRANSITION_TERMINATED("0");
    }
}

IOxfReactive::TakeEventStatus AccelerationMeasuring::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State sMeasure
    if(rootState_active == sMeasure)
        {
            if(IS_EVENT_TYPE_OF(evCalibrate_Application_id))
                {
                    NOTIFY_TRANSITION_STARTED("2");
                    cancel(rootState_timeout);
                    NOTIFY_STATE_EXITED("ROOT.sMeasure");
                    //#[ transition 2 
                    calibrate();
                    //#]
                    NOTIFY_STATE_ENTERED("ROOT.sMeasure");
                    rootState_subState = sMeasure;
                    rootState_active = sMeasure;
                    rootState_timeout = scheduleTimeout(tickTimeAcceleration, "ROOT.sMeasure");
                    NOTIFY_TRANSITION_TERMINATED("2");
                    res = eventConsumed;
                }
            else if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            NOTIFY_TRANSITION_STARTED("1");
                            cancel(rootState_timeout);
                            NOTIFY_STATE_EXITED("ROOT.sMeasure");
                            //#[ transition 1 
                            measure();
                            //#]
                            NOTIFY_STATE_ENTERED("ROOT.sMeasure");
                            rootState_subState = sMeasure;
                            rootState_active = sMeasure;
                            rootState_timeout = scheduleTimeout(tickTimeAcceleration, "ROOT.sMeasure");
                            NOTIFY_TRANSITION_TERMINATED("1");
                            res = eventConsumed;
                        }
                }
            
        }
    return res;
}

#ifdef _OMINSTRUMENT
void OMAnimatedAccelerationMeasuring::serializeAttributes(AOMSAttributes* aomsAttributes) const {
    aomsAttributes->addAttribute("currentAccelerationX", UNKNOWN2STRING(myReal->currentAccelerationX));
    aomsAttributes->addAttribute("currentAccelerationY", UNKNOWN2STRING(myReal->currentAccelerationY));
    aomsAttributes->addAttribute("currentAccelerationZ", UNKNOWN2STRING(myReal->currentAccelerationZ));
    aomsAttributes->addAttribute("intervall", UNKNOWN2STRING(myReal->intervall));
    aomsAttributes->addAttribute("smoothAccelerationX", UNKNOWN2STRING(myReal->smoothAccelerationX));
    aomsAttributes->addAttribute("smoothAccelerationY", UNKNOWN2STRING(myReal->smoothAccelerationY));
    aomsAttributes->addAttribute("smoothAccelerationZ", UNKNOWN2STRING(myReal->smoothAccelerationZ));
    aomsAttributes->addAttribute("avgAccelerationX", UNKNOWN2STRING(myReal->avgAccelerationX));
    aomsAttributes->addAttribute("avgAccelerationY", UNKNOWN2STRING(myReal->avgAccelerationY));
    aomsAttributes->addAttribute("avgAccelerationZ", UNKNOWN2STRING(myReal->avgAccelerationZ));
    aomsAttributes->addAttribute("accelerationX0", UNKNOWN2STRING(myReal->accelerationX0));
    aomsAttributes->addAttribute("accelerationY0", UNKNOWN2STRING(myReal->accelerationY0));
    aomsAttributes->addAttribute("accelerationZ0", UNKNOWN2STRING(myReal->accelerationZ0));
    aomsAttributes->addAttribute("tickTimeAcceleration", UNKNOWN2STRING(myReal->tickTimeAcceleration));
    aomsAttributes->addAttribute("n", UNKNOWN2STRING(myReal->n));
}

void OMAnimatedAccelerationMeasuring::serializeRelations(AOMSRelations* aomsRelations) const {
    aomsRelations->addRelation("itsAccelerationData", false, true);
    if(myReal->itsAccelerationData)
        {
            aomsRelations->ADD_ITEM(myReal->itsAccelerationData);
        }
}

void OMAnimatedAccelerationMeasuring::rootState_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT");
    if(myReal->rootState_subState == AccelerationMeasuring::sMeasure)
        {
            sMeasure_serializeStates(aomsState);
        }
}

void OMAnimatedAccelerationMeasuring::sMeasure_serializeStates(AOMSState* aomsState) const {
    aomsState->addState("ROOT.sMeasure");
}

IMPLEMENT_REACTIVE_META_P(AccelerationMeasuring, Application, Application, false, OMAnimatedAccelerationMeasuring)
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/AccelerationMeasuring.cpp
*********************************************************************/
