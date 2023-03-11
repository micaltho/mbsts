/*********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: Application
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/Application.h
*********************************************************************/

#ifndef Application_H
#define Application_H

#include <oxf/oxf.h>
#include <aom/aom.h>
#include <oxf/event.h>
class AccelerationData;

class AccelerationMeasuring;

class ConfigStorage;

class Controller;

class Display;

class DisplayTask;

class EepromData;

class TimeCounter;

#define evRunBackward_Application_id 19801

#define evRunForward_Application_id 19802

#define evStop_Application_id 19803

#define evMenu_Application_id 19804

#define evReset_Application_id 19805

#define evMenuExit_Application_id 19806

#define evRaiseStartTime_Application_id 19807

#define evReduceStartTime_Application_id 19808

#define evRaiseTimeFactor_Application_id 19809

#define evReduceTimeFactor_Application_id 19810

#define evTimeFactorSetting_Application_id 19811

#define evStartTimeSetting_Application_id 19812

#define evGoBack_Application_id 19813

#define evResetTime_Application_id 19814

#define evCalibrate_Application_id 19815

#define evConfigSettingsChangend_Application_id 19816

#define evProgrammStart_Application_id 19817

//## package Application



class evRunBackward : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevRunBackward;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evRunBackward();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevRunBackward : virtual public AOMEvent {
    DECLARE_META_EVENT(evRunBackward)
};
#endif // _OMINSTRUMENT

class evRunForward : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevRunForward;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evRunForward();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevRunForward : virtual public AOMEvent {
    DECLARE_META_EVENT(evRunForward)
};
#endif // _OMINSTRUMENT

class evStop : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevStop;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evStop();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevStop : virtual public AOMEvent {
    DECLARE_META_EVENT(evStop)
};
#endif // _OMINSTRUMENT

class evMenu : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevMenu;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evMenu();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevMenu : virtual public AOMEvent {
    DECLARE_META_EVENT(evMenu)
};
#endif // _OMINSTRUMENT

class evReset : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevReset;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evReset();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevReset : virtual public AOMEvent {
    DECLARE_META_EVENT(evReset)
};
#endif // _OMINSTRUMENT

class evMenuExit : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevMenuExit;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evMenuExit();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevMenuExit : virtual public AOMEvent {
    DECLARE_META_EVENT(evMenuExit)
};
#endif // _OMINSTRUMENT

class evRaiseStartTime : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevRaiseStartTime;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evRaiseStartTime();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevRaiseStartTime : virtual public AOMEvent {
    DECLARE_META_EVENT(evRaiseStartTime)
};
#endif // _OMINSTRUMENT

class evReduceStartTime : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevReduceStartTime;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evReduceStartTime();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevReduceStartTime : virtual public AOMEvent {
    DECLARE_META_EVENT(evReduceStartTime)
};
#endif // _OMINSTRUMENT

class evRaiseTimeFactor : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevRaiseTimeFactor;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evRaiseTimeFactor();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevRaiseTimeFactor : virtual public AOMEvent {
    DECLARE_META_EVENT(evRaiseTimeFactor)
};
#endif // _OMINSTRUMENT

class evReduceTimeFactor : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevReduceTimeFactor;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evReduceTimeFactor();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevReduceTimeFactor : virtual public AOMEvent {
    DECLARE_META_EVENT(evReduceTimeFactor)
};
#endif // _OMINSTRUMENT

class evTimeFactorSetting : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevTimeFactorSetting;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evTimeFactorSetting();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevTimeFactorSetting : virtual public AOMEvent {
    DECLARE_META_EVENT(evTimeFactorSetting)
};
#endif // _OMINSTRUMENT

class evStartTimeSetting : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevStartTimeSetting;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evStartTimeSetting();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevStartTimeSetting : virtual public AOMEvent {
    DECLARE_META_EVENT(evStartTimeSetting)
};
#endif // _OMINSTRUMENT

class evGoBack : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevGoBack;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evGoBack();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevGoBack : virtual public AOMEvent {
    DECLARE_META_EVENT(evGoBack)
};
#endif // _OMINSTRUMENT

class evResetTime : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevResetTime;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evResetTime();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevResetTime : virtual public AOMEvent {
    DECLARE_META_EVENT(evResetTime)
};
#endif // _OMINSTRUMENT

class evCalibrate : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevCalibrate;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evCalibrate();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevCalibrate : virtual public AOMEvent {
    DECLARE_META_EVENT(evCalibrate)
};
#endif // _OMINSTRUMENT

class evConfigSettingsChangend : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevConfigSettingsChangend;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evConfigSettingsChangend();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevConfigSettingsChangend : virtual public AOMEvent {
    DECLARE_META_EVENT(evConfigSettingsChangend)
};
#endif // _OMINSTRUMENT

class evProgrammStart : public OMEvent {
    ////    Friends    ////
    
public :

#ifdef _OMINSTRUMENT
    friend class OMAnimatedevProgrammStart;
#endif // _OMINSTRUMENT

    ////    Constructors and destructors    ////
    
    evProgrammStart();
    
    ////    Framework operations    ////
    
    virtual bool isTypeOf(const short id) const;
};

#ifdef _OMINSTRUMENT
class OMAnimatedevProgrammStart : virtual public AOMEvent {
    DECLARE_META_EVENT(evProgrammStart)
};
#endif // _OMINSTRUMENT

#endif
/*********************************************************************
	File Path	: Simulation/DefaultConfig/Application.h
*********************************************************************/
