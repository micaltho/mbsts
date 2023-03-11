/*
 *  \file eepromdriver.h
 *  \brief     Contains Base Class for EEROM drivers
 *  \details   This class provide a unique interface for all EEPROM drivers.
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      02.05.2020
 *  \copyright HS Osnabrueck
 */

/** @file */
#ifndef PLATFORM_BSP_INC_EEPROMDRIVER_H_
#define PLATFORM_BSP_INC_EEPROMDRIVER_H_

#include <cstdlib>    // for std::size

namespace Platform {
namespace BSP {

/**
 *  \class EepromDriver
 *  template base class for EEPROM drivers.\n
 *  A common interface is provided, all derived classes must implement a pReadData and a
 *  pWriteData method and have this class as friend.\n
 *  pReadData() is called by \ref read \n
 *  pWriteData() is called by \ref store \n
 *
 *  Derived Classes follow the CRTP design pattern!\n
 *  e.g:\n
 *  \code
 *  class MC24LC64 : public EepromDriver<MC24LC64, I2CDevice>
 *  {
 *  protected:
 *     bool pReadData((uint16_t addr, uint16_t length, uint8_t *data);
 *     bool pWriteData(uint16_t addr, uint16_t length, const uint8_t *data);
 *     friend EepromDriver<MC24LC64, I2CDevice>;
 *  };
 *  \endcode
 *
 *  \tparam T Class of specific EEPROM driver
 *  \tparam U Class of HW Interface, e.g I2CDevice or SSPDevice
 *  \note For the time being, only \ref I2CDevice is tested.
 */
template<class T, class U>
class EepromDriver : public U{
public:
    /**
     * read data from EEPROM
     * @param [in] addr   read address in EEPORM. Range: [0...MC24LC64_SIZE -1]
     * @param [in] length length of data to read, length + addr must be in address range of EEPROM
     * @param [out] data  buffer in which data is written, memory is taken for granted.
     * @return true if success
     */
    bool read(uint16_t addr, uint16_t length, uint8_t *data)
    {
        return static_cast<T*>(this)->T::pReadData(addr, length, data);
    }


    /**
     * store data in EEPROM
     * @param [in] addr   write adress in EEPROM. Range: [0...MC24LC64_SIZE -1]
     * @param [in] length length of data to write, lenghth + addr must be in address range of EEPROM
     * @param [in] data   pointer to write data.
     * @return true if success
     */
    bool store(uint16_t addr, uint16_t length, const uint8_t *data)
    {
        return static_cast<T*>(this)->T::pWriteData(addr, length, data);
    }

    /**
     * get EEPROM capacity in Bytes
     * \return capacity
     */
    constexpr std::size_t getSize() const { return m_size;}
    /**
     * get EEPROM block size in Byte
     * \return block size
     */
    constexpr std::size_t getBlockSize() const { return m_block;}
    /**
     * get EEPROM page size in Byte
     * \return page size
     */
    constexpr std::size_t getPageSize() const { return m_page;}
protected:
    /**
     * Constructor
     * \param [in] ifc used Interface of \ref I2CDevice or \ref SSPDevice
     * \param [in] addr_port addr of \ref I2CDevice address of EEPROM device or\n
     *        SSEL port of SSPDevice\n
     *        depending on template parameter U
     * \param [in] dc_pin dont care if \ref I2CDevice is used or\n
     *        SSEL pin of SSPDevice\n
     *        depending on template parameter U
     * \param [in] size Capacity of EEPROM in Bytes
     * \param [in] block EEPROM Block size
     * \param [in] page EEPROM page size
     */
    EepromDriver(typename U::Interface ifc,
                 uint8_t addr_port,
                 uint8_t dc_pin,
                 std::size_t size,
                 std::size_t block,
                 std::size_t page):
        U(ifc, addr_port, dc_pin),
        m_size(size),
        m_block(block),
        m_page(page)
    {}
private:
    const std::size_t m_size;
    const std::size_t m_block;
    const std::size_t m_page;

};

} /* namespace BSP */
} /* namespace Platform */

#endif /* PLATFORM_BSP_INC_EEPROMDRIVER_H_ */
