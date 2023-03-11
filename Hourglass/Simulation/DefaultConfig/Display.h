/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: Display
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: Simulation/DefaultConfig/Display.h
*********************************************************************/

#ifndef Display_H
#define Display_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include "Application.h"
#include <cstdint>
//## package Application

//## class Display
class Display {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedDisplay;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    Display();
    
    virtual ~Display() = 0;
    
    ////    Operations    ////
    
    //## operation init()
    virtual void init() = 0;
    
    //## operation updateDisplay(uint32_t,uint32_t,uint32_t,int32_t,int32_t,int32_t)
    virtual void updateDisplay(const std::uint32_t update_mode, const std::uint32_t update_currentTime_ms, const std::uint32_t update_startTime_ms, const std::int32_t acc_X = 0, const std::int32_t acc_Y = 0, const std::int32_t acc_Z = 0) = 0;
};

#ifdef _OMINSTRUMENT
class OMAnimatedDisplay : virtual public AOMInstance {
    DECLARE_META(Display, OMAnimatedDisplay)
};
#endif // _OMINSTRUMENT

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/Display.h
*********************************************************************/
