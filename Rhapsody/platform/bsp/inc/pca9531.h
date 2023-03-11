#ifndef LED8DIMMER_H
#define LED8DIMMER_H

/* --Platform includes. */
#include "i2cdevice.h"

namespace Platform {

namespace BSP {

/*! @brief Interface class to 8 LED dimmer.
 *
 *  This class defines the interface to PCA9531 device at the Eval board.
 *  The device has 8 LEDs with different colors which can be enabled or disabled.
 *  For more information of the capabilities see given hardware specification.
 */

class PCA9531 : public I2CDevice {
public:


    /*! @brief Identifier addressing LED on EA base board. */
    enum Identifier {
        /* --LED0-LED7: Red. */
        LED0 =0x0001  /*!< 1st red    LED. */,
        LED1 =LED0<<1 /*!< 2nd red    LED. */,
        LED2 =LED0<<2 /*!< 3rd yellow LED. */,
        LED3 =LED0<<3 /*!< 4th yellow LED. */,
        LED4 =LED0<<4 /*!< 5th green  LED. */,
        LED5 =LED0<<5 /*!< 6th green, LED. */,
        LED6 =LED0<<6 /*!< 7th blue   LED. */,
        LED7 =LED0<<7 /*!< 8th blue   LED. */,
    };

    /*! @brief identifies Output state of LED. */
    enum class LedState
    {
       OFF = 0,     /*!< Output is set Hi-Z (LED off – default) */
       ON,          /*!< Output is set LOW (LED on)             */
       BLINKPWM0,   /*!< Output blinks at PWM0 rate             */
       BLINKPWM1    /*!< Output blinks at PWM1 rate            */
    };

    /*! @brief Mode of single LED. */
    enum Mode {
        OFF =0x00 /*!<Disable LED.*/,
        ON =0x01 /*!<Enable LED. */
    };

    /*! @brief Constructor
     *  @param[in] ifc defines I2C bus.
     *  @param[in] addr I2C hardware address.
     */
    PCA9531(Interface ifc = Interface::I2C2, uint8_t addr =0x60);

    /*! @brief Configure blink frequency and brightness (see hardware specification).
     *  @param[in] freq0 defines frequency of first group of LEDs.
     *  @param[in] freq1 defines frequency of second group of LEDs.
     *  @param[in] pwm0 defines brightness of first group.
     *  @param[in] pwm1 defines brightness of second group.
     */
    void configure(uint8_t freq0, uint8_t freq1, uint8_t pwm0, uint8_t pwm1) const;

    /*! @brief Enable or disable LED.
     *  @param[in] id 16 value representing the LEDs.
     *  @param[in] m enable or disable.
     */
    void select(uint16_t id, Mode m =ON) const;

    /*! @brief Shift the lights to left.
     *  @param[in] pos number of positions shifting to the left.
     */
    void shiftleft(uint32_t pos) const;

    /*! @brief Shift the lights to right.
     *  @param[in] pos number of positions shifting to the right.
     */
    void shiftright(uint32_t pos) const;

    /*! @brief Rotate the lights to left.
     *  @param[in] pos number of positions rotating to the left.
     * */
    void rotateleft(uint32_t pos) const;

    /*! @brief Rotate the lights to right.
     *  @param[in] pos number of positions rotating to the right.
     */
    void rotateright(uint32_t pos) const;

    /*! @brief Get the status of LEDs.
     *  @return the status bits.
     */
    uint16_t getStatus() const;

    /*! @brief Get the status of one specific LED.
     *  @param[in] led to request status from.
     *  @return the status of LED.
     */
    LedState getLedStatus(Identifier led) const;

    /*! @brief Set the status of LEDs.
     *  @param[in] stat the the status bits.
     */
    void setStatus(uint16_t stat) const;

    /*! @brief All lights on. */
    void on() const;

    /*! @brief All lights off. */
    void off() const;

private:
    /**
     * Internal register set.
     */
    enum class Register : uint8_t {
        INPUT = 0x00,          //!< INPUT0
        PSC0,                   //!< PSC0
        PWM0,                   //!< PWM0
        PSC1,                   //!< PSC1
        PWM1,                   //!< PWM1
        LS0,                    //!< LS0
        LS1,                    //!< LS1
        /* --With auto-increment enabled. */
        INPUT_AI=INPUT|(1<<4),//!< INPUT0_AI
        PSC0_AI,                //!< PSC0_AI
        PWM0_AI,                //!< PWM0_AI
        PSC1_AI,                //!< PSC1_AI
        PWM1_AI,                //!< PWM1_AI
        LS0_AI,                 //!< LS0_AI
        LS1_AI,                 //!< LS1_AI
    };


};

/* --Inline methods. */

inline void PCA9531::setStatus(uint16_t stat) const {
    cmd(Register::LS0_AI,stat);
}

/*! @brief All lights on. */
inline void PCA9531::on() const {
    setStatus(0x5555);
}

/*! @brief All lights off. */
inline void PCA9531::off() const {
    setStatus(0x0);
}

}

}

#endif
