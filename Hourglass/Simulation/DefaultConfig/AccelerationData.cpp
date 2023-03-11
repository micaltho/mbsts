/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: AccelerationData
//!	Generated Date	: Mon, 1, Aug 2022  
	File Path	: Simulation/DefaultConfig/AccelerationData.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#include "AccelerationData.h"
#define Application_AccelerationData_AccelerationData_SERIALIZE OM_NO_OP

#define Application_AccelerationData_readAccelerationX_SERIALIZE OM_NO_OP

#define Application_AccelerationData_readAccelerationY_SERIALIZE OM_NO_OP

#define Application_AccelerationData_readAccelerationZ_SERIALIZE OM_NO_OP

#define Application_AccelerationData_readXYZ_SERIALIZE OM_NO_OP

//## package Application

//## class AccelerationData
AccelerationData::AccelerationData() {
    NOTIFY_CONSTRUCTOR(AccelerationData, AccelerationData(), 0, Application_AccelerationData_AccelerationData_SERIALIZE);
}

AccelerationData::~AccelerationData() {
    NOTIFY_DESTRUCTOR(~AccelerationData, true);
}

#ifdef _OMINSTRUMENT
IMPLEMENT_META_P(AccelerationData, Application, Application, false, OMAnimatedAccelerationData)
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/AccelerationData.cpp
*********************************************************************/
