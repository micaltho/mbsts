/*
 * isl29003.h
 *
 *  Created on: 20.06.2016
 *      Author: Michael
 */

#ifndef BSP_INC_ISL29003_H_
#define BSP_INC_ISL29003_H_

#include "i2cdevice.h"

namespace Platform {
namespace BSP {

/**
 * This class is an abstraction of the light sensor (see hardware specification).
 */

class ISL29003 : public I2CDevice {
public:

	/**
	 * Internal register set.
	 */
	enum class Register : uint8_t {
		COMMAND =0x00, //!< COMMAND
		CONTROL,       //!< CONTROL
		THRESHOLD_HIGH,//!< THRESHOLD_HIGH
		THRESHOLD_LOW, //!< THRESHOLD_LOW
		LSB_SENSOR,    //!< LSB_SENSOR
		MSB_SENSOR,    //!< MSB_SENSOR
		LSB_TIMER,     //!< LSB_TIMER
		MSB_TIMER      //!< MSB_TIMER
	};

	/**
	 * Constructor.
	 * @param ifc defines the I2C bus
	 * @param arr defines the I2C address
	 */
	ISL29003(Interface ifc =Interface::I2C2, uint8_t arr =0x44);

	/**
	 * Enables the light sensor.
	 * @return @c true if enabling was successfully or @c false
	 */
	bool enable();

	/**
	 * Disable the light sensor (not implemented).
	 * @return @c true if disabling was successfully or @c false
	 */
	bool disable();

	/**
	 * Read light sensor.
	 * @param value is the variable to store the raw value
	 * @return @c true if reading succeeded or @c false
	 */
	bool raw(uint16_t& value) const;

};


}
}

#endif /* BSP_INC_ISL29003_H_ */
