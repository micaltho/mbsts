/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCAccelerationSensor
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCAccelerationSensor.h
*********************************************************************/

#ifndef LPCAccelerationSensor_H
#define LPCAccelerationSensor_H

#include "LPC1769.h"
#include "AccelerationData.h"
#include <mma7455.h>
#include <cstdint>
//## package LPC1769

//## class LPCAccelerationSensor
class LPCAccelerationSensor : public AccelerationData {
    ////    Constructors and destructors    ////
    
public :

    //## operation LPCAccelerationSensor()
    LPCAccelerationSensor(void);
    
    virtual ~LPCAccelerationSensor(void);
    
    ////    Operations    ////
    
    //## operation readAccelerationX()
    virtual std::int32_t readAccelerationX(void);
    
    //## operation readAccelerationY()
    virtual std::int32_t readAccelerationY(void);
    
    //## operation readAccelerationZ()
    virtual std::int32_t readAccelerationZ(void);
    
    //## operation readXYZ()
    void readXYZ(void);
    
    ////    Additional operations    ////
    
    std::int8_t getAccelerationX(void) const;
    
    void setAccelerationX(const std::int8_t p_accelerationX);
    
    std::int8_t getAccelerationY(void) const;
    
    void setAccelerationY(const std::int8_t p_accelerationY);
    
    std::int8_t getAccelerationZ(void) const;
    
    void setAccelerationZ(const std::int8_t p_accelerationZ);
    
    Platform::BSP::MMA7455* getItsMMA7455(void) const;
    
    ////    Attributes    ////

protected :

    std::int8_t accelerationX;		//## attribute accelerationX
    
    std::int8_t accelerationY;		//## attribute accelerationY
    
    std::int8_t accelerationZ;		//## attribute accelerationZ
    
    ////    Relations and components    ////
    
    Platform::BSP::MMA7455 itsMMA7455;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCAccelerationSensor.h
*********************************************************************/
