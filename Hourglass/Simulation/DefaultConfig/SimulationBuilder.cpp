/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: SimulationBuilder
//!	Generated Date	: Mon, 1, Aug 2022  
	File Path	: Simulation/DefaultConfig/SimulationBuilder.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#include "SimulationBuilder.h"
#define Simulation_SimulationBuilder_SimulationBuilder_SERIALIZE OM_NO_OP

//## package Simulation

//## class SimulationBuilder
SimulationBuilder::SimulationBuilder(IOxfActive* theActiveContext) : itsController(0, 10, 1000), itsDisplayTask(10), itsTimeCounter(10, 50000) {
    NOTIFY_REACTIVE_CONSTRUCTOR(SimulationBuilder, SimulationBuilder(), 0, Simulation_SimulationBuilder_SimulationBuilder_SERIALIZE);
    setActiveContext(theActiveContext, false);
    {
        {
            itsDisplayTask.setShouldDelete(false);
        }
        {
            itsController.setShouldDelete(false);
        }
        {
            itsTimeCounter.setShouldDelete(false);
        }
        {
            itsAccelerationMeasuring.setShouldDelete(false);
        }
    }
    initRelations();
}

SimulationBuilder::~SimulationBuilder() {
    NOTIFY_DESTRUCTOR(~SimulationBuilder, true);
}

AccelerationMeasuring* SimulationBuilder::getItsAccelerationMeasuring() const {
    return (AccelerationMeasuring*) &itsAccelerationMeasuring;
}

Controller* SimulationBuilder::getItsController() const {
    return (Controller*) &itsController;
}

DisplayTask* SimulationBuilder::getItsDisplayTask() const {
    return (DisplayTask*) &itsDisplayTask;
}

SimulationAcceleration* SimulationBuilder::getItsSimulationAcceleration() const {
    return (SimulationAcceleration*) &itsSimulationAcceleration;
}

SimulationDisplay* SimulationBuilder::getItsSimulationDisplay() const {
    return (SimulationDisplay*) &itsSimulationDisplay;
}

TimeCounter* SimulationBuilder::getItsTimeCounter() const {
    return (TimeCounter*) &itsTimeCounter;
}

bool SimulationBuilder::startBehavior() {
    bool done = true;
    done &= itsAccelerationMeasuring.startBehavior();
    done &= itsController.startBehavior();
    done &= itsDisplayTask.startBehavior();
    done &= itsTimeCounter.startBehavior();
    done &= OMReactive::startBehavior();
    return done;
}

void SimulationBuilder::initRelations() {
    itsController.setItsDisplayTask(&itsDisplayTask);
    itsController.setItsTimeCounter(&itsTimeCounter);
    itsDisplayTask.setItsDisplay(&itsSimulationDisplay);
    itsController.setItsAccelerationMeasuring(&itsAccelerationMeasuring);
    itsAccelerationMeasuring.setItsAccelerationData(&itsSimulationAcceleration);
}

void SimulationBuilder::destroy() {
    itsAccelerationMeasuring.destroy();
    itsController.destroy();
    itsDisplayTask.destroy();
    itsTimeCounter.destroy();
    OMReactive::destroy();
}

#ifdef _OMINSTRUMENT
void OMAnimatedSimulationBuilder::serializeRelations(AOMSRelations* aomsRelations) const {
    aomsRelations->addRelation("itsDisplayTask", true, true);
    aomsRelations->ADD_ITEM(&myReal->itsDisplayTask);
    aomsRelations->addRelation("itsSimulationDisplay", true, true);
    aomsRelations->ADD_ITEM(&myReal->itsSimulationDisplay);
    aomsRelations->addRelation("itsController", true, true);
    aomsRelations->ADD_ITEM(&myReal->itsController);
    aomsRelations->addRelation("itsTimeCounter", true, true);
    aomsRelations->ADD_ITEM(&myReal->itsTimeCounter);
    aomsRelations->addRelation("itsSimulationAcceleration", true, true);
    aomsRelations->ADD_ITEM(&myReal->itsSimulationAcceleration);
    aomsRelations->addRelation("itsAccelerationMeasuring", true, true);
    aomsRelations->ADD_ITEM(&myReal->itsAccelerationMeasuring);
}

IMPLEMENT_REACTIVE_META_SIMPLE_P(SimulationBuilder, Simulation, Simulation, false, OMAnimatedSimulationBuilder)
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/SimulationBuilder.cpp
*********************************************************************/
