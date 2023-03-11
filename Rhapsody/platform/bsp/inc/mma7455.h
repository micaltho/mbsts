#ifndef MMA7455_H
#define MMA7455_H

#include "i2cdevice.h"

namespace Platform {

namespace BSP {

/*! @brief Interface class to EA base board accelerator.
 *
 *  This class defines the interface to MMA7455 mounted on
 *  the EA base board (see MMA7455L hardware documentation for details).
 */

class MMA7455 : public I2CDevice {
public:

	/**
	 * Internal register set.
	 */
	enum class Register : uint8_t {
		XOUTL = 0x00,//!< XOUTL
		XOUTH,       //!< XOUTH
		YOUTL,       //!< YOUTL
		YOUTH,       //!< YOUTH
		ZOUTL,       //!< ZOUTL
		ZOUTH,       //!< ZOUTH
		XOUT8,       //!< XOUT8
		YOUT8,       //!< YOUT8
		ZOUT8,       //!< ZOUT8
		STATUS,      //!< STATUS
		DETSRC,      //!< DETSRC
		TOUT,        //!< TOUT
		RESERVED_0C, //!< RESERVED_0C
		I2CAD,       //!< I2CAD
		USRINF,      //!< USRINF
		WHOAMI,      //!< WHOAMI
		XOFFL,       //!< XOFFL
		XOFFH,       //!< XOFFH
		YOFFL,       //!< YOFFL
		YOFFH,       //!< YOFFH
		ZOFFL,       //!< ZOFFL
		ZOFFH,       //!< ZOFFH
		MCTL,        //!< MCTL
		INTRST,      //!< INTRST
		CTL1,        //!< CTL1
		CTL2,        //!< CTL2
		LDTH,        //!< LDTH
		PDTH,        //!< PDTH
		PW,          //!< PW
		LT,          //!< LT
		TW,          //!< TW
		RESERVED_1F  //!< RESERVED_1F
	};


	/*! @brief Mode of operation of MMA7455. */
	enum Mode {
		STANDBY /*! <Low Power Mode [not yet implemented]. */,
		MEASUREMENT /*! <Continuous Measurements. */,
		LEVEL_DETECTION /*! <[not yet implemented]. */,
		PULSE_DETECTION /*! <[not yet implemented]. */
	};

	/*! @brief Range of measurement. */
	enum GRange {
		RANGE_2G /*! <[-2g,...,+2g] Range of measurement. */,
		RANGE_4G /*! <[-4g,...,+4g] Range of measurement. */,
		RANGE_8G /*! <[-8g,...,+8g] Range of measurement. */
	};

	/*! @brief Standard constructor.
	 *  @param[in] ifc defines I2C bus.
	 *  @param[in] addr hardware address of I2C device (hardware dependent).
	 */
	MMA7455(Interface ifc = Interface::I2C2, uint8_t addr = 0x1d);

	/*! @brief Set Mode of Operation.
	 *  @param[in] m defines the mode.
	 *  @param[in] gr defines g-range.
	 *  @return @c true if mode was set correctly.
	 */
	bool control(Mode m = MEASUREMENT, GRange gr = RANGE_2G) const;

	/*! @brief Read Data from Sensor.
	 *  @param[out] x acceleration in x direction.
	 *  @param[out] y acceleration in y direction.
	 *  @param[out] z acceleration in z direction.
	 *  @return @c true if read was done correctly.
	 */
	bool raw(int8_t& x, int8_t& y, int8_t& z) const;

	/*! @brief Read mode control register 0x16.
	 *  @return content of mode control register. */
	uint8_t modeControl() const;

	/*! @brief read status register 0x09.
	 *  @return content of status register. */
	uint8_t status() const;


};

}


}

#endif
