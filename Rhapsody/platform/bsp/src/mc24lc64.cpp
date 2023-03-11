/*
 * mc24lc64.cpp
 *
 *  Created on: 08.07.2015
 *      Author: Wuebbelmann
 */

/// \file

#include <mc24lc64.h>
#include <cstring>    // for memcpy



namespace Platform {
namespace BSP {
// Address sequence Bit Assignment:
// Control Byte: 1  0  1  0  A2 A1 A0 R/W
//              |          ||        |
//               ----------  --------
//             Control Code  Chip Select,
//     with A2=A1=A0 = 0 Wired on LPCXpresso Board
//
// Address High Byte:  DC  DC  DC  A12 A11 A10 A9  A8
// Address Low  Byte:  A7  A6  A5  A4  A3  A2  A1  A0
   static constexpr uint8_t     _24LC64_BASEADDR = 0x50;    ///< 7 bit I2C address of EEPROM
   static constexpr std::size_t  MC24LC64_SIZE  = 0x2000;   ///< EPPROM contains 8000 Bytes capacity
   static constexpr std::size_t  MC24LC64_BLOCK = 0x2000;   ///< EPPROM block size
   static constexpr std::size_t  MC24LC64_PAGE  = 32;       ///< EPPROM pagesize, write and readable in one access

   MC24LC64::MC24LC64(Interface ifc, ChipSelect cs) :
           EepromDriver(ifc,
                       _24LC64_BASEADDR,
                        0,                       // dont care when using I2C
                       MC24LC64_SIZE,
                       MC24LC64_BLOCK,
                       MC24LC64_PAGE),
                       m_cs(static_cast<uint32_t>(cs)) {};


   /*********************************************************************
    * @brief        Store Data in MC24LC64
    * @param[in]    addr: address where to store,
    * @param[in]    length:     Length of write buffer
    * @param[in]    data: Pointer to data to store
    *
    * @return         SUCCESS or ERROR
    *
    **********************************************************************/
   //Address, size & data to store
   bool MC24LC64::pWriteData(uint16_t addr, uint16_t length,const uint8_t *data)
   {
       bool success = true;
       /* FIXME: limit buffer (stack storage)! */
       uint8_t  buffer[getPageSize() +2];    ///< temp. buffer to store data, stores page and Address

       // check parameters:
       if ( (getSize() < addr)
         || (getSize() < length)
         || (getSize() < (addr + length)) ) return false;   // exceeds MC24LC64 size

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

         memcpy(buffer + 2, data, pageLength);  // +2 because of EEPROM Address

         // Device Address, base address + memory block address
         address   = _24LC64_BASEADDR + m_cs;   /// FIXME: never tested with m_cs != 0 !!!!

         buffer[0] = (addr >> 8) & 0x1F;    // EEPROM Address  A12-A8
         buffer[1] = addr & 0xFF;           // EEPROM Address  A7 - A0

         txLen=pageLength+2;
         success = transfer(buffer, txLen, nullptr, rxLen); // +2 because of EERPOM Address

         // wait for ack, write access completed
         txLen=1;
         while (true != transfer(buffer, txLen, nullptr, rxLen)) {}

         data      += pageLength;
         addr      += pageLength;
         length    -= pageLength;
       }

       return success;
   }


   /*********************************************************************
     * @brief        read Data out of MC24LC64
     * @param[in]    addr:   address where to read,
     * @param[in]    length: Length of read buffer
     * @param[out]     data: Pointer received
     *
     * @return         SUCCESS or ERROR
     *
     **********************************************************************/
   bool MC24LC64::pReadData(uint16_t addr, uint16_t length, uint8_t* data)
   {
       bool success = true;
       uint8_t buffer[2];
//       uint16_t wordAddr = addr & 0x1FFF;
       buffer[0] = (addr >> 8) & 0x1F;    // EEPROM Address  A12-A8
       buffer[1] = addr & 0xFF;           // EEPROM Address  A7 - A0


       // check parameters:
       if ( (getSize() < addr)
         || (getSize() < length)
         || (getSize() < (addr + length)) ) return false;   // exceeds MC24LC64 size
       if (0 == length)                     return true;    // no data to store

       address = _24LC64_BASEADDR + (m_cs << 1);

       uint32_t txLen=2 ,
                rxLen=length;
       success = transfer(buffer, txLen, data, rxLen);
       return success;
   }
}   // namespace BSP
}   // namespace Platform
