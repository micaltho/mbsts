/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCInit
//!	Generated Date	: Tue, 2, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCInit.cpp
*********************************************************************/

#include "LPCInit.h"
//## package LPC1769::Init

//## class LPCInit
LPCInit::LPCInit(void) {
    //#[ operation LPCInit()
    SystemCoreClockUpdate();
    Board_Init();
    Platform::BSP::SSPDevice::initialize(Platform::BSP::SSPDevice::Interface::SSP1);
    Platform::BSP::I2CDevice::initialize(Platform::BSP::I2CDevice::Interface::I2C2,
    Platform::BSP::I2CDevice::Mode::POLLING, 100000);
    Platform::BSP::DigitalInOut::initialize();
    //#]
}

LPCInit::~LPCInit(void) {
}

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCInit.cpp
*********************************************************************/
