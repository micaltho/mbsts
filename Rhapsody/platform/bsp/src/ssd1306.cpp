#include <ssd1306.h>
#include <cstring>
#include <algorithm>



//#define EXCLUDE_LOGO


// Command definition:
#define SSD1306_SETCONTRAST          0x81
#define SSD1306_DISPLAYALLON_RESUME  0xA4
#define SSD1306_DISPLAYALLON         0xA5
#define SSD1306_NORMALDISPLAY        0xA6
#define SSD1306_INVERTDISPLAY        0xA7
#define SSD1306_DISPLAYOFF           0xAE
#define SSD1306_DISPLAYON            0xAF
#define SSD1306_SETDISPLAYOFFSET     0xD3
#define SSD1306_SETCOMPINS           0xDA
#define SSD1306_SETVCOMDETECT        0xDB
#define SSD1306_SETDISPLAYCLOCKDIV   0xD5
#define SSD1306_SETPRECHARGE         0xD9
#define SSD1306_SETMULTIPLEX         0xA8
#define SSD1306_SETLOWCOLUMN         0x00
#define SSD1306_SETHIGHCOLUMN        0x10
#define SSD1306_SETSTARTLINE         0x40
#define SSD1306_MEMORYMODE           0x20
#define SSD1306_COLUMNADDR           0x21
#define SSD1306_PAGEADDR             0x22
#define SSD1306_COMSCANINC           0xC0
#define SSD1306_COMSCANDEC           0xC8
#define SSD1306_SEGREMAP             0xA0
#define SSD1306_CHARGEPUMP           0x8D
#define SSD1306_EXTERNALVCC          0x1
#define SSD1306_SWITCHCAPVCC         0x2


#define CMD_SET_COLUMN_ADDRESS_LSB(column) (0x00 | ((column)&0xF))
#define CMD_SET_COLUMN_ADDRESS_MSB(column) (0x10 | ((column)&0xF))
//#define CMD_SET_MEMORY_ADDRESSING_MODE      0x20
//#define CMD_SET_COLUMN_ADDRESS              0x21
//#define CMD_SET_PAGE_ADDRESS                0x22
//#define CMD_SET_DISPLAY_START_LINE(line)    (0x40+((line)&0x3F))
//#define CMD_SET_CONTRAST_CONTROL_BANK0      0x81
//#define CMD_SET_BRIGHTNESS                  0x82
//#define CMD_SET_LUT                         0x91
//#define CMD_SET_BANK_COLOR_1_16             0x92
//#define CMD_SET_BANK_COLOR_17_32            0x93
//#define CMD_SET_SEGMENT_REMAP(map)          (0xA0 | ((map)&0x1))
//#define CMD_SET_ENTIRE_DISPLAY_ON           0xA4
//#define CMD_SET_ENTIRE_DISPLAY_OFF          0xA5
//#define CMD_SET_NORMAL_DISPLAY              0xA6
//#define CMD_SET_INVERSE_DISPLAY             0xA7
//#define CMD_SET_MULTIPLEX_RATIO             0xA8
//#define CMD_SET_DIM_MODE                    0xAB
//#define CMD_MASTER_CONFIGURATION            0xAD
//#define CMD_SET_DIM_MODE_ON                 0xAC
//#define CMD_SET_DISPLAY_OFF                 0xAE
//#define CMD_SET_NORMAL_BRIGHTNESS_ON        0xAF
#define CMD_SET_PAGE_START_ADRESS(add)      (0xB0 | ((add)&0x7))
//#define CMD_SET_COM_OUTPUT_DIR(dir)         (0xC0 | (((dir)&0x1)<< 3))
//#define CMD_SET_DISPLAY_OFFSET              0xD3
//#define CMD_SET_CLOCK_DIV_RATIO             0xD5
//#define CMD_SET_OSC_FREQ                    0xD5
//#define CMD_SET_AREA_COLOR_MODE             0xD8
//#define CMD_SET_LOW_POWER_MODE              0xD8
//#define CMD_SET_PRE_CHARGE_PERIOD           0xD9
//#define CMD_SET_COM_PINS_HW_CONFIG          0xDA
//#define CMD_SET_VCOM_DESELECT_LEVEL         0xD4
//
//#define CMD_DEACTIVATE_SCROLL               0x2E
//#define CMD_ACTIVATE_SCROLL                 0x2F




namespace Platform {

namespace BSP {

#ifndef EXCLUDE_LOGO

static const uint8_t logo[1024] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,240,15,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,254,7,0,0,0,0,0,0,0,0,
    0,0,0,0,0,224,255,15,0,0,0,0,0,0,0,0,
    0,0,0,0,0,252,255,7,0,0,0,0,0,0,0,0,
    0,0,0,0,192,255,255,15,0,0,0,0,0,0,0,0,
    0,0,0,0,240,255,255,7,0,224,3,0,0,0,0,0,
    0,0,0,0,255,255,255,15,0,224,63,0,0,0,0,0,
    0,0,0,224,255,255,255,7,0,224,255,0,0,0,0,0,
    0,0,0,254,255,255,255,15,0,224,255,15,0,0,0,0,
    0,0,192,255,255,255,255,7,0,224,255,127,0,0,0,0,
    0,0,252,255,255,255,255,15,0,224,255,255,7,0,0,0,
    0,0,255,255,255,255,255,7,0,224,255,255,63,0,0,0,
    0,0,252,255,255,255,255,7,0,224,255,255,7,0,0,0,
    0,240,224,255,255,255,255,3,0,224,255,255,224,3,0,0,
    0,208,7,254,255,255,63,0,0,224,255,15,124,3,0,0,
    0,56,124,240,255,255,7,0,0,224,255,195,7,3,0,0,
    0,16,224,1,255,127,0,0,0,224,63,240,0,3,0,0,
    0,56,0,62,252,15,0,0,0,224,7,15,0,3,0,0,
    0,16,0,240,192,0,0,0,0,192,224,3,0,3,0,0,
    0,56,0,0,15,0,0,0,0,0,62,0,0,3,0,0,
    0,16,0,0,124,0,0,0,0,192,7,0,0,3,0,0,
    0,56,0,0,192,0,0,0,0,124,0,0,0,3,0,0,
    0,16,0,0,192,0,0,0,0,15,0,0,0,3,0,0,
    0,56,0,0,192,0,0,0,240,0,0,0,0,3,0,0,
    0,16,0,0,192,0,0,0,62,0,0,0,0,3,0,0,
    0,56,0,0,192,0,0,224,3,0,0,0,0,3,0,0,
    0,112,0,0,192,0,0,124,0,0,0,0,128,3,0,0,
    0,192,7,0,192,0,0,12,0,0,0,0,124,0,0,0,
    0,0,30,0,192,0,0,12,0,0,0,0,15,0,0,0,
    0,0,224,3,192,0,0,12,0,0,0,240,0,0,0,0,
    0,0,0,15,192,0,0,12,0,0,0,62,0,0,0,0,
    0,0,0,240,192,0,0,12,0,0,224,3,0,0,0,0,
    0,0,0,192,199,0,0,12,0,0,124,0,0,0,0,0,
    0,0,0,0,252,0,0,12,0,192,7,0,0,0,0,0,
    0,0,0,0,224,0,0,12,0,240,0,0,0,0,0,0,
    0,0,0,0,0,0,0,12,0,15,0,0,0,0,0,0,
    0,0,0,0,0,0,0,12,224,3,0,0,0,0,0,0,
    0,0,0,0,0,0,0,12,62,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,204,7,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,124,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,12,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

#endif  // #ifndef EXCLUDE_LOGO

SSD1306::SSD1306(Interface ifc):MonoChromeDisplay(ifc,0x3c)
{ }

SSD1306::~SSD1306() {
    if (isFramebufferDynamic && framebuffer) --framebuffer;
    delete [] framebuffer;
}


void SSD1306::init() const {
    /*
     * Recommended Initial code according to manufacturer
     */
    // Init sequence for 128x64 OLED module
    cmd(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    cmd(0x80);                 // the suggested ratio 0x80

    cmd(SSD1306_SETMULTIPLEX);                  // 0xA8
    cmd(0x3F);

    cmd(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    cmd(0x0);                                   // no offset

    cmd(SSD1306_SETSTARTLINE);// | 0x0);        // line #0

    cmd(SSD1306_CHARGEPUMP);                    // 0x8D
    cmd(0x14);  // using internal VCC

    cmd(SSD1306_MEMORYMODE);                    // 0x20
    cmd(0x00);          // 0x00 horizontal addressing

    cmd(SSD1306_SEGREMAP | 0x1); // rotate screen 180

    cmd(SSD1306_COMSCANDEC); // rotate screen 180

    cmd(SSD1306_SETCOMPINS);                    // 0xDA
    cmd(0x12);

    cmd(SSD1306_SETCONTRAST);                   // 0x81
    cmd(0xCF);

    cmd(SSD1306_SETPRECHARGE);                  // 0xd9
    cmd(0xF1);

    cmd(SSD1306_SETVCOMDETECT);                 // 0xDB
    cmd(0x40);

    cmd(SSD1306_DISPLAYALLON_RESUME);           // 0xA4

    cmd(SSD1306_NORMALDISPLAY);                 // 0xA6
}


void SSD1306::showDemoPicture() {
    clrscr();
#ifndef EXCLUDE_LOGO
    bitmap(logo,width,height, PixelStorage::BitPerPixel);
#else
    printf("NO LOGO\r\n");
#endif
    flush();
}



void SSD1306::on() const {
    cmd(SSD1306_DISPLAYON);
}

void SSD1306::off() const {
    cmd(SSD1306_DISPLAYOFF);
}

bool SSD1306::cmd(uint8_t* buffer, uint32_t& len) const {
    /* --Switch to command mode. */
    return write(buffer,len);
}

bool SSD1306::data(uint8_t* buffer, uint32_t& len) const {
    /* --Switch to data mode. */
   // dataMode();
    ++len;
    buffer[0] = 1<<6;  // set Data Mode
    return write(buffer,len);
}

bool SSD1306::cmd(uint8_t value) const {

    uint32_t len=2;
    uint8_t buffer[4];
    buffer[0] = 0; // Co = 0; Command Mode
    buffer[1] = value;
    return cmd(buffer,len);
}

bool SSD1306::data(uint8_t value) const {
    uint32_t len=1;
    uint8_t buffer[2];
    buffer[1] = value;
    return data(buffer,len);
}

bool SSD1306::initialize(uint32_t w, uint32_t h, uint8_t fill, uint8_t* buffer) {
    height=h;
    width=w;

    /* --Already allocated? */
    if (isFramebufferDynamic)
    {
       if (framebuffer) --framebuffer;
       delete [] framebuffer;
    }

    /* --Allocate. */
    if (buffer == nullptr)
    {
       uint32_t size = (height * width) >> 3; /* --divide by 8. */
       framebuffer = new uint8_t[size + 1];  // one byte for I2C Control byte
       isFramebufferDynamic = true;
    }
    else
    {
       framebuffer = buffer;
       isFramebufferDynamic = false;
    }
    ++framebuffer;   // skip I2C Control byte in buffer
    /* --Clear. */
    clrscr(fill);

    /* --Initialize device. */
    off();
    init();
    /* --Delay. */
    for (uint32_t i = 0; i < 0xffff; i++);
    on();
    return true;
}



bool SSD1306::flush() const {

    for(uint8_t page=0;page<8;page++) {
          cmd(CMD_SET_PAGE_START_ADRESS(page));
          cmd(CMD_SET_COLUMN_ADDRESS_LSB(0));
          cmd(CMD_SET_COLUMN_ADDRESS_MSB(0));

          uint8_t* start=framebuffer + page*width -1;  // -1 for I2C control byte
          uint32_t len=width;
          uint8_t temp = *start;   // first byte in buffer is overwritten in I2C transfer
          data(start,len);
          *start = temp;           // restore byte
    }

    return true;
}



} // namespace Platform

}
