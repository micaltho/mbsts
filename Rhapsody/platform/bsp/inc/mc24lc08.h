/**
 *  \brief     Implements an interface to EEPROM.
 *  \details   This file defines the interface to EEPROM mounted on
 *             the EA base board (see 24LC08 hardware documentation for details).
 *             The EEPROM provides 8kbit (1024 bytes) capacity
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      29.09.2015
 *  \pre
 *  \copyright HS Osnabrueck
 */

/** @file */

#ifndef MC24LC08_H_
#define MC24LC08_H_

#include <i2cdevice.h>
#include <eepromdriver.h>

namespace Platform {
namespace BSP {

/**
 * This class handles store and read access to 8k-bit serial EEPROM
 */
class MC24LC08: public EepromDriver<MC24LC08, I2CDevice> {
public:
  /**
   * Constructor, no parameters are needed
   */
  MC24LC08(Interface ifc);

protected:
    /**
     * read data from EEPROM
     * @param [in] addr   read address in EEPORM. Range: [0...MC24LC08_SIZE -1]
     * @param [in] length length of data to read, lenghth + addr must be in address range of EEPROM
     * @param [out] data  buffer in which data is written, memory is taken for granted.
     * @return true if success
     */
    bool pReadData(uint16_t addr, uint16_t length, uint8_t *data);

    /**
     * store data in EEPROM
     * @param [in] addr   write adress in EEPROM. Range: [0...MC24LC08_SIZE -1]
     * @param [in] length length of data to write, lenghth + addr must be in address range of EEPROM
     * @param [in] data   pointer to write data.
     * @return true if success
     */
    bool pWriteData(uint16_t addr, uint16_t length, const uint8_t *data);

    friend EepromDriver<MC24LC08, I2CDevice>;      ///< own base class has access to protected methods
private:
    /**
     * Gets bit 9 and 10 of address, these bits are 2 bit address of a block
     * @param x  address to convert
     * @return  2 bit address of block in which x is located.
     */
    uint16_t getblockaddress(uint16_t x) const {return (((x) & 0x3FF) >> 8);};

};

}   // namespace BSP
}   // namespace Platform

#endif /* MC24LC08_H_ */
