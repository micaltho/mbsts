/**
 *  \brief     Implements an interface to a display with SSD1306 driver device.
 *  \details   This file defines the interface to a Display using I2C bus.\n
 *             For more details see e.g. <https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf> \n
 *
 *  \author    J. Wuebbelmann
 *  \version   2.0
 *  \date      02.05.2020
 *  \pre
 *  \copyright HS Osnabrueck
 */

/** @file */


#ifndef SSD1306_H
#define SSD1306_H

#include "i2cdevice.h"
#include "MonoChromeDisplay.h"

namespace Platform {
namespace BSP {


/**
  * \brief
 * SSD1306 can control 128x64 pixel output.
 * The default 5x7 font allows 20 columns and 8 rows.
 *
 */


class SSD1306 : public MonoChromeDisplay<I2CDevice> {
public:

    /*! @brief Standard constructor. */
    SSD1306(Interface ifc);
    ~SSD1306();

    /**
     * Just demo picture.
     */
    void showDemoPicture();


public:
    /**
     * Initialize the SSD display.
     * @param w defines the width of the display
     * @param h defines the height
     * @param fill defines initial fill pattern
     * @param [in] buffer defines an memory region where framebuffer is stored.
     *  If \a buffer equals @c nullptr, the framebuffer is allocated dynamically.
     *
     * @return @c true if initialization succeeded or @c false
     */
    bool initialize(uint32_t w =128,
                    uint32_t h =64,
                    uint8_t fill =0x00,
                    uint8_t* buffer = nullptr) override;

    /**
     * Enable display.
     */
    void on() const override;

    /**
     * Disable display.
     */
    void off() const override;

    /**
     * Flush (transfer internal frame buffer to display).
     * @return @c true if flushed succeeded or @c false
     */
    bool flush() const override;

protected:
    /**
     * Send buffer to device (command mode). Check hardware documentation on command set.
     * @param buffer defines buffer
     * @param len defines length of buffer
     * @return @c true when sending was successfully or @c false
     */
    bool cmd(uint8_t* buffer, uint32_t& len) const override;

    /**
     * Send buffer to device (data mode). Check hardware documentation on data set.
     * @param buffer defines buffer
     * @param len defines length of buffer
     * @return @c true when sending was successfully or @c false
     */
    bool data(uint8_t* buffer, uint32_t& len) const override;

    /**
     * Send single byte in command mode.
     * @param value defines the display command.
     * @return @c true when sending was successfully or @c false
     */
    bool cmd(uint8_t value) const override;

    /**
     * Send single byte in data mode.
     * @param value defines the data value.
     * @return @c true when sending was successfully or @c false
     */
    bool data(uint8_t value) const override;

private:
    /**
     * Internal hardware initialization routine (magic!)
     */
    void init() const;
};

}
}

#endif
