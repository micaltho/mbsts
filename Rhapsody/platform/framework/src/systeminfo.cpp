/*
 * systeminfo.cpp
 *
 *  Created on: 28.06.2016
 *      Author: Michael
 */

#include "systeminfo.h"

#include "FreeRTOS.h"
#include "task.h"

//#include "ffconf.h"

#include "core_cm3.h"

#include <cstdio>

#include "board.h"


namespace Platform {

static char buffer[32];

std::string SystemInformation::rtos() { return "FREERTOS " tskKERNEL_VERSION_NUMBER; }

std::string SystemInformation::fatfs() {
//	sprintf(buffer,"CHAN FAT %06u",_FFCONF);
	return buffer;
}

std::string SystemInformation::build() { return __DATE__ " " __TIME__; }

std::string SystemInformation::compiler() { return __VERSION__; }

std::string SystemInformation::hal() {
	sprintf(buffer,"CMSIS %X",__CM3_CMSIS_VERSION);
	return buffer;
}

std::string SystemInformation::mac() {
	Board_ENET_GetMacADDR((uint8_t*)buffer);
	return std::string("MAC ADDR ") + buffer;
}

void SystemInformation::print() {
		printf("%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n%s\r\n",
				rtos().c_str(),fatfs().c_str(),compiler().c_str(),hal().c_str(),build().c_str(),mac().c_str());
}


}
