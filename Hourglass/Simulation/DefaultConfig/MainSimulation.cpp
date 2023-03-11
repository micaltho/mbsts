/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: DefaultConfig
//!	Generated Date	: Wed, 22, Jun 2022  
	File Path	: Simulation/DefaultConfig/MainSimulation.cpp
*********************************************************************/

#include "MainSimulation.h"
#include "Application.h"
#include "Simulation.h"
Simulation::Simulation() {
    Simulation_initRelations();
    Simulation_startBehavior();
}

int main(int argc, char* argv[]) {
    int status = 0;
    if(OXF::initialize(argc, argv, 6423))
        {
            Simulation initializer_Simulation;
            //#[ configuration Simulation::DefaultConfig 
            //#]
            OXF::start();
            status = 0;
        }
    else
        {
            status = 1;
        }
    return status;
}

/*********************************************************************
	File Path	: Simulation/DefaultConfig/MainSimulation.cpp
*********************************************************************/
