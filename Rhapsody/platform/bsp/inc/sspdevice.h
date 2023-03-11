/*
 * sspdevice.h
 *
 *  Created on: 21.06.2016
 *      Author: Michael
 */

#ifndef BSP_INC_SSPDEVICE_H_
#define BSP_INC_SSPDEVICE_H_

/* --LPCOpen includes. */
#include "chip.h"
#include "board.h"
#include "ssp_17xx_40xx.h"

#include "digitalinout.h"

namespace Platform {
namespace BSP {

/**
 * This class is the generalized class of all devices connected to SPI interface.
 */


typedef bool (* LockFctType)(void);  //! < type of callback for mutual exclusion


/*! @brief Base class for Devices using SPI
 *
 */

class SSPDevice {
public:

    /**
     * Hardware interface (see LPC1769 hardware specification)
     */
    enum class Interface {
        SSP0,//!< SSP0
        SSP1 //!< SSP1
    };

    /**
     * This function initializes the given SPIC bus. This function must be called at start-up.
     * @param ifc defines the SPI bus.
     * @return true if initialization succeeded or false
     */
    static bool initialize(Interface ifc);

    /**
     * This function de-initialized the given SPI bus.
     * @param ifc defines the SPI bus to de-initialize.
     * @return true if function succeeded or false.
     */
    static bool deinitialize(Interface ifc);

    /**
     * Constructor
     * @param ifc defines the hardware interface connected to
     * @param port defines the port identifier of slave select signal
     * @param pin defines the pin of slave select signal
     */
    SSPDevice(Interface ifc, uint8_t port, uint8_t pin);

    /*! @cond HIDDEN_DOXYGEN*/

    /* --Forbidden to copy/assign/... any instance of this class. */
    SSPDevice(const SSPDevice&) = delete;
    SSPDevice(SSPDevice&&) = delete;
    SSPDevice& operator=(const SSPDevice&) = delete;
    const SSPDevice& operator=(SSPDevice&&) = delete;

    /* --Default destructor. */
    virtual ~SSPDevice() = default;

    /*! @endcond */

    /**
     * Read buffer.
     * @param buffer defines buffer
     * @param len defines length of buffer
     * @return @c true if operation was succeeded or @c false
     */
    bool read(uint8_t* buffer, uint32_t& len) const;

    /**
     * Write buffer.
     * @param buffer defines buffer
     * @param len defines length of buffer
     * @return @c true if operation was succeeded or @c false
     */
    bool write(uint8_t* buffer, uint32_t& len) const;

    /**
     * Write single byte.
     * @param value defines value to write to
     * @return @c true if operation was succeeded or @c false
     */
    bool write(uint8_t value) const;


    /**
     * Assign callback functions for lock and unlock in multithreading applications \n
     * Functions must be user provided.
     * @param[in] l pointer to user lock function
     * @param[in] ul pointer to user unlock function
     * @return @c true if operation was succeeded or @c false
     */
    bool assignLockFct(LockFctType l,LockFctType ul);

protected:

    /**
     * Acquire SPI bus for this device.
     */
    void acquire() const;

    /**
     * Release SPI bus for this device.
     */
    void release() const;

    /** Slave select pin
      \note This pin must be configured as GPIO, do not use HW SSEL function.
       HW function only works in case there is just one slave connected to SPI
     */
    Platform::BSP::DigitalInOut ssel;
    LPC_SSP_T* interface;     /**< Internal LPCopen device */
    Interface  sym_interface; /**< Hardware device */

private:
    LockFctType lock;      /**< user function for lock in multithreading applications   */
    LockFctType unlock;    /**< user function for unlock in multithreading applications */
};

}  // namespace BSP
}  // namespace Platform


#endif /* BSP_INC_SSPDEVICE_H_ */
