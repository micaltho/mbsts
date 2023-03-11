/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: SimulationAcceleration
//!	Generated Date	: Mon, 1, Aug 2022  
	File Path	: Simulation/DefaultConfig/SimulationAcceleration.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#include "SimulationAcceleration.h"
#define Simulation_SimulationAcceleration_SimulationAcceleration_SERIALIZE OM_NO_OP

#define Simulation_SimulationAcceleration_readAccelerationX_SERIALIZE OM_NO_OP

#define Simulation_SimulationAcceleration_readAccelerationY_SERIALIZE OM_NO_OP

#define Simulation_SimulationAcceleration_readAccelerationZ_SERIALIZE OM_NO_OP

#define Simulation_SimulationAcceleration_readXYZ_SERIALIZE OM_NO_OP

#define OMAnim_Simulation_SimulationAcceleration_setAcc_X_std__uint32_t_UNSERIALIZE_ARGS OP_UNSER(OMDestructiveString2X,p_acc_X)

#define OMAnim_Simulation_SimulationAcceleration_setAcc_X_std__uint32_t_SERIALIZE_RET_VAL

#define OMAnim_Simulation_SimulationAcceleration_setAcc_Y_std__uint32_t_UNSERIALIZE_ARGS OP_UNSER(OMDestructiveString2X,p_acc_Y)

#define OMAnim_Simulation_SimulationAcceleration_setAcc_Y_std__uint32_t_SERIALIZE_RET_VAL

//## package Simulation

//## class SimulationAcceleration
SimulationAcceleration::SimulationAcceleration() : acc_X(0), acc_Y(0), acc_Z(0) {
    NOTIFY_ACTIVE_NOT_REACTIVE_CONSTRUCTOR(SimulationAcceleration, SimulationAcceleration(), 0, Simulation_SimulationAcceleration_SimulationAcceleration_SERIALIZE);
}

SimulationAcceleration::~SimulationAcceleration() {
    NOTIFY_DESTRUCTOR(~SimulationAcceleration, false);
}

std::int32_t SimulationAcceleration::readAccelerationX() {
    NOTIFY_OPERATION(readAccelerationX, readAccelerationX(), 0, Simulation_SimulationAcceleration_readAccelerationX_SERIALIZE);
    //#[ operation readAccelerationX()
    return acc_X;
    //#]
}

std::int32_t SimulationAcceleration::readAccelerationY() {
    NOTIFY_OPERATION(readAccelerationY, readAccelerationY(), 0, Simulation_SimulationAcceleration_readAccelerationY_SERIALIZE);
    //#[ operation readAccelerationY()
    return acc_Y;
    //#]
}

std::int32_t SimulationAcceleration::readAccelerationZ() {
    NOTIFY_OPERATION(readAccelerationZ, readAccelerationZ(), 0, Simulation_SimulationAcceleration_readAccelerationZ_SERIALIZE);
    //#[ operation readAccelerationZ()
    //#]
}

void SimulationAcceleration::readXYZ() {
    NOTIFY_OPERATION(readXYZ, readXYZ(), 0, Simulation_SimulationAcceleration_readXYZ_SERIALIZE);
    //#[ operation readXYZ()
    //#]
}

std::uint32_t SimulationAcceleration::getAcc_X() const {
    return acc_X;
}

void SimulationAcceleration::setAcc_X(std::uint32_t p_acc_X) {
    acc_X = p_acc_X;
    NOTIFY_SET_OPERATION;
}

std::uint32_t SimulationAcceleration::getAcc_Y() const {
    return acc_Y;
}

void SimulationAcceleration::setAcc_Y(std::uint32_t p_acc_Y) {
    acc_Y = p_acc_Y;
    NOTIFY_SET_OPERATION;
}

std::uint32_t SimulationAcceleration::getAcc_Z() const {
    return acc_Z;
}

void SimulationAcceleration::setAcc_Z(std::uint32_t p_acc_Z) {
    acc_Z = p_acc_Z;
}

#ifdef _OMINSTRUMENT
void OMAnimatedSimulationAcceleration::serializeAttributes(AOMSAttributes* aomsAttributes) const {
    aomsAttributes->addAttribute("acc_Y", UNKNOWN2STRING(myReal->acc_Y));
    aomsAttributes->addAttribute("acc_X", UNKNOWN2STRING(myReal->acc_X));
    aomsAttributes->addAttribute("acc_Z", UNKNOWN2STRING(myReal->acc_Z));
    OMAnimatedAccelerationData::serializeAttributes(aomsAttributes);
}

void OMAnimatedSimulationAcceleration::serializeRelations(AOMSRelations* aomsRelations) const {
    OMAnimatedAccelerationData::serializeRelations(aomsRelations);
}

IMPLEMENT_META_S_P(SimulationAcceleration, Simulation, false, AccelerationData, OMAnimatedAccelerationData, OMAnimatedSimulationAcceleration)

OMINIT_SUPERCLASS(AccelerationData, OMAnimatedAccelerationData)

OMREGISTER_CLASS

IMPLEMENT_META_OP(OMAnimatedSimulationAcceleration, Simulation_SimulationAcceleration_setAcc_X_std__uint32_t, "setAcc_X", FALSE, "setAcc_X(uint32_t)", 1)

IMPLEMENT_OP_CALL(Simulation_SimulationAcceleration_setAcc_X_std__uint32_t, SimulationAcceleration, setAcc_X(p_acc_X), NO_OP())

IMPLEMENT_META_OP(OMAnimatedSimulationAcceleration, Simulation_SimulationAcceleration_setAcc_Y_std__uint32_t, "setAcc_Y", FALSE, "setAcc_Y(uint32_t)", 1)

IMPLEMENT_OP_CALL(Simulation_SimulationAcceleration_setAcc_Y_std__uint32_t, SimulationAcceleration, setAcc_Y(p_acc_Y), NO_OP())
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/SimulationAcceleration.cpp
*********************************************************************/
