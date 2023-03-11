/*
 * isl29003.cpp
 *
 *  Created on: 20.06.2016
 *      Author: Michael
 */

#include "isl29003.h"

namespace Platform {

namespace BSP {

ISL29003::ISL29003(Interface ifc, uint8_t arr):I2CDevice(ifc,arr) {}

bool ISL29003::enable() {
//	uint8_t reg=static_cast<uint8_t>(Register::COMMAND);
//	return set(reg,1<<7);

	uint8_t value=1<<7;

	return cmd(Register::COMMAND,value);

}


bool ISL29003::disable() {
	return false;
}


bool ISL29003::raw(uint16_t& value) const {
	uint8_t reg=static_cast<uint8_t>(Register::LSB_SENSOR);
	return get(reg,value);
}



} /* --BSP */
} /* --Platform */
