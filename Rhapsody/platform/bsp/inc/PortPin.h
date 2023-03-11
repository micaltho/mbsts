/*
 * PortPin.h
 *
 *  Created on: 09.09.2016
 *      Author: Michael
 */

#ifndef BSP_INC_PORTPIN_H_
#define BSP_INC_PORTPIN_H_

#include <cstdint>

/* --LPCOpen Includes. */
#include "iocon_17xx_40xx.h"

namespace Platform {
namespace BSP {

/**
 * This class defines a single pin that can be multiplexed.
 */

class PortPin {
public:

	/**
	 * This defines the selected function 0-3 of multiplexed pin (see LPC1769 hardware specification).
	 */
	enum Function {
		FUNCTION0 =IOCON_FUNC0,//!< Function 0 (usually GPIO)
		FUNCTION1 =IOCON_FUNC1,//!< Function 1
		FUNCTION2 =IOCON_FUNC2,//!< Function 2
		FUNCTION3 =IOCON_FUNC3 //!< Function 3
	};

	/**
	 * Default constructor.
	 */
	PortPin():mport(-1),mpin(-1) {}

	/**
	 * Constructor.
	 * @param po defines the port identifier
	 * @param pi defines the pin
	 * @param fun defines the function
	 * @param mode defines the mode of operation
	 */
	PortPin(uint8_t po, uint8_t pi, Function fun =FUNCTION0, uint32_t mode =IOCON_MODE_INACT);


	/*! @cond HIDDEN_DOXYGEN*/

	/* --Forbidden to copy/assign/... any instance of this class. */
	PortPin(const PortPin&) = delete;
	PortPin(PortPin&&) = delete;
	PortPin& operator=(const PortPin&) = delete;
	const PortPin& operator=(PortPin&&) = delete;

	/* --Default destructor. */
	virtual ~PortPin() = default;

	/*! @endcond */

	/**
	 * Access port identifier.
	 * @return the port of the pin
	 */
	uint8_t port() const { return mport; }

	/**
	 * Access pin of given port.
	 * @return the pin within the port.
	 */
	uint8_t pin() const { return mpin; }

protected:

	uint8_t mport /** Port */, mpin /** Pin*/;

};

inline PortPin::PortPin(uint8_t po, uint8_t pi, Function fun, uint32_t mode):mport(po),mpin(pi) {
	/* --Set Multiplexing. */
	Chip_IOCON_PinMuxSet(LPC_IOCON,mport,mpin,mode | fun);
}






}

}



#endif /* BSP_INC_PORTPIN_H_ */
