#include "font5x7.h"
#include <fontNum24_24.h>
#include <st7565r.h>

#include <cstring>

//#define EXCLUDE_LOGO


#define CMD_SET_COLUMN_ADDRESS_LSB(column) (0x00 | ((column)&0xF))
#define CMD_SET_COLUMN_ADDRESS_MSB(column) (0x10 | ((column)&0xF))
#define CMD_SET_MEMORY_ADDRESSING_MODE      0x20
#define CMD_SET_COLUMN_ADDRESS              0x21
#define CMD_SET_PAGE_ADDRESS                0x22
#define CMD_SET_DISPLAY_START_LINE(line)    (0x40+((line)&0x3F))
#define CMD_SET_CONTRAST_CONTROL_BANK0      0x81
#define CMD_SET_BRIGHTNESS                  0x82
#define CMD_SET_LUT                         0x91
#define CMD_SET_BANK_COLOR_1_16             0x92
#define CMD_SET_BANK_COLOR_17_32            0x93
#define CMD_SET_SEGMENT_REMAP(map)          (0xA0 | ((map)&0x1))
#define CMD_SET_ENTIRE_DISPLAY_ON           0xA4
#define CMD_SET_ENTIRE_DISPLAY_OFF          0xA5
#define CMD_SET_NORMAL_DISPLAY              0xA6
#define CMD_SET_INVERSE_DISPLAY             0xA7
#define CMD_SET_MULTIPLEX_RATIO             0xA8
#define CMD_SET_DIM_MODE                    0xAB
#define CMD_MASTER_CONFIGURATION            0xAD
#define CMD_SET_DIM_MODE_ON                 0xAC
#define CMD_SET_DISPLAY_OFF                 0xAE
#define CMD_SET_NORMAL_BRIGHTNESS_ON        0xAF
#define CMD_SET_PAGE_START_ADRESS(add)      (0xB0 | ((add)&0x7))
#define CMD_SET_COM_OUTPUT_DIR(dir)         (0xC0 | (((dir)&0x1)<< 3))
#define CMD_SET_DISPLAY_OFFSET              0xD3
#define CMD_SET_CLOCK_DIV_RATIO             0xD5
#define CMD_SET_OSC_FREQ                    0xD5
#define CMD_SET_AREA_COLOR_MODE             0xD8
#define CMD_SET_LOW_POWER_MODE              0xD8
#define CMD_SET_PRE_CHARGE_PERIOD           0xD9
#define CMD_SET_COM_PINS_HW_CONFIG          0xDA
#define CMD_SET_VCOM_DESELECT_LEVEL         0xD4

#define CMD_DEACTIVATE_SCROLL               0x2E
#define CMD_ACTIVATE_SCROLL                 0x2F

namespace Platform
{

namespace BSP
{

#ifndef EXCLUDE_LOGO

static const uint8_t logo[1024] =
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 240, 15, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 254, 7, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 224, 255, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 252,
        255, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 255, 255, 15, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 240, 255, 255, 7, 0, 224, 3, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 255, 255, 255, 15, 0, 224, 63, 0, 0, 0, 0, 0, 0, 0, 0, 224,
        255, 255, 255, 7, 0, 224, 255, 0, 0, 0, 0, 0, 0, 0, 0, 254, 255, 255,
        255, 15, 0, 224, 255, 15, 0, 0, 0, 0, 0, 0, 192, 255, 255, 255, 255, 7,
        0, 224, 255, 127, 0, 0, 0, 0, 0, 0, 252, 255, 255, 255, 255, 15, 0, 224,
        255, 255, 7, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 7, 0, 224, 255,
        255, 63, 0, 0, 0, 0, 0, 252, 255, 255, 255, 255, 7, 0, 224, 255, 255, 7,
        0, 0, 0, 0, 240, 224, 255, 255, 255, 255, 3, 0, 224, 255, 255, 224, 3,
        0, 0, 0, 208, 7, 254, 255, 255, 63, 0, 0, 224, 255, 15, 124, 3, 0, 0, 0,
        56, 124, 240, 255, 255, 7, 0, 0, 224, 255, 195, 7, 3, 0, 0, 0, 16, 224,
        1, 255, 127, 0, 0, 0, 224, 63, 240, 0, 3, 0, 0, 0, 56, 0, 62, 252, 15,
        0, 0, 0, 224, 7, 15, 0, 3, 0, 0, 0, 16, 0, 240, 192, 0, 0, 0, 0, 192,
        224, 3, 0, 3, 0, 0, 0, 56, 0, 0, 15, 0, 0, 0, 0, 0, 62, 0, 0, 3, 0, 0,
        0, 16, 0, 0, 124, 0, 0, 0, 0, 192, 7, 0, 0, 3, 0, 0, 0, 56, 0, 0, 192,
        0, 0, 0, 0, 124, 0, 0, 0, 3, 0, 0, 0, 16, 0, 0, 192, 0, 0, 0, 0, 15, 0,
        0, 0, 3, 0, 0, 0, 56, 0, 0, 192, 0, 0, 0, 240, 0, 0, 0, 0, 3, 0, 0, 0,
        16, 0, 0, 192, 0, 0, 0, 62, 0, 0, 0, 0, 3, 0, 0, 0, 56, 0, 0, 192, 0, 0,
        224, 3, 0, 0, 0, 0, 3, 0, 0, 0, 112, 0, 0, 192, 0, 0, 124, 0, 0, 0, 0,
        128, 3, 0, 0, 0, 192, 7, 0, 192, 0, 0, 12, 0, 0, 0, 0, 124, 0, 0, 0, 0,
        0, 30, 0, 192, 0, 0, 12, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 224, 3, 192, 0,
        0, 12, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 0, 15, 192, 0, 0, 12, 0, 0, 0,
        62, 0, 0, 0, 0, 0, 0, 0, 240, 192, 0, 0, 12, 0, 0, 224, 3, 0, 0, 0, 0,
        0, 0, 0, 192, 199, 0, 0, 12, 0, 0, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 252,
        0, 0, 12, 0, 192, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 224, 0, 0, 12, 0, 240,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 15, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 12, 224, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12,
        62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 204, 7, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, };
#endif  // #ifndef EXCLUDE_LOGO


ST7565R::ST7565R(Interface ifc, uint8_t port, uint8_t pin) :
        MonoChromeDisplay(ifc, port, pin),
        mode(2, 7,  DigitalInOut::Direction::OUTPUT),
        onoff(2, 1, DigitalInOut::Direction::OUTPUT)
{
}

ST7565R::~ST7565R()
{
    if (isFramebufferDynamic)
    {
        delete[] framebuffer;
    }
}

bool ST7565R::initialize(uint32_t w, uint32_t h, uint8_t fill, uint8_t *buffer)
{
    height = h;
    width = w;

    /* --Already allocated? */
    if (isFramebufferDynamic)
    {
        delete[] framebuffer;
    }

    /* --Allocate. */
    if (buffer == nullptr)
    {
        uint32_t size = (height * width) >> 3; /* --divide by 8. */
        framebuffer = new uint8_t[size];
        isFramebufferDynamic = true;
    }
    else
    {
        framebuffer = buffer;
        isFramebufferDynamic = false;
    }
    /* --Clear. */
    clrscr(fill);

    /* --Initialize device. */
    off();
    init();
    /* --Delay. */
    for (uint32_t i = 0; i < 0xffff; i++)
        ;
    on();
    return true;
}

void ST7565R::init() const
{
    /*
     * Recommended Initial code according to manufacturer
     */
    cmd(CMD_SET_DISPLAY_START_LINE(0));            //(display start set)
    cmd(0xA1);                                     // ADC select / reverse!
    cmd(0xC0);                                     // Common output mode direction, normal direction
    cmd(0xA6);                                     // Display all points ON
    cmd(0xA2);                                     // LCD Bias set, 1/9 bias
    cmd(0x2F);                                     // Power Control set, all ON
    cmd(0xF8);
    cmd(0x00);
    cmd(0x27);
    cmd(0x81);
    cmd(0x16);
    cmd(0xAC);
    cmd(0x00);
    cmd(0xAF);
}

void ST7565R::on() const
{
    onoff.set();
}

void ST7565R::off() const
{
    onoff.clear();
}

bool ST7565R::cmd(uint8_t *buffer, uint32_t &len) const
{
    /* --Switch to command mode. */
    commandMode();
    return write(buffer, len);
}

bool ST7565R::data(uint8_t *buffer, uint32_t &len) const
{
    /* --Switch to data mode. */
    dataMode();
    return write(buffer, len);
}

bool ST7565R::cmd(uint8_t value) const
{
    uint32_t len = 1;
    return cmd(&value, len);
}

bool ST7565R::data(uint8_t value) const
{
    uint32_t len = 1;
    return data(&value, len);
}

void ST7565R::commandMode() const
{
    mode.clear();
}

void ST7565R::dataMode() const
{
    mode.set();
}

bool ST7565R::flush() const
{

    for (uint8_t page = 0; page < 8; page++)
    {
        cmd(CMD_SET_PAGE_START_ADRESS(page));
        cmd(CMD_SET_COLUMN_ADDRESS_LSB(2));
        cmd(CMD_SET_COLUMN_ADDRESS_MSB(1));

        uint8_t *start = framebuffer + page * width;
        uint32_t len = width;
        data(start, len);
    }

    return true;
}


void ST7565R::setPosition(uint8_t screen_row, uint8_t screen_column)
{
    cur_column = screen_column;
    cur_row    = screen_row % 8;
}



void ST7565R::showDemoPicture()
{
    clrscr();
#ifndef EXCLUDE_LOGO
    bitmap(logo, width, height, PixelStorage::BitPerPixel);
#else
     printf("NO LOGO\r\n");
#endif
    flush();
}

void ST7565R::showDemoText()
{
    clrscr();
    print("MICHAEL UELSCHEN");
    println("HOCHSCHULE OSNA\n\n");
    newline(2);
    println("(C) June 2016");
    flush();
}

void ST7565R::printBigNum(uint8_t num)
{
    uint8_t digit = 0;

    size_t  sizeByte = sizeof(uint8_t) * 8;
    uint8_t screenRow    = 0;
    uint8_t screenColumn = 1;
    uint8_t divider = 100;

    // font specific:

    // fontNum24_24 : first index:  index of character
    // fontNum24_24 : second index: index of character  row
    // fontNum24_24 : third index:  index of character  column byte in row
    uint8_t fontWidth  = sizeof(fontNum24_24[0][0]) * sizeByte;
    uint8_t fontHeight = sizeof(fontNum24_24[0]) /       // size of character
                         sizeof(fontNum24_24[0][0]);     // size of row

    // Framebuffer offset, needed for every char
    uint32_t fbOffset = width                                   // skip one line
                      + screenRow * (fontHeight >> 3) * width;  // offset row


    for (uint8_t i = 0; i < 3; ++i, ++screenColumn)  // loop over three digits
    {
        digit = num/divider;
        num %= divider;
        divider /= 10;
        for (uint8_t xpos = 0; xpos < fontWidth / sizeByte; ++xpos)
        {
            unsigned int fbxOffset = screenColumn * fontWidth       // offset column
                                   + xpos * sizeByte;
            for (uint8_t ypos = 0; ypos < fontHeight; ++ypos)
            {
                uint8_t fontByte = fontNum24_24[digit][ypos][xpos];
                if (fontByte)   // assume we have a lot if 0 Bytes in font
                {
                    uint32_t fbyOffset = (ypos >> 3) * width;
                    uint8_t bit = ypos % 8;
                    for (uint8_t j = 0; j < sizeByte; ++j)
                    {
                        if (fontByte & (0x1 << (sizeByte - 1 - j)))
                        {
                            uint32_t fbByte = fbOffset
                                            + fbxOffset
                                            + fbyOffset
                                            + j;
                            framebuffer[fbByte] |= (0x1 << bit);
                        }
                    }
                }
            }
        }
    }
}

}

} // namespace Platform

