/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: Application
//!	Generated Date	: Thu, 25, Aug 2022  
	File Path	: LPC1769/DefaultConfig/Application.h
*********************************************************************/

#ifndef Application_H
#define Application_H

#include "RXF_Event.h"
class AccelerationData;

class AccelerationMeasuring;

class ConfigStorage;

class Controller;

class Display;

class DisplayTask;

class EepromData;

class TimeCounter;

//## package Application



class evRunBackward : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evRunBackward(void);
};

extern const RXF::Event::Id_t evRunBackward_Application_id;

class evRunForward : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evRunForward(void);
};

extern const RXF::Event::Id_t evRunForward_Application_id;

class evStop : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evStop(void);
};

extern const RXF::Event::Id_t evStop_Application_id;

class evMenu : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evMenu(void);
};

extern const RXF::Event::Id_t evMenu_Application_id;

class evReset : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evReset(void);
};

extern const RXF::Event::Id_t evReset_Application_id;

class evMenuExit : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evMenuExit(void);
};

extern const RXF::Event::Id_t evMenuExit_Application_id;

class evRaiseStartTime : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evRaiseStartTime(void);
};

extern const RXF::Event::Id_t evRaiseStartTime_Application_id;

class evReduceStartTime : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evReduceStartTime(void);
};

extern const RXF::Event::Id_t evReduceStartTime_Application_id;

class evRaiseTimeFactor : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evRaiseTimeFactor(void);
};

extern const RXF::Event::Id_t evRaiseTimeFactor_Application_id;

class evReduceTimeFactor : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evReduceTimeFactor(void);
};

extern const RXF::Event::Id_t evReduceTimeFactor_Application_id;

class evTimeFactorSetting : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evTimeFactorSetting(void);
};

extern const RXF::Event::Id_t evTimeFactorSetting_Application_id;

class evStartTimeSetting : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evStartTimeSetting(void);
};

extern const RXF::Event::Id_t evStartTimeSetting_Application_id;

class evGoBack : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evGoBack(void);
};

extern const RXF::Event::Id_t evGoBack_Application_id;

class evResetTime : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evResetTime(void);
};

extern const RXF::Event::Id_t evResetTime_Application_id;

class evCalibrate : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evCalibrate(void);
};

extern const RXF::Event::Id_t evCalibrate_Application_id;

class evConfigSettingsChangend : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evConfigSettingsChangend(void);
};

extern const RXF::Event::Id_t evConfigSettingsChangend_Application_id;

class evProgrammStart : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evProgrammStart(void);
};

extern const RXF::Event::Id_t evProgrammStart_Application_id;

class evStart : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evStart(void);
};

extern const RXF::Event::Id_t evStart_Application_id;

class evGoBackToRunHourglass : public RXF::Event {
    ////    Constructors and destructors    ////
    
public :

    evGoBackToRunHourglass(void);
};

extern const RXF::Event::Id_t evGoBackToRunHourglass_Application_id;

#endif
/*********************************************************************
	File Path	: LPC1769/DefaultConfig/Application.h
*********************************************************************/
