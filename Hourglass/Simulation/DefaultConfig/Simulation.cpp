/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: Simulation
//!	Generated Date	: Mon, 1, Aug 2022  
	File Path	: Simulation/DefaultConfig/Simulation.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#include "Simulation.h"
#include "SimulationBuilder.h"
#include "SimulationAcceleration.h"
#include "SimulationDisplay.h"
//## package Simulation


SimulationBuilder itsSimulationBuilder;

#ifdef _OMINSTRUMENT
static void serializeGlobalVars(AOMSAttributes* /* aomsAttributes */);

static void RenameGlobalInstances();

IMPLEMENT_META_PACKAGE(Simulation, Simulation)
#endif // _OMINSTRUMENT

void Simulation_initRelations() {
    {
        {
            itsSimulationBuilder.setShouldDelete(false);
        }
    }
    
    #ifdef _OMINSTRUMENT
    RenameGlobalInstances();
    #endif // _OMINSTRUMENT
}

bool Simulation_startBehavior() {
    bool done = true;
    done &= itsSimulationBuilder.startBehavior();
    return done;
}

#ifdef _OMINSTRUMENT
static void serializeGlobalVars(AOMSAttributes* /* aomsAttributes */) {
}

static void RenameGlobalInstances() {
    OM_SET_INSTANCE_NAME(&itsSimulationBuilder, SimulationBuilder, "itsSimulationBuilder", AOMNoMultiplicity);
}
#endif // _OMINSTRUMENT

Simulation_OMInitializer::Simulation_OMInitializer() {
    Simulation_initRelations();
    Simulation_startBehavior();
}

Simulation_OMInitializer::~Simulation_OMInitializer() {
}

/*********************************************************************
	File Path	: Simulation/DefaultConfig/Simulation.cpp
*********************************************************************/
