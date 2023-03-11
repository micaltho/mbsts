#ifndef PLATFORM_BSP_INC_ADC_H_
#define PLATFORM_BSP_INC_ADC_H_

/* --Platform includes. */
#include <chip.h>

namespace Platform
{
namespace BSP
{

/*! @brief class of to read the Analog-to-Digital Converter (ADC)
 *
 *  This class initializes the ADC and provides a getter. If more than one instance with different
 *  channels exist, the ADC is used in burst mode and will stay in this mode.
 */

class Adc
{
public:
    /**
     * Available ADC Channels, determines used pin
     */
    enum class Input_e
    {
        AD0 = 0,     //!< AD0.0  (Port 0  Pin 23)
        AD1,         //!< AD0.1  (Port 0  Pin 24)
        AD2,         //!< AD0.2  (Port 0  Pin 25)
        AD3,         //!< AD0.3  (Port 0  Pin 26)
        AD4,         //!< AD0.4  (Port 1  Pin 30)
        AD5,         //!< AD0.5  (Port 1  Pin 31)
        AD6,         //!< AD0.6  (Port 0  Pin  3)
        AD7          //!< AD0.7  (Port 0  Pin  2)
    };

    /**
     * Constructor to initialize the ADC channel. If more than one channel is used, the ADC goes in burst mode.
     * @param[in]  adPin ADC Channel. A channel is associated with a Pin of the LPC
     */
    Adc(Input_e adPin);

    /* --Default destructor. */
    virtual ~Adc() = default;

    /*! @brief get ADC value.
     *  @return  conversion result for channel, 0xFFFF in case of error
     */
    uint16_t getValue() const;
private:
    /**
     * Mode, ADC might be in Burst or SW controlled mode
     */
    enum class Mode_e
    {
        NOBURST = 0,  //!< SW controlled mode
        BURST         //!< Burst mode
    };

    const ADC_CHANNEL_T m_channel;       ///<  channel number (0-7)
    static uint32_t s_usedChannels;      ///<  stores the used channels of the ADC. Is the same for all instances
    static Mode_e   s_mode;              ///<  stores burst or SW controlled mode. Is the same for all instances
};


} /* namespace BSP */
} /* namespace Platform */

#endif /* PLATFORM_BSP_INC_ADC_H_ */
