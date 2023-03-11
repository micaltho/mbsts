#ifndef I2CDEVICE_H
#define I2CDEVICE_H

/* --LPCOpen includes. */
#include "chip.h"
#include "board.h"
#include "i2c_17xx_40xx.h"

namespace Platform {
namespace BSP {

/*! @brief Base class of all devices connected via I2C.
 *
 *  This class defines the interface to all I2C devices available at the
 *  EA base board. Don't use this class directly but define a new derived
 *  class.
 */


typedef bool (* LockFctType)(void);  //! < type of callback for mutual exclusion


class I2CDevice {
public:

	/**
	 * I2C hardware interface.
	 */
	enum class Interface {
		I2C0 = I2C_ID_T::I2C0, //!< Use I2C0
		I2C1 = I2C_ID_T::I2C1, //!< Use I2C1
		I2C2 = I2C_ID_T::I2C2  //!< Use I2C2
	};

	/**
	 * I2C mode of operation
	 */
	enum class Mode {
		POLLING, 	//!< Polling mode
		INTERRUPT	//!< Interrupt mode (Interrupt not yet supported!)
	};

	/**
	 * This function initializes the given I2C bus. This function must be called at start-up.
	 * @param ifc defines the I2C bus.
	 * @param mode defines the mode or operation.
	 * @param speed defines the bus speed.
	 * @return true if initialization succeeded or false
	 */
	static bool initialize(Interface ifc, Mode mode, uint32_t speed);

	/**
	 * This function de-initialized the given I2C bus.
	 * @param ifc defines the I2C bus to de-initialize.
	 * @return true if function succeeded or false.
	 */
	static bool deinitialize(Interface ifc);

	/*! @brief Constructor
	 *  @param ifc defines the selected I2C bus connected to.
	 *  @param[in] addr address of the I2C device (defined in hardware specification of device).
	 *  @param[in] dc Dont care. Value is only required to have the same parameter list as
	 *    class \ref SSPDevice
	 */
	I2CDevice(Interface ifc, uint8_t addr, uint8_t dc = 0);

	/*! @cond HIDDEN_DOXYGEN*/

	/* --Forbidden to copy/assign/... any instance of this class. */
	I2CDevice(const I2CDevice&) = delete;
	I2CDevice(I2CDevice&&) = delete;
	I2CDevice& operator=(const I2CDevice&) = delete;
	const I2CDevice& operator=(I2CDevice&&) = delete;

	/* --Default destructor. */
	virtual ~I2CDevice() = default;

	/*! @endcond */

	/**
	 * Read a buffer of bytes from I2Cdevice.
	 * @param buffer defines buffer to store bytes
	 * @param len defines size of buffer
	 * @return @c true if operation was successfully or @c false
	 */
	bool read(uint8_t* buffer, uint32_t& len) const;

	/**
	 * Write a buffer of bytes to I2Cdevice.
	 * @param buffer defines buffer
	 * @param len defines size of buffer
	 * @return @c true if operation was successfully or @c false
	 */
	bool write(uint8_t* buffer, uint32_t& len) const;


	///@{
	/**
	 * Write single byte to given register
	 * @param cmd defines the command/register
	 * @param value defines the value to be written
	 * @return @c true if operation was successfully or @c false
	 */
	bool set(uint8_t cmd, uint8_t value) const;

	/**
	 * Write 2 bytes to given register
	 * @param cmd defines the command/register
	 * @param value defines the value to be written
	 * @return @c true if operation was successfully or @c false
	 */
	bool set(uint8_t cmd, uint16_t value) const;

	/**
	 * Write 4 bytes to given register
	 * @param cmd defines the command/register
	 * @param value defines the value to be written
	 * @return @c true if operation was successfully or @c false
	 */
	bool set(uint8_t cmd, uint32_t value) const;
	///@}

	///@{
	/**
	 * Read single byte from given register
	 * @param cmd defines the command/register
	 * @param value defines location to store value
	 * @return @c true if operation was successfully or @c false
	 */
	bool get(uint8_t cmd, uint8_t& value) const;

	/**
	 * Read 2 bytes from given register
	 * @param cmd defines the command/register
	 * @param value defines location to store value
	 * @return @c true if operation was successfully or @c false
	 */
	bool get(uint8_t cmd, uint16_t& value) const;

	/**
	 * Read 4 bytes from given register
	 * @param cmd defines the command/register
	 * @param value defines location to store value
	 * @return @c true if operation was successfully or @c false
	 */
	bool get(uint8_t cmd, uint32_t& value) const;
	///@}

	///@{
	/**
	 * Send I2C command to device (1 Byte).
	 * @param cmd defines the command (Can be used with enum class values of derived classes).
	 * @param value defines the value corresponding to given command.
	 * @return @c true if operation succeeded or @c false
	 */
	template<typename T> bool cmd(T cmd, uint8_t value) const {
		return set(static_cast<uint8_t>(cmd),value);
	}

	/**
	 * Send I2C command to device (2 Bytes).
	 * @param cmd defines the command (Can be used with enum class values of derived classes).
	 * @param value defines the value corresponding to given command.
	 * @return @c true if operation succeeded or @c false
	 */
	template<typename T> bool cmd(T cmd, uint16_t value) const {
		return set(static_cast<uint8_t>(cmd),value);
	}

	/**
	 * Send I2C command to device (4 Bytes).
	 * @param cmd defines the command (Can be used with enum class values of derived classes).
	 * @param value defines the value corresponding to given command.
	 * @return @c true if operation succeeded or @c false
	 */
	template<typename T> bool cmd(T cmd, uint32_t value) const {
		return set(static_cast<uint8_t>(cmd),value);
	}
	///@}

	///@{
	/**
	 * Receive I2C control value from device (1 Byte).
	 * @param ctrl defines control register of I2C device.
	 * @param value defines control value
	 * @return @c true if write/read access succeeded or @c false.
	 */
	template<typename T> bool ctrl(T ctrl, uint8_t& value) const {
		return get(static_cast<uint8_t>(ctrl),value);
	}

	/**
	 * Receive I2C control value from device (2 Bytes).
	 * @param ctrl defines control register of I2C device.
	 * @param value defines control value
	 * @return @c true if write/read access succeeded or @c false.
	 */
	template<typename T> bool ctrl(T ctrl, uint16_t& value) const {
		return get(static_cast<uint8_t>(ctrl),value);
	}

	/**
	 * Receive I2C control value from device (4 Bytes).
	 * @param ctrl defines control register of I2C device.
	 * @param value defines control value
	 * @return @c true if write/read access succeeded or @c false.
	 */
	template<typename T> bool ctrl(T ctrl, uint32_t& value) const {
		return get(static_cast<uint8_t>(ctrl),value);
	}
	///@}

	/**
	 *  Completes read (transmit)/write (receive) transfer.
	 *  @param[in] txBuf pointer to byte buffer (transmit).
	 *  @param[in] txLen size of transmit buffer.
	 *  @param[out] rxBuf pointer to byte buffer (receive).
	 *  @param[in] rxLen size of receive buffer.
	 *  @return @c true when transfer was completed correctly.
	 */
	bool transfer(uint8_t* txBuf, uint32_t& txLen, uint8_t* rxBuf, uint32_t& rxLen) const;

    /**
     * Assign callback functions for lock and unlock in multithreading applications \n
     * Functions must be user provided.
     * @param[in] l pointer to user lock function
     * @param[in] ul pointer to user unlock function
     * @return @c true if operation was succeeded or @c false
     */
    bool assignLockFct(LockFctType l,LockFctType ul);

protected:

	Interface interface; /*!<I2C bus. */
	uint8_t address; /*!<Hardware address of I2C device (see hardware documentation). */

private:
    LockFctType lock = nullptr;   /**< user function for lock in multithreading applications   */
    LockFctType unlock = nullptr; /**< user function for unlock in multithreading applications */

};

}
}

#endif
