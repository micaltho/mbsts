/**
 *  \file      dac.h
 *  \brief     access to DAC of LPC1769.
 *  \details   Configures HW, allows write access to dac.
 *             DMA is not implemented
 *             The only available DAC channel is mapped to Port 0 Pin 26!
 *
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      10.12.2020
 *  \pre
 *  \copyright HS Osnabrueck
 */

#ifndef PLATFORM_BSP_INC_DAC_H_
#define PLATFORM_BSP_INC_DAC_H_
#include <cstdint>

namespace Platform
{
namespace BSP
{
/*! @brief static class of to write to the Digital-to-Analog Converter (DAC)
 *
 *  This class initializes the DAC and provides a setter.\n
 * \note It is not possible to make an object of this class!\n
 *   Only static methods are provided
 *  \note P0.26 is the only DAC Pin
 */
class Dac
{
public:
    /**
     * Available DAC Rates
    */
    enum class UpDateTimes_e
    {
        MAX_UPDATE_RATE_1MHz = 0,   //!< High speed, higher energy consumption
        MAX_UPDATE_RATE_400kHz      //!< Low speed, less energy consumption
    };

    /**!
     * @brief Initialize the DAC channel.
     * P0.26 is initialized as DAC output, dac goes in 400kHz mode.
    */
    static void initialize();

    /**
     * @brief Deinitialize the DAC channel.
     *
    */
    static void deinitialize();

    /**
     * @brief set DAC output  value
     * @param[in] value DAC value to set. Only 10 bits are used
     *
    */
    static void setAnalog(std::uint16_t value);

    /**
     * @brief set update rate of dac, speed and energy consumption are effected
     * @param[in] rate as defined in \ref UpDateTimes_e
     *
    */
    static void setUpdateRate(UpDateTimes_e rate);

    /**
      * @brief gets update rate of dac
      * @returns update rate in \ref UpDateTimes_e
      *
    */
    static UpDateTimes_e getUpdateRate();

private:
    Dac() = delete;
    ~Dac() = delete;
    Dac(const Dac&) = delete;
    Dac(const Dac&&) = delete;
    Dac& operator=(const Dac&) = delete;
    Dac& operator=(const Dac&&) = delete;
};

} /* namespace Framework */
} /* namespace Platform */

#endif /* PLATFORM_BSP_INC_DAC_H_ */
