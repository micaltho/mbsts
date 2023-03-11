/********************************************************************
	Rhapsody	: 9.0 
	Login		: joklappe
	Component	: LPC1769 
	Configuration 	: DefaultConfig
	Model Element	: Application
//!	Generated Date	: Thu, 25, Aug 2022  
	File Path	: LPC1769/DefaultConfig/Application.cpp
*********************************************************************/

#include "Application.h"
#include "AccelerationData.h"
#include "AccelerationMeasuring.h"
#include "ConfigStorage.h"
#include "Controller.h"
#include "Display.h"
#include "DisplayTask.h"
#include "EepromData.h"
#include "TimeCounter.h"
//## package Application



evRunBackward::evRunBackward(void) {
    setId(evRunBackward_Application_id);
}

const RXF::Event::Id_t evRunBackward_Application_id(19801);

evRunForward::evRunForward(void) {
    setId(evRunForward_Application_id);
}

const RXF::Event::Id_t evRunForward_Application_id(19802);

evStop::evStop(void) {
    setId(evStop_Application_id);
}

const RXF::Event::Id_t evStop_Application_id(19803);

evMenu::evMenu(void) {
    setId(evMenu_Application_id);
}

const RXF::Event::Id_t evMenu_Application_id(19804);

evReset::evReset(void) {
    setId(evReset_Application_id);
}

const RXF::Event::Id_t evReset_Application_id(19805);

evMenuExit::evMenuExit(void) {
    setId(evMenuExit_Application_id);
}

const RXF::Event::Id_t evMenuExit_Application_id(19806);

evRaiseStartTime::evRaiseStartTime(void) {
    setId(evRaiseStartTime_Application_id);
}

const RXF::Event::Id_t evRaiseStartTime_Application_id(19807);

evReduceStartTime::evReduceStartTime(void) {
    setId(evReduceStartTime_Application_id);
}

const RXF::Event::Id_t evReduceStartTime_Application_id(19808);

evRaiseTimeFactor::evRaiseTimeFactor(void) {
    setId(evRaiseTimeFactor_Application_id);
}

const RXF::Event::Id_t evRaiseTimeFactor_Application_id(19809);

evReduceTimeFactor::evReduceTimeFactor(void) {
    setId(evReduceTimeFactor_Application_id);
}

const RXF::Event::Id_t evReduceTimeFactor_Application_id(19810);

evTimeFactorSetting::evTimeFactorSetting(void) {
    setId(evTimeFactorSetting_Application_id);
}

const RXF::Event::Id_t evTimeFactorSetting_Application_id(19811);

evStartTimeSetting::evStartTimeSetting(void) {
    setId(evStartTimeSetting_Application_id);
}

const RXF::Event::Id_t evStartTimeSetting_Application_id(19812);

evGoBack::evGoBack(void) {
    setId(evGoBack_Application_id);
}

const RXF::Event::Id_t evGoBack_Application_id(19813);

evResetTime::evResetTime(void) {
    setId(evResetTime_Application_id);
}

const RXF::Event::Id_t evResetTime_Application_id(19814);

evCalibrate::evCalibrate(void) {
    setId(evCalibrate_Application_id);
}

const RXF::Event::Id_t evCalibrate_Application_id(19815);

evConfigSettingsChangend::evConfigSettingsChangend(void) {
    setId(evConfigSettingsChangend_Application_id);
}

const RXF::Event::Id_t evConfigSettingsChangend_Application_id(19816);

evProgrammStart::evProgrammStart(void) {
    setId(evProgrammStart_Application_id);
}

const RXF::Event::Id_t evProgrammStart_Application_id(19817);

evStart::evStart(void) {
    setId(evStart_Application_id);
}

const RXF::Event::Id_t evStart_Application_id(19818);

evGoBackToRunHourglass::evGoBackToRunHourglass(void) {
    setId(evGoBackToRunHourglass_Application_id);
}

const RXF::Event::Id_t evGoBackToRunHourglass_Application_id(19819);

/*********************************************************************
	File Path	: LPC1769/DefaultConfig/Application.cpp
*********************************************************************/
