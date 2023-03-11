/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: AccelerationData
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/AccelerationData.h
*********************************************************************/

#ifndef AccelerationData_H
#define AccelerationData_H

#include "Application.h"
#include <cstdint>
//## package Application

//## class AccelerationData
class AccelerationData {
    ////    Constructors and destructors    ////
    
public :

    AccelerationData(void);
    
    virtual ~AccelerationData(void) = 0;
    
    ////    Operations    ////
    
    //## operation readAccelerationX()
    virtual std::int32_t readAccelerationX(void) = 0;
    
    //## operation readAccelerationY()
    virtual std::int32_t readAccelerationY(void) = 0;
    
    //## operation readAccelerationZ()
    virtual std::int32_t readAccelerationZ(void) = 0;
    
    //## operation readXYZ()
    virtual void readXYZ(void) = 0;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/AccelerationData.h
*********************************************************************/
