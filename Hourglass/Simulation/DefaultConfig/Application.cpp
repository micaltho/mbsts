/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: Simulation 
	Configuration 	: DefaultConfig
	Model Element	: Application
//!	Generated Date	: Tue, 9, Aug 2022  
	File Path	: Simulation/DefaultConfig/Application.cpp
*********************************************************************/

#define NAMESPACE_PREFIX

#include "Application.h"
#include "AccelerationData.h"
#include "AccelerationMeasuring.h"
#include "ConfigStorage.h"
#include "Controller.h"
#include "Display.h"
#include "DisplayTask.h"
#include "EepromData.h"
#include "TimeCounter.h"
#define evRunBackward_SERIALIZE OM_NO_OP

#define evRunBackward_UNSERIALIZE OM_NO_OP

#define evRunBackward_CONSTRUCTOR evRunBackward()

#define evRunForward_SERIALIZE OM_NO_OP

#define evRunForward_UNSERIALIZE OM_NO_OP

#define evRunForward_CONSTRUCTOR evRunForward()

#define evStop_SERIALIZE OM_NO_OP

#define evStop_UNSERIALIZE OM_NO_OP

#define evStop_CONSTRUCTOR evStop()

#define evMenu_SERIALIZE OM_NO_OP

#define evMenu_UNSERIALIZE OM_NO_OP

#define evMenu_CONSTRUCTOR evMenu()

#define evReset_SERIALIZE OM_NO_OP

#define evReset_UNSERIALIZE OM_NO_OP

#define evReset_CONSTRUCTOR evReset()

#define evMenuExit_SERIALIZE OM_NO_OP

#define evMenuExit_UNSERIALIZE OM_NO_OP

#define evMenuExit_CONSTRUCTOR evMenuExit()

#define evRaiseStartTime_SERIALIZE OM_NO_OP

#define evRaiseStartTime_UNSERIALIZE OM_NO_OP

#define evRaiseStartTime_CONSTRUCTOR evRaiseStartTime()

#define evReduceStartTime_SERIALIZE OM_NO_OP

#define evReduceStartTime_UNSERIALIZE OM_NO_OP

#define evReduceStartTime_CONSTRUCTOR evReduceStartTime()

#define evRaiseTimeFactor_SERIALIZE OM_NO_OP

#define evRaiseTimeFactor_UNSERIALIZE OM_NO_OP

#define evRaiseTimeFactor_CONSTRUCTOR evRaiseTimeFactor()

#define evReduceTimeFactor_SERIALIZE OM_NO_OP

#define evReduceTimeFactor_UNSERIALIZE OM_NO_OP

#define evReduceTimeFactor_CONSTRUCTOR evReduceTimeFactor()

#define evTimeFactorSetting_SERIALIZE OM_NO_OP

#define evTimeFactorSetting_UNSERIALIZE OM_NO_OP

#define evTimeFactorSetting_CONSTRUCTOR evTimeFactorSetting()

#define evStartTimeSetting_SERIALIZE OM_NO_OP

#define evStartTimeSetting_UNSERIALIZE OM_NO_OP

#define evStartTimeSetting_CONSTRUCTOR evStartTimeSetting()

#define evGoBack_SERIALIZE OM_NO_OP

#define evGoBack_UNSERIALIZE OM_NO_OP

#define evGoBack_CONSTRUCTOR evGoBack()

#define evResetTime_SERIALIZE OM_NO_OP

#define evResetTime_UNSERIALIZE OM_NO_OP

#define evResetTime_CONSTRUCTOR evResetTime()

#define evCalibrate_SERIALIZE OM_NO_OP

#define evCalibrate_UNSERIALIZE OM_NO_OP

#define evCalibrate_CONSTRUCTOR evCalibrate()

#define evConfigSettingsChangend_SERIALIZE OM_NO_OP

#define evConfigSettingsChangend_UNSERIALIZE OM_NO_OP

#define evConfigSettingsChangend_CONSTRUCTOR evConfigSettingsChangend()

#define evProgrammStart_SERIALIZE OM_NO_OP

#define evProgrammStart_UNSERIALIZE OM_NO_OP

#define evProgrammStart_CONSTRUCTOR evProgrammStart()

//## package Application


#ifdef _OMINSTRUMENT
static void serializeGlobalVars(AOMSAttributes* /* aomsAttributes */);

IMPLEMENT_META_PACKAGE(Application, Application)

static void serializeGlobalVars(AOMSAttributes* /* aomsAttributes */) {
}
#endif // _OMINSTRUMENT

evRunBackward::evRunBackward() {
    NOTIFY_EVENT_CONSTRUCTOR(evRunBackward)
    setId(evRunBackward_Application_id);
}

bool evRunBackward::isTypeOf(const short id) const {
    return (evRunBackward_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evRunBackward, Application, Application, evRunBackward())

evRunForward::evRunForward() {
    NOTIFY_EVENT_CONSTRUCTOR(evRunForward)
    setId(evRunForward_Application_id);
}

bool evRunForward::isTypeOf(const short id) const {
    return (evRunForward_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evRunForward, Application, Application, evRunForward())

evStop::evStop() {
    NOTIFY_EVENT_CONSTRUCTOR(evStop)
    setId(evStop_Application_id);
}

bool evStop::isTypeOf(const short id) const {
    return (evStop_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evStop, Application, Application, evStop())

evMenu::evMenu() {
    NOTIFY_EVENT_CONSTRUCTOR(evMenu)
    setId(evMenu_Application_id);
}

bool evMenu::isTypeOf(const short id) const {
    return (evMenu_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evMenu, Application, Application, evMenu())

evReset::evReset() {
    NOTIFY_EVENT_CONSTRUCTOR(evReset)
    setId(evReset_Application_id);
}

bool evReset::isTypeOf(const short id) const {
    return (evReset_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evReset, Application, Application, evReset())

evMenuExit::evMenuExit() {
    NOTIFY_EVENT_CONSTRUCTOR(evMenuExit)
    setId(evMenuExit_Application_id);
}

bool evMenuExit::isTypeOf(const short id) const {
    return (evMenuExit_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evMenuExit, Application, Application, evMenuExit())

evRaiseStartTime::evRaiseStartTime() {
    NOTIFY_EVENT_CONSTRUCTOR(evRaiseStartTime)
    setId(evRaiseStartTime_Application_id);
}

bool evRaiseStartTime::isTypeOf(const short id) const {
    return (evRaiseStartTime_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evRaiseStartTime, Application, Application, evRaiseStartTime())

evReduceStartTime::evReduceStartTime() {
    NOTIFY_EVENT_CONSTRUCTOR(evReduceStartTime)
    setId(evReduceStartTime_Application_id);
}

bool evReduceStartTime::isTypeOf(const short id) const {
    return (evReduceStartTime_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evReduceStartTime, Application, Application, evReduceStartTime())

evRaiseTimeFactor::evRaiseTimeFactor() {
    NOTIFY_EVENT_CONSTRUCTOR(evRaiseTimeFactor)
    setId(evRaiseTimeFactor_Application_id);
}

bool evRaiseTimeFactor::isTypeOf(const short id) const {
    return (evRaiseTimeFactor_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evRaiseTimeFactor, Application, Application, evRaiseTimeFactor())

evReduceTimeFactor::evReduceTimeFactor() {
    NOTIFY_EVENT_CONSTRUCTOR(evReduceTimeFactor)
    setId(evReduceTimeFactor_Application_id);
}

bool evReduceTimeFactor::isTypeOf(const short id) const {
    return (evReduceTimeFactor_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evReduceTimeFactor, Application, Application, evReduceTimeFactor())

evTimeFactorSetting::evTimeFactorSetting() {
    NOTIFY_EVENT_CONSTRUCTOR(evTimeFactorSetting)
    setId(evTimeFactorSetting_Application_id);
}

bool evTimeFactorSetting::isTypeOf(const short id) const {
    return (evTimeFactorSetting_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evTimeFactorSetting, Application, Application, evTimeFactorSetting())

evStartTimeSetting::evStartTimeSetting() {
    NOTIFY_EVENT_CONSTRUCTOR(evStartTimeSetting)
    setId(evStartTimeSetting_Application_id);
}

bool evStartTimeSetting::isTypeOf(const short id) const {
    return (evStartTimeSetting_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evStartTimeSetting, Application, Application, evStartTimeSetting())

evGoBack::evGoBack() {
    NOTIFY_EVENT_CONSTRUCTOR(evGoBack)
    setId(evGoBack_Application_id);
}

bool evGoBack::isTypeOf(const short id) const {
    return (evGoBack_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evGoBack, Application, Application, evGoBack())

evResetTime::evResetTime() {
    NOTIFY_EVENT_CONSTRUCTOR(evResetTime)
    setId(evResetTime_Application_id);
}

bool evResetTime::isTypeOf(const short id) const {
    return (evResetTime_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evResetTime, Application, Application, evResetTime())

evCalibrate::evCalibrate() {
    NOTIFY_EVENT_CONSTRUCTOR(evCalibrate)
    setId(evCalibrate_Application_id);
}

bool evCalibrate::isTypeOf(const short id) const {
    return (evCalibrate_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evCalibrate, Application, Application, evCalibrate())

evConfigSettingsChangend::evConfigSettingsChangend() {
    NOTIFY_EVENT_CONSTRUCTOR(evConfigSettingsChangend)
    setId(evConfigSettingsChangend_Application_id);
}

bool evConfigSettingsChangend::isTypeOf(const short id) const {
    return (evConfigSettingsChangend_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evConfigSettingsChangend, Application, Application, evConfigSettingsChangend())

evProgrammStart::evProgrammStart() {
    NOTIFY_EVENT_CONSTRUCTOR(evProgrammStart)
    setId(evProgrammStart_Application_id);
}

bool evProgrammStart::isTypeOf(const short id) const {
    return (evProgrammStart_Application_id==id);
}

IMPLEMENT_META_EVENT_P(evProgrammStart, Application, Application, evProgrammStart())

/*********************************************************************
	File Path	: Simulation/DefaultConfig/Application.cpp
*********************************************************************/
