/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: EepromData
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/EepromData.h
*********************************************************************/

#ifndef EepromData_H
#define EepromData_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Application.h"
#include <cstdint>
//## package Application

//## class EepromData
class EepromData {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedEepromData;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    EepromData();
    
    virtual ~EepromData() = 0;
    
    ////    Operations    ////
    
    //## operation getConfigdata()
    virtual std::uint8_t getConfigdata() = 0;
    
    //## operation setConfigdata(uint8_t)
    virtual void setConfigdata(const std::uint8_t lastStartTime) = 0;
};

#ifdef _OMINSTRUMENT
class OMAnimatedEepromData : virtual public AOMInstance {
    DECLARE_META(EepromData, OMAnimatedEepromData)
};
#endif // _OMINSTRUMENT

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/EepromData.h
*********************************************************************/
