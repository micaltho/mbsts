/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: LPCOledDisplay
//!	Generated Date	: Wed, 31, Aug 2022  
	File Path	: LPC1769/DefaultConfig/LPCOledDisplay.h
*********************************************************************/

#ifndef LPCOledDisplay_H
#define LPCOledDisplay_H

#include "LPC1769.h"
#include "Display.h"
#include <ssd1305.h>
#include <cstdint>
//## package LPC1769

//## class LPCOledDisplay
class LPCOledDisplay : public Display {
    ////    Constructors and destructors    ////
    
public :

    //## operation LPCOledDisplay()
    LPCOledDisplay(void);
    
    virtual ~LPCOledDisplay(void);
    
    ////    Operations    ////
    
    //## operation AccelerometerSettings(int32_t,int32_t,int32_t)
    void AccelerometerSettings(const std::int32_t acc_X, const std::int32_t acc_Y, const std::int32_t acc_Z);
    
    //## operation GravitationFromLeftToRight()
    void GravitationFromLeftToRight(void);
    
    //## operation GravitationFromRightToLeft()
    void GravitationFromRightToLeft(void);
    
    //## operation Hourglass(uint32_t,uint32_t)
    void Hourglass(const std::uint32_t update_currentTime_ms, const std::uint32_t startTime_ms);
    
    //## operation MainMenu()
    void MainMenu(void);
    
    //## operation StartTimeSettings(uint32_t)
    void StartTimeSettings(const std::uint32_t StartTime);
    
    //## operation TimeFactorSettings(uint32_t)
    void TimeFactorSettings(const std::uint32_t TimeFactor);
    
    //## operation emptyWatch_Signal()
    void emptyWatch_Signal(void);
    
    //## operation fallingSandDown()
    void fallingSandDown(void);
    
    //## operation fallingSandUp()
    void fallingSandUp(void);
    
    //## operation fillGlassWithSand()
    void fillGlassWithSand(void);
    
    //## operation init()
    virtual void init(void);
    
    //## operation updateDisplay(uint32_t,uint32_t,uint32_t,int32_t,int32_t,int32_t)
    void updateDisplay(const std::uint32_t update_mode, const std::uint32_t update_currentTime_ms, const std::uint32_t update_startTime_ms, const std::int32_t acc_X = 0, const std::int32_t acc_Y = 0, const std::int32_t acc_Z = 0);
    
    ////    Additional operations    ////
    
    std::uint32_t getEmptyWatch_counter(void) const;
    
    void setEmptyWatch_counter(const std::uint32_t p_EmptyWatch_counter);
    
    static const std::uint8_t getPixels_Blink_Signal_One(int32_t i1);
    
    static const std::uint8_t getPixels_Blink_Signal_Zero(int32_t i1);
    
    bool getSandIsDown(void) const;
    
    void setSandIsDown(const bool p_SandIsDown);
    
    bool getSandIsUp(void) const;
    
    void setSandIsUp(const bool p_SandIsUp);
    
    double getFallingSandFactor(void) const;
    
    void setFallingSandFactor(const double p_fallingSandFactor);
    
    static std::uint32_t getFromRightToLeft(void);
    
    static void setFromRightToLeft(const std::uint32_t p_fromRightToLeft);
    
    std::uint32_t getLastCurrentTime(void) const;
    
    void setLastCurrentTime(const std::uint32_t p_lastCurrentTime);
    
    std::uint8_t getNumOfRowsWithSand(void) const;
    
    void setNumOfRowsWithSand(const std::uint8_t p_numOfRowsWithSand);
    
    std::uint8_t getPixel_init(int32_t i1) const;
    
    void setPixel_init(int32_t i1, const std::uint8_t p_pixel_init);
    
    std::uint8_t getPixels(int32_t i1) const;
    
    void setPixels(int32_t i1, const std::uint8_t p_pixels);
    
    static std::uint8_t getPixels_state(int32_t i1);
    
    static void setPixels_state(int32_t i1, const std::uint8_t p_pixels_state);
    
    Platform::BSP::SSD1305* getItsSSD1305(void) const;
    
    ////    Attributes    ////

protected :

    std::uint32_t EmptyWatch_counter;		//## attribute EmptyWatch_counter
    
    static const std::uint8_t Pixels_Blink_Signal_One[6144];		//## attribute Pixels_Blink_Signal_One
    
    static const std::uint8_t Pixels_Blink_Signal_Zero[6144];		//## attribute Pixels_Blink_Signal_Zero
    
    bool SandIsDown;		//## attribute SandIsDown
    
    bool SandIsUp;		//## attribute SandIsUp
    
    double fallingSandFactor;		//## attribute fallingSandFactor
    
    static std::uint32_t fromRightToLeft;		//## attribute fromRightToLeft
    
    std::uint32_t lastCurrentTime;		//## attribute lastCurrentTime
    
    std::uint8_t numOfRowsWithSand;		//## attribute numOfRowsWithSand
    
    std::uint8_t pixel_init[6144];		//## attribute pixel_init
    
    std::uint8_t pixels[6144];		//## attribute pixels
    
    static std::uint8_t pixels_state[6144];		//## attribute pixels_state
    
    ////    Relations and components    ////
    
    Platform::BSP::SSD1305 itsSSD1305;
};

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/LPCOledDisplay.h
*********************************************************************/
