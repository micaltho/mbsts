/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: SimulationAcceleration
//!	Generated Date	: Mon, 1, Aug 2022  
	File Path	: Simulation/DefaultConfig/SimulationAcceleration.h
*********************************************************************/

#ifndef SimulationAcceleration_H
#define SimulationAcceleration_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Simulation.h"
#include <oxf/omthread.h>
#include "AccelerationData.h"
#include <cstdint>
#define OMAnim_Simulation_SimulationAcceleration_setAcc_X_std__uint32_t_ARGS_DECLARATION std::uint32_t p_acc_X;

#define OMAnim_Simulation_SimulationAcceleration_setAcc_Y_std__uint32_t_ARGS_DECLARATION std::uint32_t p_acc_Y;

//## package Simulation

//## class SimulationAcceleration
class SimulationAcceleration : public OMThread, public AccelerationData {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedSimulationAcceleration;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    SimulationAcceleration();
    
    virtual ~SimulationAcceleration();
    
    ////    Operations    ////
    
    //## operation readAccelerationX()
    virtual std::int32_t readAccelerationX();
    
    //## operation readAccelerationY()
    std::int32_t readAccelerationY();
    
    //## operation readAccelerationZ()
    virtual std::int32_t readAccelerationZ();
    
    //## operation readXYZ()
    void readXYZ();
    
    ////    Additional operations    ////
    
    std::uint32_t getAcc_X() const;
    
    void setAcc_X(std::uint32_t p_acc_X);
    
    std::uint32_t getAcc_Y() const;
    
    void setAcc_Y(std::uint32_t p_acc_Y);
    
    std::uint32_t getAcc_Z() const;
    
    void setAcc_Z(std::uint32_t p_acc_Z);
    
    ////    Attributes    ////

protected :

    std::uint32_t acc_X;		//## attribute acc_X
    
    std::uint32_t acc_Y;		//## attribute acc_Y
    
    std::uint32_t acc_Z;		//## attribute acc_Z
};

#ifdef _OMINSTRUMENT
DECLARE_OPERATION_CLASS(Simulation_SimulationAcceleration_setAcc_X_std__uint32_t)

DECLARE_OPERATION_CLASS(Simulation_SimulationAcceleration_setAcc_Y_std__uint32_t)

class OMAnimatedSimulationAcceleration : public OMAnimatedAccelerationData {
    DECLARE_META(SimulationAcceleration, OMAnimatedSimulationAcceleration)
    
    DECLARE_META_OP(Simulation_SimulationAcceleration_setAcc_X_std__uint32_t)
    
    DECLARE_META_OP(Simulation_SimulationAcceleration_setAcc_Y_std__uint32_t)
    
    ////    Framework operations    ////
    
public :

    virtual void serializeAttributes(AOMSAttributes* aomsAttributes) const;
    
    virtual void serializeRelations(AOMSRelations* aomsRelations) const;
};
#endif // _OMINSTRUMENT

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/SimulationAcceleration.h
*********************************************************************/
