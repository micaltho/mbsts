/**
 *  \brief     Calculation of CRC32 Checksum compliant to CCIT21
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      12.12.2019
 *  \copyright HS Osnabrueck
 */

/** @file */


#ifndef PLATFORM_FRAMEWORK_CRC32_H_
#define PLATFORM_FRAMEWORK_CRC32_H_

#include <private/checksum.h>



namespace Platform
{
namespace Framework
{

/**
 *  \class crc32 inc/crc32.h
 *  class for claculation of crc32 checksum compliant to CCIT32.\n
 */
class crc32: public checksum<crc32>
{
public:
    crc32():checksum<crc32>("CCIT32") {}

    /*!
     *  \brief get polynome
     *
     * \return used polynome for CRC32 calculation
     */
    const uint32_t getPolynome() const    { return polynome;}

private:
    /*!
     * \brief calculates CRC32 checksum with table driven algoritm.\n
     * Polynom is 0x4c11db7 (standard CCIT32 Value)
     * \param [in] data Byte pointer to data
     * \param [in] nBytes length of byte stream
     * \return checksum
     */
    uint32_t pcalc(const uint8_t* data, std::size_t nBytes) const;
    friend checksum<crc32>;       ///< must be friend, calls my protected method.
private:
    const uint32_t ccitt32_crcinit = -1;     ///< initvalue conform to CCIT32
    const uint32_t polynome = 0x4c11db7;     ///< polynome used for table calculation
};

} /* namespace Framework */
} /* namespace Platform */

#endif /* PLATFORM_FRAMEWORK_CRC32_H_ */
