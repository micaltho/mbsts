/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: EepromData
//!	Generated Date	: Wed, 17, Aug 2022  
	File Path	: LPC1769/DefaultConfig/EepromData.h
*********************************************************************/

#ifndef EepromData_H
#define EepromData_H

#include "Application.h"
#include <cstdint>
//## package Application

//## class EepromData
class EepromData {
    ////    Constructors and destructors    ////
    
public :

    EepromData(void);
    
    virtual ~EepromData(void) = 0;
    
    ////    Operations    ////
    
    //## operation getConfigdata(uint32_t)
    virtual std::uint32_t getConfigdata(std::uint32_t LastStartTime) = 0;
    
    //## operation setConfigdata(uint32_t)
    virtual bool setConfigdata(std::uint32_t lastStartTime) = 0;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/EepromData.h
*********************************************************************/
