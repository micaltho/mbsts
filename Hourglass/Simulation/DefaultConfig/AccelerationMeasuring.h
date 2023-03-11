/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: AccelerationMeasuring
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/AccelerationMeasuring.h
*********************************************************************/

#ifndef AccelerationMeasuring_H
#define AccelerationMeasuring_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Application.h"
#include <oxf/omthread.h>
#include <oxf/omreactive.h>
#include <oxf/state.h>
#include <oxf/event.h>
#include <cstdint>
class AccelerationData;

//## package Application

//## class AccelerationMeasuring
class AccelerationMeasuring : public OMThread, public OMReactive {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedAccelerationMeasuring;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    //## operation AccelerationMeasuring(uint32_t)
    AccelerationMeasuring(const std::uint32_t tickTimeAcceleration, IOxfActive* theActiveContext = 0);
    
    AccelerationMeasuring(IOxfActive* theActiveContext = 0);
    
    ~AccelerationMeasuring();
    
    ////    Operations    ////
    
    //## operation calibrate()
    void calibrate();
    
    //## operation getSmoothAccelerationX()
    std::int32_t getSmoothAccelerationX();
    
    //## operation getSmoothAccelerationY()
    std::int32_t getSmoothAccelerationY();
    
    //## operation getSmoothAccelerationZ()
    std::int32_t getSmoothAccelerationZ();
    
    void measure();
    
    ////    Additional operations    ////
    
    std::int32_t getAccelerationX0() const;
    
    void setAccelerationX0(std::int32_t p_accelerationX0);
    
    std::int32_t getAccelerationY0() const;
    
    void setAccelerationY0(std::int32_t p_accelerationY0);
    
    std::int32_t getAccelerationZ0() const;
    
    void setAccelerationZ0(std::int32_t p_accelerationZ0);
    
    std::int32_t getAvgAccelerationX() const;
    
    void setAvgAccelerationX(std::int32_t p_avgAccelerationX);
    
    std::int32_t getAvgAccelerationY() const;
    
    void setAvgAccelerationY(std::int32_t p_avgAccelerationY);
    
    std::int32_t getAvgAccelerationZ() const;
    
    void setAvgAccelerationZ(std::int32_t p_avgAccelerationZ);
    
    std::int32_t getCurrentAccelerationX() const;
    
    void setCurrentAccelerationX(std::int32_t p_currentAccelerationX);
    
    std::int32_t getCurrentAccelerationY() const;
    
    void setCurrentAccelerationY(std::int32_t p_currentAccelerationY);
    
    std::int32_t getCurrentAccelerationZ() const;
    
    void setCurrentAccelerationZ(std::int32_t p_currentAccelerationZ);
    
    std::int32_t getIntervall() const;
    
    void setIntervall(std::int32_t p_intervall);
    
    std::uint32_t getN() const;
    
    void setN(std::uint32_t p_n);
    
    void setSmoothAccelerationX(std::int32_t p_smoothAccelerationX);
    
    void setSmoothAccelerationY(std::int32_t p_smoothAccelerationY);
    
    void setSmoothAccelerationZ(std::int32_t p_smoothAccelerationZ);
    
    std::uint32_t getTickTimeAcceleration() const;
    
    void setTickTimeAcceleration(std::uint32_t p_tickTimeAcceleration);
    
    AccelerationData* getItsAccelerationData() const;
    
    void setItsAccelerationData(AccelerationData* p_AccelerationData);
    
    virtual bool startBehavior();

protected :

    void initStatechart();
    
    void cleanUpRelations();
    
    void cancelTimeouts();
    
    bool cancelTimeout(const IOxfTimeout* arg);
    
    ////    Attributes    ////
    
    std::int32_t accelerationX0;		//## attribute accelerationX0
    
    std::int32_t accelerationY0;		//## attribute accelerationY0
    
    std::int32_t accelerationZ0;		//## attribute accelerationZ0
    
    std::int32_t avgAccelerationX;		//## attribute avgAccelerationX
    
    std::int32_t avgAccelerationY;		//## attribute avgAccelerationY
    
    std::int32_t avgAccelerationZ;		//## attribute avgAccelerationZ
    
    std::int32_t currentAccelerationX;		//## attribute currentAccelerationX
    
    std::int32_t currentAccelerationY;		//## attribute currentAccelerationY
    
    std::int32_t currentAccelerationZ;		//## attribute currentAccelerationZ
    
    std::int32_t intervall;		//## attribute intervall
    
    std::uint32_t n;		//## attribute n
    
    std::int32_t smoothAccelerationX;		//## attribute smoothAccelerationX
    
    std::int32_t smoothAccelerationY;		//## attribute smoothAccelerationY
    
    std::int32_t smoothAccelerationZ;		//## attribute smoothAccelerationZ
    
    std::uint32_t tickTimeAcceleration;		//## attribute tickTimeAcceleration
    
    ////    Relations and components    ////
    
    AccelerationData* itsAccelerationData;
    
    ////    Framework operations    ////

public :

    // rootState:
    inline bool rootState_IN() const;
    
    virtual void rootState_entDef();
    
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // sMeasure:
    inline bool sMeasure_IN() const;
    
    ////    Framework    ////

protected :

    enum AccelerationMeasuring_Enum {
        OMNonState = 0,
        sMeasure = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
};

#ifdef _OMINSTRUMENT
class OMAnimatedAccelerationMeasuring : virtual public AOMInstance {
    DECLARE_REACTIVE_META(AccelerationMeasuring, OMAnimatedAccelerationMeasuring)
    
    ////    Framework operations    ////
    
public :

    virtual void serializeAttributes(AOMSAttributes* aomsAttributes) const;
    
    virtual void serializeRelations(AOMSRelations* aomsRelations) const;
    
    void rootState_serializeStates(AOMSState* aomsState) const;
    
    void sMeasure_serializeStates(AOMSState* aomsState) const;
};
#endif // _OMINSTRUMENT

inline bool AccelerationMeasuring::rootState_IN() const {
    return true;
}

inline bool AccelerationMeasuring::sMeasure_IN() const {
    return rootState_subState == sMeasure;
}

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/AccelerationMeasuring.h
*********************************************************************/
