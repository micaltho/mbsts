/*
 * MC24LC08.cpp
 *
 *  Created on: 08.07.2015
 *      Author: Wuebbelmann
 */

/// \file

#include <mc24lc08.h>
#include <cstring>     // for memcopy

namespace Platform {
namespace BSP {
// Device Identifier: 1010
// Device Address:    A2 B1 B0 with: A2=0 (Wired) B1, B0=Block Address
// LSB:  R/W

   static constexpr uint8_t     _24LC08_BASEADDR = 0x50;   ///< I2C address of EEPROM
   static constexpr std::size_t MC24LC08_SIZE    = 1024;   ///< EPPROM contains 1024 Bytes capacity
   static constexpr std::size_t MC24LC08_BLOCK   =  256;   ///< EPPROM block size
   static constexpr std::size_t MC24LC08_PAGE    =   16;   ///< EPPROM pagesize, write and readable in one access

   MC24LC08::MC24LC08(Interface ifc):
        EepromDriver(ifc,
        _24LC08_BASEADDR,
        0,                       // dont care when using I2C
        MC24LC08_SIZE,
        MC24LC08_BLOCK,
        MC24LC08_PAGE) {}


   /*********************************************************************
    * @brief        Store Data in MC24LC08
    * @param[in]    addr: address where to store,
    * @param[in]    length:     Length of write buffer
    * @param[in]    data: Pointer to data to store
    *
    * @return         SUCCESS or ERROR
    *
    **********************************************************************/
   bool MC24LC08::pWriteData(uint16_t addr, uint16_t length, const uint8_t *data)
   {
       bool success = true;
       /* FIXME: limit buffer (stack storage)! */
       uint8_t  buffer[getPageSize() +1];    ///< temp. buffer to store data, stores page and Address

       // check parameters:
       if ( (getSize() < addr)
         || (getSize() < length)
         || (getSize() < (addr + length)) ) return false;   // exceeds MC24LC08 size

       while (length && success)
       {
         // try to write complete pages (16 Byte)
         uint8_t pageOffset = addr   & (getPageSize() - 1);
         uint8_t pageLength = length>getPageSize() ? getPageSize() : length;
         uint32_t txLen,
                  rxLen = 0;
         if (getPageSize() < pageOffset + pageLength)
         {
             pageLength = getPageSize() - pageOffset;
         }
         memcpy(buffer + 1, data, pageLength);  // +1 because of EERPOM Address
         // Device Address, base address + memory block address
         address   = _24LC08_BASEADDR + getblockaddress(addr);
         buffer[0] = addr & 0xFF;    // EEPROM Address

         txLen=pageLength+1;         // +1 because of EERPOM Address
         success = transfer(buffer, txLen, nullptr, rxLen);

         // wait for ack, write access completed
         txLen=1;
         while (true != transfer(buffer, txLen, nullptr, rxLen)) {}

         data   += pageLength;
         addr   += pageLength;
         length -= pageLength;
       }

       return success;
   }


   /*********************************************************************
     * @brief        read Data out of MC24LC08
     * @param[in]    addr:   address where to read,
     * @param[in]    length: Length of read buffer
     * @param[out]     data: Pointer received
     *
     * @return         SUCCESS or ERROR
     *
     **********************************************************************/
   bool MC24LC08::pReadData(uint16_t addr, uint16_t length, uint8_t *data)
   {
       bool success = true;
       uint8_t wordAddr = addr & 0xFF;

       // check parameters:
       if ( (getSize() < addr)
         || (getSize() < length)
         || (getSize() < (addr + length)) ) return false;   // exceeds MC24LC08 size
       if (0 == length)                         return true;    // no data to store

       address = _24LC08_BASEADDR + getblockaddress(addr);

       uint32_t txLen=1,rxLen=length;
       success = transfer(&wordAddr, txLen, data, rxLen);
       return success;

   }
}   // namespace BSP
}   // namespace Platform
