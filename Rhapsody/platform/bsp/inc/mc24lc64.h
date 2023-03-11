/**
 *  \brief     Implements an interface to MC24LC64 EEPROM.
 *  \details   This file defines the interface to EEPROM mounted on the
 *             LPCXpress01768 rev D1 board (see 24LC64 hardware documentation
 *             for details).\n
 *             The EEPROM provides 64kibit (8 KiBytes) capacity
 *
 *  \author    J. Wuebbelmann
 *  \version   2.0
 *  \date      02.05.2020
 *  \pre
 *  \copyright HS Osnabrueck
 */

/** @file */

#ifndef MC24LC64_H_
#define MC24LC64_H_

#include <i2cdevice.h>
#include <eepromdriver.h>
//#include <cstring>

namespace Platform {
namespace BSP {


/**
 * This class handles store and read access to 8k-bit serial EEPROM
 */
class MC24LC64: public EepromDriver<MC24LC64, I2CDevice> {
public:
    /**
     * \brief defines the possible chip select values of MC24LC64 devices
     */
    enum class ChipSelect
    {
        CS0 = 0,   ///< Control byte A2 A1 A0 = 0 0 0
        CS1,       ///< Control byte A2 A1 A0 = 0 0 1
        CS2,       ///< Control byte A2 A1 A0 = 0 1 0
        CS3,       ///< Control byte A2 A1 A0 = 0 1 1
        CS4,       ///< Control byte A2 A1 A0 = 1 0 0
        CS5,       ///< Control byte A2 A1 A0 = 1 0 1
        CS6,       ///< Control byte A2 A1 A0 = 1 1 0
        CS7,       ///< Control byte A2 A1 A0 = 1 1 1
    };

    /**
     * Constructor
     * \param [in] ifc used I2C Interface of type \ref Interface
     * \param [in] cs Chip select of instance (4 Device are allowed)
     */
    MC24LC64(Interface ifc, ChipSelect cs = ChipSelect::CS0);

protected:
    /**
     * read data from EEPROM
     * @param [in] addr   read address in EEPORM. Range: [0...MC24LC64_SIZE -1]
     * @param [in] length length of data to read, lenghth + addr must be in address range of EEPROM
     * @param [out] data  buffer in which data is written, memory is taken for granted.
     * @return true if success
     */
    bool pReadData(uint16_t addr, uint16_t length, uint8_t *data);

    /**
     * store data in EEPROM
     * @param [in] addr   write adress in EEPROM. Range: [0...MC24LC64_SIZE -1]
     * @param [in] length length of data to write, lenghth + addr must be in address range of EEPROM
     * @param [in] data   pointer to write data.
     * @return true if success
     */
    bool pWriteData(uint16_t addr, uint16_t length, const uint8_t *data);

    friend EepromDriver<MC24LC64, I2CDevice>;    ///< own base class has access to protected methods

private:
    uint32_t m_cs = static_cast<uint32_t>(ChipSelect::CS0);     // Default on LPCXpresso board

};

}   // namespace BSP
}   // namespace Platform

#endif /* MC24LC64_H_ */
