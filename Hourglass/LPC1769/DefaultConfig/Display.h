/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: Display
//!	Generated Date	: Thu, 4, Aug 2022  
	File Path	: LPC1769/DefaultConfig/Display.h
*********************************************************************/

#ifndef Display_H
#define Display_H

#include "Application.h"
#include <cstdint>
//## package Application

//## class Display
class Display {
    ////    Constructors and destructors    ////
    
public :

    Display(void);
    
    virtual ~Display(void) = 0;
    
    ////    Operations    ////
    
    //## operation init()
    virtual void init(void) = 0;
    
    //## operation updateDisplay(uint32_t,uint32_t,uint32_t,int32_t,int32_t,int32_t)
    virtual void updateDisplay(const std::uint32_t update_mode, const std::uint32_t update_currentTime_ms, const std::uint32_t update_startTime_ms, const std::int32_t acc_X = 0, const std::int32_t acc_Y = 0, const std::int32_t acc_Z = 0) = 0;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/Display.h
*********************************************************************/
