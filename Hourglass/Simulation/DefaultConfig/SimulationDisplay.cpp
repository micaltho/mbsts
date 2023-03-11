/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: SimulationDisplay
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: Simulation/DefaultConfig/SimulationDisplay.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#include "SimulationDisplay.h"
#define Simulation_SimulationDisplay_updateDisplay_SERIALIZE \
    aomsmethod->addAttribute("update_mode", UNKNOWN2STRING(update_mode));\
    aomsmethod->addAttribute("update_currentTime_ms", UNKNOWN2STRING(update_currentTime_ms));\
    aomsmethod->addAttribute("update_startTime_ms", UNKNOWN2STRING(update_startTime_ms));
#define Simulation_SimulationDisplay_SimulationDisplay_SERIALIZE OM_NO_OP

#define Simulation_SimulationDisplay_init_SERIALIZE OM_NO_OP

//## package Simulation

//## class SimulationDisplay
SimulationDisplay::SimulationDisplay() : currentTime_ms(0), mode(0), startTime_ms(50000) {
    NOTIFY_CONSTRUCTOR(SimulationDisplay, SimulationDisplay(), 0, Simulation_SimulationDisplay_SimulationDisplay_SERIALIZE);
}

SimulationDisplay::~SimulationDisplay() {
    NOTIFY_DESTRUCTOR(~SimulationDisplay, false);
}

void SimulationDisplay::init() {
    NOTIFY_OPERATION(init, init(), 0, Simulation_SimulationDisplay_init_SERIALIZE);
    //#[ operation init()
    //#]
}

void SimulationDisplay::updateDisplay(const std::uint32_t update_mode, const std::uint32_t update_currentTime_ms, const std::uint32_t update_startTime_ms) {
    NOTIFY_OPERATION(updateDisplay, updateDisplay(const std::uint32_t,const std::uint32_t,const std::uint32_t), 3, Simulation_SimulationDisplay_updateDisplay_SERIALIZE);
    //#[ operation updateDisplay(uint32_t,uint32_t,uint32_t)
    mode = update_mode;
    currentTime_ms = update_currentTime_ms;
    startTime_ms = update_startTime_ms;
    //#]
}

int SimulationDisplay::getCurrentTime_ms() const {
    return currentTime_ms;
}

void SimulationDisplay::setCurrentTime_ms(int p_currentTime_ms) {
    currentTime_ms = p_currentTime_ms;
    NOTIFY_SET_OPERATION;
}

int SimulationDisplay::getMode() const {
    return mode;
}

void SimulationDisplay::setMode(int p_mode) {
    mode = p_mode;
    NOTIFY_SET_OPERATION;
}

int SimulationDisplay::getStartTime_ms() const {
    return startTime_ms;
}

void SimulationDisplay::setStartTime_ms(int p_startTime_ms) {
    startTime_ms = p_startTime_ms;
    NOTIFY_SET_OPERATION;
}

#ifdef _OMINSTRUMENT
void OMAnimatedSimulationDisplay::serializeAttributes(AOMSAttributes* aomsAttributes) const {
    aomsAttributes->addAttribute("currentTime_ms", x2String(myReal->currentTime_ms));
    aomsAttributes->addAttribute("startTime_ms", x2String(myReal->startTime_ms));
    aomsAttributes->addAttribute("mode", x2String(myReal->mode));
    OMAnimatedDisplay::serializeAttributes(aomsAttributes);
}

void OMAnimatedSimulationDisplay::serializeRelations(AOMSRelations* aomsRelations) const {
    OMAnimatedDisplay::serializeRelations(aomsRelations);
}

IMPLEMENT_META_S_P(SimulationDisplay, Simulation, false, Display, OMAnimatedDisplay, OMAnimatedSimulationDisplay)

OMINIT_SUPERCLASS(Display, OMAnimatedDisplay)

OMREGISTER_CLASS
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/SimulationDisplay.cpp
*********************************************************************/
