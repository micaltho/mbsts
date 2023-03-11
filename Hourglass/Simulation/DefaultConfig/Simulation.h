/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: Simulation
//!	Generated Date	: Mon, 1, Aug 2022  
	File Path	: Simulation/DefaultConfig/Simulation.h
*********************************************************************/

#ifndef Simulation_H
#define Simulation_H

#include <oxf/oxf.h>
#include <aom/aom.h>
class SimulationAcceleration;

class SimulationBuilder;

class SimulationDisplay;

//## package Simulation


extern SimulationBuilder itsSimulationBuilder;

void Simulation_initRelations();

bool Simulation_startBehavior();

class Simulation_OMInitializer {
    ////    Constructors and destructors    ////
    
public :

    Simulation_OMInitializer();
    
    ~Simulation_OMInitializer();
};

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/Simulation.h
*********************************************************************/
