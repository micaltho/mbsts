#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <cstdint>

/* --Local includes. */
#include "digitalinout.h"
#include "chip.h"


namespace Platform {

namespace BSP {

/*! @brief Interrupt manager.
 *
 *  This class is the managing instance keeping all interrupt handling objects.
 *  There should be exactly _one_ instance of this class system-wide. In order
 *  to enable an interrupt, attach the interrupt handler object and enable
 *  the manager.
 *
 *  THIS IS ONLY FOR INTERNAL USAGE OF Platform::BSP LIBRARY!
 *
 */

class InterruptManager {

public:

    /*! @brief Standard constructor. */
    InterruptManager();

    /*! @cond HIDDEN_DOXYGEN*/

    /* --Forbidden to copy/assign/... any instance of this class. */
    InterruptManager(const InterruptManager&) = delete;
    InterruptManager(InterruptManager&&) = delete;
    InterruptManager& operator=(const InterruptManager&) = delete;
    const InterruptManager& operator=(InterruptManager&&) = delete;

    /* --Default destructor. */
    virtual ~InterruptManager() = default;

    /*! @endcond */

    /**
     * Setting an interrupt handler object under control of the manager.
     * @param gpio defines the associated pin of the interrupt
     * @param ih defines the interrupt handler routine.
     * @return @c true if attach method succeeded.
     */
    bool attach(const DigitalInOut& gpio, const DigitalInOut::InterruptHandler& ih) const;

    /**
     * release an interrupt handler object from control of the manager.
     * @param gpio defines the associated pin of the interrupt
     * @return @c true if detach method succeeded.
     */
    bool detach(const DigitalInOut& gpio) const;


    /*! @brief Enable the manager and all attached interrupt handling methods. */
    /*! @note This method sets priority to 6 to allow FreeRTOS calls in ISRs!  */
    void enable();

    /*! @brief Disable the manager and all attached interrupt handling methods. */
    void disable();

    /**
     * Enable interrupt at pin
     * @param gpio defines the pin to be enabled
     * @param edge defines the trigger
     * @return @c true if succeeded or @c false
     */
    bool enable(const DigitalInOut& gpio, uint32_t edge) const;

    /**
     * Disable interrupt at pin
     * @param gpio defines the pin to be enabled
     * @return @c true if succeeded or @c false
     */
    bool disable(const DigitalInOut& gpio) const;

    /**
     * clear interrupt at pin
     * @param gpio defines the interrupt pin to be cleared
     * @return @c true if succeeded or @c false
     */
    bool clear(const DigitalInOut& gpio) const;


    /*! @cond HIDDEN_DOXYGEN*/

    /* --Search table for interrupt handling routine. DON'T CALL THIS! */
    static void resolve();

    /*! @endcond */

private:

    typedef enum
    {
        PORT0_NHANDLER = 32,
        PORT2_NHANDLER= 14,
        NHANDLER = PORT0_NHANDLER+PORT2_NHANDLER
    } NUMOFHANDLER;

    /* --Error when interrupt handler is missing. */
    static void failure(uint32_t );

    /*! @brief resolve the interrupt and call handler
     *  \param[in] port     must be GPIOINT_PORT0
     *  \param[in] handler  pointer to field of interrupt handler
     *  \param[in] numOfHandler max. number of handler in field \ref handler
     */
    static void resolve(LPC_GPIOINT_PORT_T port, uint32_t offset, NUMOFHANDLER numOfHandler);


    /* --Only port P0.0-P0.30 (32) and port P2.0-P2.13 (14) is supported by LPC1769. */

    bool isInterruptible(uint32_t port, uint32_t pin) const {
    	return ((port==0 && pin<PORT0_NHANDLER)||(port==2 && pin<PORT2_NHANDLER)) ? true: false;
    }

    LPC_GPIOINT_PORT_T getIntPort(uint32_t port) const {return port == 0 ? GPIOINT_PORT0 : GPIOINT_PORT2;}

    /*! @brief Checks the associated edge type.
       *  @param[in] e the edge type to be checked.
       *  @returns @c true if given edge is source of interrupt. */
    bool isTrigger(uint32_t event, DigitalInOut::EdgeType e) const { return e&event; }


    /* --Interrupt handler array. */
    static DigitalInOut::InterruptHandler handler[NHANDLER];

};

}

}

#endif
