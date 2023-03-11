/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: Display
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: Simulation/DefaultConfig/Display.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#include "Display.h"
#define Application_Display_updateDisplay_SERIALIZE \
    aomsmethod->addAttribute("update_mode", UNKNOWN2STRING(update_mode));\
    aomsmethod->addAttribute("update_currentTime_ms", UNKNOWN2STRING(update_currentTime_ms));\
    aomsmethod->addAttribute("update_startTime_ms", UNKNOWN2STRING(update_startTime_ms));\
    aomsmethod->addAttribute("acc_X", UNKNOWN2STRING(acc_X));\
    aomsmethod->addAttribute("acc_Y", UNKNOWN2STRING(acc_Y));\
    aomsmethod->addAttribute("acc_Z", UNKNOWN2STRING(acc_Z));
#define Application_Display_Display_SERIALIZE OM_NO_OP

#define Application_Display_init_SERIALIZE OM_NO_OP

//## package Application

//## class Display
Display::Display() {
    NOTIFY_CONSTRUCTOR(Display, Display(), 0, Application_Display_Display_SERIALIZE);
}

Display::~Display() {
    NOTIFY_DESTRUCTOR(~Display, true);
}

#ifdef _OMINSTRUMENT
IMPLEMENT_META_P(Display, Application, Application, false, OMAnimatedDisplay)
#endif // _OMINSTRUMENT

/*********************************************************************
	File Path	: Simulation/DefaultConfig/Display.cpp
*********************************************************************/
