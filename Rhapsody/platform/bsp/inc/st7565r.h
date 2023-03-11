#ifndef ST7865R_H
#define ST7865R_H


#include "sspdevice.h"
#include "MonoChromeDisplay.h"

namespace Platform {
namespace BSP {


/**
  * \brief
 * SSD1306 can control 96x64 pixel output.
 * The default 5x7 font allows 16 columns and 8 rows.
 *
 */
class ST7565R : public MonoChromeDisplay<SSPDevice> {
public:

	 /*! @brief Standard constructor. */
	ST7565R(Interface ifc, uint8_t port, uint8_t pin);
    ~ST7565R();


    /**
     * Print 3 digit number in center of display. 24x24 font is used..
     * @param num is the number to show
     */
    void printBigNum(uint8_t num);

    /**
     * Just demo picture.
     */
    void showDemoPicture();

    /**
     * Just demo text.
     */
    void showDemoText();



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


    /**
     *  Changes cursor position. Print next symbol at (row,column) (only 7Bit ASCII).
     * @param screen_row
     * @param screen_column
     * @returns none
     */
    void setPosition(uint8_t screen_row = 1, uint8_t screen_column = 1);

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
    /**
      * Switch display to command mode.
      */
     void commandMode() const;

     /**
      * Switch display to data mode.
      */
     void dataMode() const;

    DigitalInOut mode;      /**< Pin Command/Data. */
    DigitalInOut onoff;     /**< Pin on/off Display. */

};

}
}

#endif
