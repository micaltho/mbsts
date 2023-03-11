/**
 *  \brief     Implements an interface to temperature sensor.
 *  \details   This file defines the interface to temperature sensor mounted on
 *             the EA base board (see hardware documentation for details).
 * \warning:   HW Timer 1 is used. Run time statistics of OS are not possible anymore.
 * \warning:   the measurement is NOT reentrant. The access to temperature sensor is blocking!
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      29.09.2015
 *  \pre
 *  \copyright HS Osnabrueck
 */

/** @file */
#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_

#include "interrupt.h"
#include "digitalinout.h"

namespace Platform {
namespace BSP {

  /*! @brief Interface class to EA base board temperature sensor.
   *
   *  This class defines the interface to temperature sensor mounted on
   *  the EA base board (see hardware documentation for details).\n
   *  The class follows the singleton design pattern as it uses the ressource
   *  Temperature sensor and Timer1 for measurement. The GPIO Pin used for measurement
   *  is hard coded in enum DIGITALPIN
   */


class MAX6576 {
private:

    enum DIGITALPIN          /// defines port and pin used for measurement
    {
        PORT=0,              ///< port number, depends on J25 on EA Board
        PIN=2                ///< pin  number, depends on J25 on EA Board
    };
    enum MEASSURE_STATE      /// states of measurement state machine
    {
        INIT,                ///< Timer is configured
        RUNNING,             ///< Timer value is read, measurement completed
        READY                ///<  Measurement completed, no action
    };
    enum DIVIDER6576         /// possible dividers for frequency, defined by HW J26.
    {
        TEN=10,              ///< J26: TS1 = 0, TS0 = 0
        FORTY=40,            ///< J26: TS1 = 0, TS0 = 1
        HUNDDREDSIXTY=160,   ///< J26: TS1 = 1, TS0 = 0
        SIXHANDREDFORTY=640  ///< J26: TS1 = 1, TS0 = 1
    };

    // attributes:
    uint32_t         requestedInstances;       ///< counts calls to \ref getInstance Methode
    uint32_t         enabledCount;             ///< counts number of concurrent measurement requests
    DIVIDER6576      m_skalarMultiplier;       ///< multiplier configured in HW, see J26 setting on EA Board

    InterruptManager irManager;                ///< interrupt manager
    Platform::BSP::DigitalInOut  tempIRQ;      ///< GPIO Pin used for measurement, see J25 setting, in SW fix P0.2

    MEASSURE_STATE    m_measureState;          ///< state of state machine in interrupt service routine
    uint16_t          m_measuredUs;            ///< result of measurement, T = m_measuredUs / m_skalarMultiplier
    uint32_t          m_firstTime;

    uint32_t          m_ticksPerUs;            ///< timer ticks per us


    // methods
    // constructors and destructor are private, class is a singleton!
    /// \brief private constructor\n
    ///  class follows singleton design pattern.
    MAX6576();

    /*! @cond HIDDEN_DOXYGEN*/

    /* --Forbidden to copy/assign/... any instance of this class. */
    MAX6576(const MAX6576&) = delete;
    MAX6576& operator=(const MAX6576&)  = delete;
    const MAX6576& operator=(MAX6576&&) = delete;
    /*! @endcond */

    /// \brief destructor, should never be called
    virtual ~MAX6576()
    {
        // detach Interrupt
        tempIRQ.disableInterrupt();
    };


    /// \brief setup of timer for measurement
    /// \returns nothing
    void setup();

    /// \brief prepares for measurements, enables interrupt, sets isr
    /// \returns status of function
    bool open();

    /// \brief finishs measurements, disables interrupt
    /// \returns status of function
    bool close();

    /// \brief interrupt service routine, triggered by falling edge at \ref tempIRQ pin
    /// \param[in] edge edge type which triggerd interrupt
    /// \returns   nothing
    void isr(Platform::BSP::DigitalInOut::EdgeType edge);
public:
    /**
     * get reference of temperature sensor class
     * @return reference to temperature sensor
     */
    static MAX6576 &getInstance();
    /**
     * get temperature in Celsius
     * @return temperature in degree Celsius
     */
    int16_t   getTemperature();
    /**
     * get temperature in Kelvin
     * @return temperature in degree Kelvin
     */
    uint16_t  getTempKelvin();
};

}  // namespace BSP
}  // namespace Platform

#endif /* TEMPSENSOR_H_ */

