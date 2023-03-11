/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCEeprom
//!	Generated Date	: Wed, 17, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCEeprom.cpp
*********************************************************************/

#include "LPCEeprom.h"
//## package LPC1769

//## class LPCEeprom
LPCEeprom::LPCEeprom(void) : itsMC24LC08(Platform::BSP::I2CDevice::Interface::I2C2)
  {
    //#[ operation LPCEeprom()
    //#]
}

LPCEeprom::~LPCEeprom(void) {
}

std::uint32_t LPCEeprom::getConfigdata(std::uint32_t LastStartTime) {
    //#[ operation getConfigdata(uint32_t)
    itsMC24LC08.read(14,sizeof(LastStartTime),(uint8_t*) &LastStartTime);
    return LastStartTime;
    //#]
}

bool LPCEeprom::setConfigdata(std::uint32_t LastStartTime) {
    //#[ operation setConfigdata(uint32_t)
    return itsMC24LC08.store(14, sizeof(LastStartTime), (uint8_t*) &LastStartTime);
    //#]
}

Platform::BSP::MC24LC08* LPCEeprom::getItsMC24LC08(void) const {
    return (Platform::BSP::MC24LC08*) &itsMC24LC08;
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCEeprom.cpp
*********************************************************************/
