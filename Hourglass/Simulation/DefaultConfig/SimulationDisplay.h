/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: SimulationDisplay
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: Simulation/DefaultConfig/SimulationDisplay.h
*********************************************************************/

#ifndef SimulationDisplay_H
#define SimulationDisplay_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Simulation.h"
#include "Display.h"
#include <cstdint>
//## package Simulation

//## class SimulationDisplay
class SimulationDisplay : public Display {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedSimulationDisplay;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    SimulationDisplay();
    
    ~SimulationDisplay();
    
    ////    Operations    ////
    
    //## operation init()
    void init();
    
    //## operation updateDisplay(uint32_t,uint32_t,uint32_t)
    void updateDisplay(const std::uint32_t update_mode, const std::uint32_t update_currentTime_ms, const std::uint32_t update_startTime_ms);
    
    ////    Additional operations    ////
    
    int getCurrentTime_ms() const;
    
    void setCurrentTime_ms(int p_currentTime_ms);
    
    int getMode() const;
    
    void setMode(int p_mode);
    
    int getStartTime_ms() const;
    
    void setStartTime_ms(int p_startTime_ms);
    
    ////    Attributes    ////

protected :

    int currentTime_ms;		//## attribute currentTime_ms
    
    int mode;		//## attribute mode
    
    int startTime_ms;		//## attribute startTime_ms
};

#ifdef _OMINSTRUMENT
class OMAnimatedSimulationDisplay : public OMAnimatedDisplay {
    DECLARE_META(SimulationDisplay, OMAnimatedSimulationDisplay)
    
    ////    Framework operations    ////
    
public :

    virtual void serializeAttributes(AOMSAttributes* aomsAttributes) const;
    
    virtual void serializeRelations(AOMSRelations* aomsRelations) const;
};
#endif // _OMINSTRUMENT

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/SimulationDisplay.h
*********************************************************************/
