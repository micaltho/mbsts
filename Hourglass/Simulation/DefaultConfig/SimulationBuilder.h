/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: SimulationBuilder
//!	Generated Date	: Mon, 1, Aug 2022  
	File Path	: Simulation/DefaultConfig/SimulationBuilder.h
*********************************************************************/

#ifndef SimulationBuilder_H
#define SimulationBuilder_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Simulation.h"
#include <oxf/omthread.h>
#include <oxf/omreactive.h>
#include <oxf/state.h>
#include <oxf/event.h>
#include "AccelerationMeasuring.h"
#include "Controller.h"
#include "DisplayTask.h"
#include "SimulationAcceleration.h"
#include "SimulationDisplay.h"
#include "TimeCounter.h"
//## package Simulation

//## class SimulationBuilder
class SimulationBuilder : public OMReactive {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedSimulationBuilder;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    SimulationBuilder(IOxfActive* theActiveContext = 0);
    
    ~SimulationBuilder();
    
    ////    Additional operations    ////
    
    AccelerationMeasuring* getItsAccelerationMeasuring() const;
    
    Controller* getItsController() const;
    
    DisplayTask* getItsDisplayTask() const;
    
    SimulationAcceleration* getItsSimulationAcceleration() const;
    
    SimulationDisplay* getItsSimulationDisplay() const;
    
    TimeCounter* getItsTimeCounter() const;
    
    virtual bool startBehavior();

protected :

    void initRelations();
    
    ////    Relations and components    ////
    
    AccelerationMeasuring itsAccelerationMeasuring;
    
    Controller itsController;
    
    DisplayTask itsDisplayTask;
    
    SimulationAcceleration itsSimulationAcceleration;
    
    SimulationDisplay itsSimulationDisplay;
    
    TimeCounter itsTimeCounter;
    
    ////    Framework operations    ////

public :

    virtual void destroy();
};

#ifdef _OMINSTRUMENT
class OMAnimatedSimulationBuilder : virtual public AOMInstance {
    DECLARE_META(SimulationBuilder, OMAnimatedSimulationBuilder)
    
    ////    Framework operations    ////
    
public :

    virtual void serializeRelations(AOMSRelations* aomsRelations) const;
};
#endif // _OMINSTRUMENT

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/SimulationBuilder.h
*********************************************************************/
