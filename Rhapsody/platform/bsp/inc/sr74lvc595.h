#ifndef LED7SEGMENT_H
#define LED7SEGMENT_H

#include <cstdint>

/* --Local include. */
#include "sspdevice.h"

namespace Platform {

namespace BSP {

/*! @brief Class to control 7 respective 8 segment display of the EA base board.*/

class SR74LVC595 : public SSPDevice {

public:

	/*! @brief Constructor
	 *  @param[in] ifc SPI interface of the device
	 *  @param[in] port defines the port of the slave selection signal (see EA schematics).
	 *  @param[in] pin defines the pin of the slave selection signal.
	 *  @param[in] initial set LEDs to value when object is constructed.
	 */
	SR74LVC595(Interface ifc, uint8_t port, uint8_t pin, uint8_t initial =0xff);

	/*! @brief Sets individual segments.
	 *  @param[in] value addressing the segments.
	 */
	bool set(uint8_t value) const;

	/*! @brief Sets all segments to off. */
	bool off() const;

};

}

}
#endif
