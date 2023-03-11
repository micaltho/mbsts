#ifndef DIGITALINOUT_H
#define DIGITALINOUT_H

#include <cstdint>
#include <functional>

/* --Platform includes. */
#include "chip.h"
#include "board.h"

/* --BSP includes. */
#include "PortPin.h"

namespace Platform {

namespace BSP {

/*! @brief Class of general purpose input output pins.
 *
 *  This class defines the interface to GPIO pins. This class can be used
 *  as is or as base class of more sophisticated pins. This class also defines
 *  the interface on interrupt handler routines.
 */

class DigitalInOut : public PortPin {
public:

	/**
	 * This method initialized the GPIO pins and the interrupt handling (if set)
	 * @param alsoInitializeInterruptHandling defines whether to set-up interrupt handling or not
	 * @return @c true if hardware was initialized successfully or @c false
	 */
	static bool initialize(bool alsoInitializeInterruptHandling =true);

	/*! @brief Defines the direction of the GPIO pin.
	 */
	enum class Direction { INPUT /*!<Read from pin.*/, OUTPUT /*!<Write to pin.*/};

	/* --Interrupt Handling. */

	/**
	 * The type specifies when handler should be invoked.
	 */
	enum EdgeType {
		NO_EDGE =0x00,  	          		//!< Does not invoke handler
		FALLING_EDGE =0x01, 				//!< Invoke handler on falling edge
	    RISING_EDGE =0x02,					//!< Invoke handler on rising edge
		ANY_EDGE =FALLING_EDGE|RISING_EDGE  //!< Invoke handler on both edges
	};

	/**
	 * Define interrupt handler type.
	 */
	using InterruptHandler = std::function<void(uint32_t)>;

	/*! @brief Constructor
	 *  @param[in] p defines the port according to LPC1769 specification.
	 *  @param[in] b defines the pin or bit of given port.
	 *  @param[in] d defines the direction
	 */
	DigitalInOut(uint8_t p, uint32_t b, Direction d =Direction::INPUT);

	/*! @cond HIDDEN_DOXYGEN*/

	/* --Forbidden to copy/assign/... any instance of this class. */
	DigitalInOut(const DigitalInOut&) = delete;
	DigitalInOut(DigitalInOut&&) = delete;
	DigitalInOut& operator=(const DigitalInOut&) = delete;
	const DigitalInOut& operator=(DigitalInOut&&) = delete;

	/* --Default destructor. */
	virtual ~DigitalInOut() = default;

	/*! @endcond */

	/*! @brief Sets the pin to true (1) if output.
	 */
	void set() const;

	/*! @brief Sets the pin to false (0) if output.
	 */
	void clear() const;

	/*! @brief Gets value if input.
	 *  @return @c true if pin is set.
	 */
	bool get() const;

	/*! @brief Returns the port number.
	 *  @return the port number (see LPC1769 specification).
	 */
	uint8_t getPort() const { return port(); }

	/*! @brief Returns the pin number.
	 *  @return the pin number (see LPC1769 specification).
	 */
	uint32_t getPin() const { return pin(); }

	/**
	 * Set Interrupt handler.
	 * @param irq defines the interrupt handler routine, e.g. lambda expression
	 * @param edge defines the edge(s) triggering the handler (this enables also the interrupt!)
	 * @return returns true when setting up and enabling succeeded
	 */
	bool onInterrupt(const InterruptHandler& irq, uint32_t edge =NO_EDGE) const;

	/**
	 * Enable interrupt handler.
	 * @param edge defines the edge(s) triggering the handler
	 * @return return true when enabling succeeded or false
	 */
	bool enableInterrupt(uint32_t edge =FALLING_EDGE|RISING_EDGE) const;

	/**
	 * Disable interrupt handler on all trigger
	 * @return true when disabling the interrupt succeeded
	 */
	bool disableInterrupt() const;

	/**
	 * Clear pending interrupt on all trigger
	 * @return true when clearing the pending interrupt succeeded
	 */
	bool clearPendingInterrupt() const;

};

}
}

#endif
