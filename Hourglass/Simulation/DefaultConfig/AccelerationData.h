/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: AccelerationData
//!	Generated Date	: Mon, 1, Aug 2022  
	File Path	: Simulation/DefaultConfig/AccelerationData.h
*********************************************************************/

#ifndef AccelerationData_H
#define AccelerationData_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Application.h"
#include <cstdint>
//## package Application

//## class AccelerationData
class AccelerationData {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedAccelerationData;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    AccelerationData();
    
    virtual ~AccelerationData() = 0;
    
    ////    Operations    ////
    
    //## operation readAccelerationX()
    virtual std::int32_t readAccelerationX() = 0;
    
    //## operation readAccelerationY()
    virtual std::int32_t readAccelerationY() = 0;
    
    //## operation readAccelerationZ()
    virtual std::int32_t readAccelerationZ() = 0;
    
    //## operation readXYZ()
    virtual void readXYZ() = 0;
};

#ifdef _OMINSTRUMENT
class OMAnimatedAccelerationData : virtual public AOMInstance {
    DECLARE_META(AccelerationData, OMAnimatedAccelerationData)
};
#endif // _OMINSTRUMENT

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/AccelerationData.h
*********************************************************************/
