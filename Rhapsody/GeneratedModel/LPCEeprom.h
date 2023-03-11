/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCEeprom
//!	Generated Date	: Wed, 17, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCEeprom.h
*********************************************************************/

#ifndef LPCEeprom_H
#define LPCEeprom_H

#include "LPC1769.h"
#include "EepromData.h"
#include <mc24lc08.h>
#include <cstdint>
//## package LPC1769

//## class LPCEeprom
class LPCEeprom : public EepromData {
    ////    Constructors and destructors    ////
    
public :

    //## operation LPCEeprom()
    LPCEeprom(void);
    
    virtual ~LPCEeprom(void);
    
    ////    Operations    ////
    
    //## operation getConfigdata(uint32_t)
    virtual std::uint32_t getConfigdata(std::uint32_t LastStartTime);
    
    //## operation setConfigdata(uint32_t)
    virtual bool setConfigdata(std::uint32_t LastStartTime);
    
    ////    Additional operations    ////
    
    Platform::BSP::MC24LC08* getItsMC24LC08(void) const;
    
    ////    Relations and components    ////

protected :

    Platform::BSP::MC24LC08 itsMC24LC08;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCEeprom.h
*********************************************************************/
