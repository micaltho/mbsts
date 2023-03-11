/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: AccelerationMeasuring
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: LPC1769/DefaultConfig/AccelerationMeasuring.h
*********************************************************************/

#ifndef AccelerationMeasuring_H
#define AccelerationMeasuring_H

#include "Application.h"
#include "RXF_Active.h"
#include "RXF_Reactive.h"
#include "RXF_Event.h"
#include <cstdint>
class AccelerationData;

//## package Application

//## class AccelerationMeasuring
class AccelerationMeasuring : public RXF::Active, public RXF::Reactive {
    ////    Constructors and destructors    ////
    
public :

    //## operation AccelerationMeasuring(uint32_t)
    AccelerationMeasuring(const std::uint32_t tickTimeAcceleration);
    
    AccelerationMeasuring(void);
    
    virtual ~AccelerationMeasuring(void);
    
    ////    Operations    ////
    
    //## operation calibrate()
    void calibrate(void);
    
    //## operation getSmoothAccelerationX()
    std::int32_t getSmoothAccelerationX(void);
    
    //## operation getSmoothAccelerationY()
    std::int32_t getSmoothAccelerationY(void);
    
    //## operation getSmoothAccelerationZ()
    std::int32_t getSmoothAccelerationZ(void);
    
    void measure(void);
    
    ////    Additional operations    ////
    
    std::int32_t getAccelerationX0(void) const;
    
    void setAccelerationX0(const std::int32_t p_accelerationX0);
    
    std::int32_t getAccelerationY0(void) const;
    
    void setAccelerationY0(const std::int32_t p_accelerationY0);
    
    std::int32_t getAccelerationZ0(void) const;
    
    void setAccelerationZ0(const std::int32_t p_accelerationZ0);
    
    std::int32_t getAvgAccelerationX(void) const;
    
    void setAvgAccelerationX(const std::int32_t p_avgAccelerationX);
    
    std::int32_t getAvgAccelerationY(void) const;
    
    void setAvgAccelerationY(const std::int32_t p_avgAccelerationY);
    
    std::int32_t getAvgAccelerationZ(void) const;
    
    void setAvgAccelerationZ(const std::int32_t p_avgAccelerationZ);
    
    std::int32_t getCurrentAccelerationX(void) const;
    
    void setCurrentAccelerationX(const std::int32_t p_currentAccelerationX);
    
    std::int32_t getCurrentAccelerationY(void) const;
    
    void setCurrentAccelerationY(const std::int32_t p_currentAccelerationY);
    
    std::int32_t getCurrentAccelerationZ(void) const;
    
    void setCurrentAccelerationZ(const std::int32_t p_currentAccelerationZ);
    
    std::int32_t getIntervall(void) const;
    
    void setIntervall(const std::int32_t p_intervall);
    
    std::uint32_t getN(void) const;
    
    void setN(const std::uint32_t p_n);
    
    void setSmoothAccelerationX(const std::int32_t p_smoothAccelerationX);
    
    void setSmoothAccelerationY(const std::int32_t p_smoothAccelerationY);
    
    void setSmoothAccelerationZ(const std::int32_t p_smoothAccelerationZ);
    
    std::uint32_t getTickTimeAcceleration(void) const;
    
    void setTickTimeAcceleration(const std::uint32_t p_tickTimeAcceleration);
    
    AccelerationData* getItsAccelerationData(void) const;
    
    void setItsAccelerationData(AccelerationData* const p_AccelerationData);
    
    virtual bool startBehavior(void);

protected :

    void cleanUpRelations(void);

public :

    virtual void send_evCalibrate(void);

private :

    RXF::Event** getQueueMemory(void);
    
    ////    Attributes    ////

protected :

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
    inline bool rootState_IN(void) const;
    
    // sMeasure:
    inline bool sMeasure_IN(void) const;

protected :

    virtual void rootState_entDef(void);
    
    virtual RXF::Reactive::TakeEventStatus rootState_processEvent(void);
    
    ////    Framework    ////
    
    enum AccelerationMeasuring_Enum {
        OMNonState = 0,
        sMeasure = 1
    };

private :

    AccelerationMeasuring_Enum rootState_subState;
    
    AccelerationMeasuring_Enum rootState_active;
    
    RXF::TimeoutEvent rootState_timeout;
    
    RXF::Event* queueMemory[10U];
};

inline bool AccelerationMeasuring::rootState_IN(void) const {
    return true;
}

inline bool AccelerationMeasuring::sMeasure_IN(void) const {
    return rootState_subState == sMeasure;
}

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/AccelerationMeasuring.h
*********************************************************************/
