/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: EepromData
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/EepromData.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#include "EepromData.h"
#define Application_EepromData_EepromData_SERIALIZE OM_NO_OP

#define Application_EepromData_getConfigdata_SERIALIZE OM_NO_OP

#define Application_EepromData_setConfigdata_SERIALIZE aomsmethod->addAttribute("lastStartTime", x2String(lastStartTime));

//## package Application

//## class EepromData
EepromData::EepromData() {
    NOTIFY_CONSTRUCTOR(EepromData, EepromData(), 0, Application_EepromData_EepromData_SERIALIZE);
}

EepromData::~EepromData() {
    NOTIFY_DESTRUCTOR(~EepromData, true);
}

#ifdef _OMINSTRUMENT
IMPLEMENT_META_P(EepromData, Application, Application, false, OMAnimatedEepromData)
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/EepromData.cpp
*********************************************************************/
