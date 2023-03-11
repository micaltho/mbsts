/*
 * MonoChromeDisplay<U>.h
 *
 *  Created on: 28.01.2021
 *      Author: Wuebbelmann
 */

#ifndef PLATFORM_BSP_INC_MONOCHROMEDISPLAY_H_
#define PLATFORM_BSP_INC_MONOCHROMEDISPLAY_H_
#include "font5x7.h"
#include <cstring>
#include <string>

namespace Platform {
namespace BSP {

/*! @brief Base Class to output to monochromatic Display (very simplistic!).
 *
 *  This class defines the interface to the  display.
 *  It has only limited functionality.
 *
 *  The Display implements 2 coordinate systems:
 *    - (x,y) based for pixel-based output
 *    - (row,column) based for textual output
 *
 *  In both cases the origin (0,0) is located at the upper left corner.
 *
 * @code
 *  pixel coordinate system
 *  0   ---> x                 width-1
 *  0 +----------------------------+
 *    |                            |
 *  | |                            |
 *  | |     (x,y)                  |
 *  y |                            |
 *    |                            |
 *    +----------------------------+ height-1
 *
 *  text coordinate system
 *    0   ---> column            columns-1
 *  0 +----------------------------+
 *    |                            |
 *  r |                            |
 *  o |     (row,column)           |
 *  w |                            |
 *    |                            |
 *    +----------------------------+ rows-1
 * @endcode
 *
 * Display can control width x height pixel output, depending on the realization.
 * The default 5x7 font allows 20 columns and 8 rows.
 *
 *
 *   A common interface is provided, all derived classes must implement some pure virtual methods.\n *
 *
 *  \tparam U Class of HW Interface, e.g I2CDevice or SSPDevice
*/


template<typename U>
class MonoChromeDisplay : public U
{
public:

    /**
     * Encoding of data in a bitmap
     */
    enum class PixelStorage
    {
        BytePerPixel = 0,     //!< a pixel uses one byte of memory
        BitPerPixel,          //!< a pixel uses one bit of memory
        RLEencoding           //!< Bit pixel plus run length encoding
    };

    /** \brief Does length run encoding according to ATARI STAD \
     *         (https://www.fileformat.info/format/atari/egff.htm) only horizontal packing is done
     */

    /** \brief Header structure for RLE encoding.
     *  RLE File has the following structure:
     *     Byte1      Byte2      Byte3     Byte4
     *  ---------------------------------------------
     *  |          |          |          |          |
     *  | Magic[0] | Magic[1] | Magic[2] | Magic[3] |
     *  |          |          |          |          |
     *  ---------------------------------------------
     *  |          |          |          |          |
     *  | IdByte   | PackByte | SpecialB | width[0] |
     *  |          |          |          |          |
     *  ---------------------------------------------
     *  |          |          |          |          |
     *  | width[1} | height[0]| height[1]| data[0]  |
     *  |          |          |          |          |
     *  ---------------------------------------------
     *  |          |          |          |          |
     *  | data[1]  | data[2]  | ...      | data[N]  |
     *  |          |          |          |          |
     *  ---------------------------------------------
     *  with: Magic[0] ... Magic[3] = 'jW21'
     *
     * RLE decoding is according this pseudo code:
     * \code
     *  Read a byte
     *      If the byte is the IdByte value
     *            Read a byte (the RunCount)
     *            Repeat the PackByte value RunCount + 1 times else
     *      If the byte is the SpecialByte value
     *            Read a byte (the RunValue)
     *            Read a byte (the RunCount)
     *            Repeat the RunValue RunCount +1 times
     *      else
     *            Use the byte value literally.
     * \endcode
     */
    struct RLEHeader
    {
       char          Packed[4];    ///< Magic number, must be "jW21"
       std::uint8_t  IdByte;       ///<  RLE ID value of a 'PackByte' run
       std::uint8_t  PackByte;     ///<  The value of a 'PackByte' run
       std::uint8_t  SpecialByte;  ///<  RLE ID value of a non-'PackByte' run
       std::uint8_t  width[2];     ///<  width of image,  LSB first
       std::uint8_t  height[2];    ///<  height of image, LSB first
    };

    /**
    * Constructor
    * \param [in] ifc used Interface of \ref I2CDevice or \ref SSPDevice
    * \param [in] addr_port addr of I2CDevice address of EEPROM device or\n
    *        SSEL port of SSPDevice\n
    *        depending on template parameter U
    * \param [in] dc_pin dont care if I2CDevice is used or\n
    *        SSEL pin of SSPDevice\n
    *        depending on template parameter U
    */
    MonoChromeDisplay(typename U::Interface ifc,
                     uint8_t addr_port,
                     uint8_t dc_pin = 0) :  U(ifc, addr_port, dc_pin)
    {};


    /** @name driver specific
     */
   ///@{


    /**
     * Initialize the display.
     * @param w defines the width of the display
     * @param h defines the height
     * @param fill defines initial fill pattern
     * @param [in] buffer defines an memory region where framebuffer is stored.
     *  If \a buffer equals @c nullptr, the framebuffer is allocated dynamically.
     *
     * @return @c true if initialization succeeded or @c false
     */
    virtual bool initialize(uint32_t w =96, uint32_t h =64, uint8_t fill =0x00, uint8_t* buffer = nullptr) = 0;


    /**
     * Enable display.
     */
    virtual void on() const = 0;

    /**
     * Disable display.
     */
    virtual void off() const = 0;

    /**
      * Flush (transfer internal frame buffer to display).
      * @return @c true if flushed succeeded or @c false
      */
    virtual bool flush() const = 0;

protected:
     /**
       * Send buffer to device (command mode). Check hardware documentation on command set.
       * @param buffer defines buffer
       * @param len defines length of buffer
       * @return @c true when sending was successfully or @c false
       */
    virtual bool cmd(uint8_t* buffer, uint32_t& len) const = 0;

    /**
     * Send buffer to device (data mode). Check hardware documentation on data set.
     * @param buffer defines buffer
     * @param len defines length of buffer
     * @return @c true when sending was successfully or @c false
     */
    virtual bool data(uint8_t* buffer, uint32_t& len) const = 0;


    /**
     * Send single byte in command mode.
     * @param value defines the display command.
     * @return @c true when sending was successfully or @c false
     */
    virtual bool cmd(uint8_t value) const = 0;


    /**
     * Send single byte in data mode.
     * @param value defines the data value.
     * @return @c true when sending was successfully or @c false
     */
    virtual bool data(uint8_t value) const = 0;
      ///@}
public:

     /** @name Graphical output
      */
     ///@{

     /**
      * Clear the screen.
      * @param pattern defines the fill pattern
      */
     void clrscr(uint8_t pattern=0x00);


     /**
      * Set pixel at (x,y) to value, just internal framebuffer.
      * \warning it is not tested whether pixel is in framebuffer! A write to illegal memory is possible.\n
      * The call is faster then the save \ref pixelLimit
      * @param x defines x position
      * @param y defines y position
      * @param value specifies to set or to unset pixel
      */
     void pixel(uint32_t x, uint32_t y, bool value =true) const;

     /**
      * Set pixel at (x,y) to value, just internal framebuffer. Check for boundary!
      * @param x defines x position
      * @param y defines y position
      * @param value specifies to set or to unset pixel
      */
     void pixelLimit(uint32_t x, uint32_t y, bool value =true) const;


     /**
      * Draw line from (x0, y0) to (x1, y1) implements Bresenham algorithm
      * @param x0 defines x coordinate start point
      * @param y0 defines y coordinate start point
      * @param x1 defines x coordinate end point
      * @param y1 defines y coordinate end point
      */
     void line(int32_t x0, int32_t y0, int32_t x1, int32_t y1) const;

     /**
      * Draw circle from (x0, y0) with radius, implements Bresenham algorithm
      * @param x0 defines x coordinate of center
      * @param y0 defines y coordinate of center
      * @param radius defines radius of circle
      */
      void circle(int32_t x0, int32_t y0, uint32_t radius) const;

      /**
       * Draw rectangle from (x0, y0) (upper left point) with given width and height)
       * @param x0 defines x coordinate start point
       * @param y0 defines y coordinate start point
       * @param width defines width of rectangle
       * @param height defines height of rectangle
       */
      void rectangle(int32_t x0, int32_t y0, uint32_t width, uint32_t height) const;

      /**
       * Draw square from (x0, y0) (upper left point) with given width)
       * @param x0 defines x coordinate start point
       * @param y0 defines y coordinate start point
       * @param width defines width of rectangle
       */
      void square(int32_t x0, int32_t y0, uint32_t width) const {rectangle(x0,y0,width,width);};


      /**
      * Set bitmap at position (x,y).
      * @param picture defines pointer to bitmap buffer.
      * @param pic_width defines width of bitmap
      * @param pic_height defines height of bitmap
      * @param pixStorage defines how a pixel is stored in bitmap buffer
      * @param x defines x position
      * @param y defines y position
      */
     void bitmap(const uint8_t* picture,
                 uint32_t pic_width,
                 uint32_t pic_height,
                 PixelStorage  pixStorage = PixelStorage::BytePerPixel,
                 uint8_t x =0,
                 uint8_t y =0);

     ///@}


     /** @name Textual output
      */
     ///@{

     /**
      * Put symbol at (row,column) (only 7Bit ASCII). Does not change cursor position.
      * @param[in] screen_row
      * @param[in] screen_column
      * @param[in] symbol
      * @param[in] invert if true, symbol is displayed inverted
      */
     void ascii(uint8_t screen_row, uint8_t screen_column, uint8_t symbol, bool invert = false);

     /**
      * Add one or more newlines to the text.
      * @param n
      */
     void newline(uint8_t n=1);

     /**
      * Set cursor position to 0.
      *
      */
     void home() {cur_row = cur_column = 0;}

     /**
      * Print string (\n will force a line break). Will change cursor position.
      * @param src is the string to show
      * @param [in] invert if true, symbol is displayed inverted
      */
     void print(const std::string& src, bool invert = false)
             {print(src.c_str(), invert);}

     /**
      * Print string (\n will force a line break). Will change cursor position.
      * @param src is the string to show
      * @param [in] invert if true, symbol is displayed inverted
      */
     void print(const char* src, bool invert = false);

     /**
      * Print string (\n will force a line break) and terminates current line. Will change cursor position.
      * @param src is the string to show
      * @param [in] invert if true, symbol is displayed inverted
      */
     void println(const std::string& src, bool invert = false)
             {println(src.c_str(), invert);}

     /**
      * Print string (\n will force a line break) and terminates current line. Will change cursor position.
      * @param src is the string to show
      * @param [in] invert if true, symbol is displayed inverted
      */
     void println(const char * src, bool invert = false);

     /**
      * Just demo text.
      */
     void showDemoText();
     ///@}

     /**
      * getter for \ref height
      *
      * @returns height in pixel
      */
     uint32_t getHeight() const {return height;}
     /**
      * getter for \ref width
      *
      * @returns width in pixel
      */
     uint32_t getWidth() const  {return width;}

protected:
    uint32_t height      = 0;       /**< height of internal frame buffer. */
    uint32_t width       = 0;       /**< width of internal frame buffer. */
    uint8_t* framebuffer = nullptr; /**< internal frame buffer. */

    uint8_t cur_row    = 0;         /**< current row position required for textual output. */
    uint8_t cur_column = 0;         /**< current column position required for textual output. */

    bool    isFramebufferDynamic = false;  /**< is framebuffer allocated on heap? */

};



template<typename U>
void MonoChromeDisplay<U>::clrscr(uint8_t pattern) {
    uint32_t size=(height*width)>>3;
    memset(framebuffer,pattern,size);
    /* --Reset cursor position. */
    cur_row=cur_column=0;
}




template<typename U>
void MonoChromeDisplay<U>::pixel(uint32_t x, uint32_t y, bool value) const{
    uint32_t byte=(y>>3)*width+x;    /* --Byte. */
    uint32_t bit=y%8;

    uint8_t n=framebuffer[byte];

    if (value) {
        /* --Bit setzen. */
        n=n|(1<<bit);
    }
    else {
        /* --Bit löschen. */
        n=n&~(1<<bit);

    }

    framebuffer[byte]=n;

}

template<typename U>
void MonoChromeDisplay<U>::pixelLimit(uint32_t x, uint32_t y, bool value) const
{
    if(x < width && y < height)  pixel(x,y, value);
}


template<typename U>
void MonoChromeDisplay<U>::line(int32_t x0, int32_t y0, int32_t x1, int32_t y1) const {
      int32_t dx = x0<x1 ? x1-x0 : x0 - x1,  // abs(x1-x0)
              sx = x0<x1 ? 1 : -1;
      int32_t dy = y0>y1 ? y1-y0 : y0 - y1,  //-abs(y1-y0),
              sy = y0<y1 ? 1 : -1;
      int32_t err = dx+dy, e2; /* error value e_xy */

      while(1){
        pixelLimit(x0,y0);
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
      }
}


template<typename U>
void MonoChromeDisplay<U>::circle(int32_t x0, int32_t y0, uint32_t radius) const
{
    int32_t f = 1 - radius;
    int32_t ddF_x = 0;
    int32_t ddF_y = -2 * radius;
    int32_t x = 0;
    int32_t y = radius;

    pixelLimit(x0, y0 + radius);
    pixelLimit(x0, y0 - radius);
    pixelLimit(x0 + radius, y0);
    pixelLimit(x0 - radius, y0);

    while(x < y)
    {
      if(f >= 0)
      {
        y--;
        ddF_y += 2;
        f += ddF_y;
      }
      x++;
      ddF_x += 2;
      f += ddF_x + 1;

      pixelLimit(x0 + x, y0 + y);
      pixelLimit(x0 - x, y0 + y);
      pixelLimit(x0 + x, y0 - y);
      pixelLimit(x0 - x, y0 - y);
      pixelLimit(x0 + y, y0 + x);
      pixelLimit(x0 - y, y0 + x);
      pixelLimit(x0 + y, y0 - x);
      pixelLimit(x0 - y, y0 - x);
    }
}

template<typename U>
void MonoChromeDisplay<U>::rectangle(int32_t x0, int32_t y0, uint32_t width, uint32_t height) const
{

      line(x0, y0, x0+width, y0);
      line(x0+width, y0, x0+width, y0+height);
      line(x0+width, y0+height, x0, y0+height);
      line(x0, y0+height, x0, y0);
}

template<typename U>
void MonoChromeDisplay<U>::ascii(uint8_t screen_row, uint8_t screen_column, uint8_t symbol, bool invert)
{
    /* --Check if row in [0..7] and column in [0..15]. */
    if (screen_row < 8 && screen_column < (width/6))
    {
        /* --Check if font has symbol. */
        if (symbol < ' ' || symbol > 0x7f)
        {
            /* --Unknown character. */
            uint8_t unknown = 0xaa;

            for (uint32_t i = 1; i < 5; i++)
            {
                framebuffer[i + screen_row * width + screen_column * 6] =
                        unknown;
                unknown = ~unknown;
            }
        }
        /* --Set font bitmap. */
        else
        {
            /* --Rotate the symbol. */
            for (uint8_t i = 7; i > 1; i--)
            {
                uint8_t rotated = 0x00;
                if (invert) rotated = 0xFF;
                /* --Inner loop on the rows. */
                for (uint8_t j = 0; j < 8; j++)
                    /* --Test bit. */
                    if (font5x7[symbol - ' '][j] & (1 << i))
                    {
                        if(invert)
                            rotated &= ~(1 << j);
                        else
                            rotated |= (1 << j);
                    }
                /* --Write to framebuffer. */
                framebuffer[7 - i + screen_row * width + screen_column * 6] =
                        rotated;
            }
        }
    }
}


template<typename U>
void MonoChromeDisplay<U>::showDemoText() {
    clrscr();
    print("TI");
    println("HOCHSCHULE OSNA\n\n");
    newline(2);
    println("(C) Jan 2021");
    flush();
}



template<typename U>
void MonoChromeDisplay<U>::print(const char* src, bool invert)
{
    size_t i = 0;
    char c;
    while ((c = src[i++]) != '\0')
    {
        /* --Check for \n. */
        if (c == '\n')
            newline();
        else
        {
            /* --Output ascii character. */
            ascii(cur_row, cur_column, c, invert);
            /* --Update cursor position. */
            cur_column++;
            if (cur_column > width/6-1)
                newline();
        }
    }
}

template<typename U>
void MonoChromeDisplay<U>::newline(uint8_t n) {
    cur_column=0;
    cur_row=(cur_row+n)%8;
}



template<typename U>
void MonoChromeDisplay<U>::println(const char* src,  bool invert) {
    print(src, invert);
    newline();
}






template<typename U>
void MonoChromeDisplay<U>::bitmap(const uint8_t* picture,
                     uint32_t pic_width,
                     uint32_t pic_height,
                     PixelStorage  pixStorage,
                     uint8_t x,
                     uint8_t y) {
    uint8_t maxx=std::min(width,x+pic_width);
    uint8_t maxy=std::min(height,y+pic_height);
    /* --Copy bitmap data to internal framebuffer. */
    if (PixelStorage::BitPerPixel ==  pixStorage)
    {
        maxx >>= 3; // we have 8 pixel in one byte.
        uint32_t dwidth = width >> 3;
        for(uint8_t i=0;i<maxx;i++)
            for(uint8_t j=0;j<maxy;j++)
            {
                uint8_t octet = picture[j*dwidth +i];
                for(uint32_t bit = 0; bit < 8; ++bit)
                   pixel(x+(i<<3)+bit,y+j,(octet >> bit) & 0x1);
            }
    }
    else if(PixelStorage::BytePerPixel == pixStorage)
    {
        // one pixel per byte
        for(uint8_t i=0;i<maxx;i++)
            for(uint8_t j=0;j<maxy;j++)
                pixel(x+i,y+j,picture[j*width+i]);
    }
    else if(PixelStorage::RLEencoding == pixStorage)
    {
        // one pixel per bit and RLE
        const RLEHeader* header = reinterpret_cast<const RLEHeader*>(picture);
        uint8_t idByte      = header->IdByte;      // picture[4];
        uint8_t packedByte  = header->PackByte;    //picture[5];
        uint8_t specialByte = header->SpecialByte; //picture[6];

        maxx >>= 3;
        size_t maxBytes = maxx*maxy;
        size_t picIndex = sizeof(RLEHeader);   // offset of picture data.
        size_t mapIndex = 0;
        while (mapIndex < maxBytes)
        {
            // read bytes
            uint8_t octet = picture[picIndex++];
            uint8_t runCount = 0;
            if(octet == idByte)
            {
                octet = packedByte;
                runCount = picture[picIndex++];
            }
            else if(octet == specialByte)
            {
                octet = picture[picIndex++];
                runCount  = picture[picIndex++];
            }
            for(uint32_t j = 0; j <= static_cast<uint32_t>(runCount); ++j)
            {
                uint8_t xoff = mapIndex % maxx;
                uint8_t yoff = mapIndex / maxx;
                for(uint32_t bit = 0; bit < 8; ++bit)
                   pixel(x+(xoff<<3)+bit,y+yoff,(octet >> bit) & 0x1);
                mapIndex++;
            }
        }
    }
}

}  // namspace BSP
}  // namesapce Platform

#endif /* PLATFORM_BSP_INC_MONOCHROMEDISPLAY_H_ */
