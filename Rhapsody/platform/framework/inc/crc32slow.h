/**
 *  \brief     Calculation of CRC32 Checksum compliant to CCIT21
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      12.12.2019
 *  \copyright HS Osnabrueck
 */

/** @file */


#ifndef PLATFORM_FRAMEWORK_CRC32SLOW_H_
#define PLATFORM_FRAMEWORK_CRC32SLOW_H_

#include <private/checksum.h>



namespace Platform
{
namespace Framework
{

/**
 *  \class crc32slow inc/crc32slow.h
 *  class for claculation of crc32 checksum compliant to CCIT32.\n
 */
class crc32slow: public checksum<crc32slow>
{
public:
	crc32slow():checksum<crc32slow>("CCIT32_SLOW") {}

	/*!
	 *  \brief get polynome
	 *
	 * \return used polynome for CRC32 calculation
	 */
	const uint32_t getPolynome() const	{ return polynome;}

protected:
    /*!
     * \brief calculates CRC32 checksum in loop.\n
     * Polynom is
     * \param [in] data Byte pointer to data
     * \param [in] nBytes length of byte stream
     * \return checksum
     */
	uint32_t pcalc(const uint8_t* data, std::size_t nBytes) const;
    friend checksum<crc32slow>;       ///< must be friend, calls my protected method.
private:
    const uint32_t ccitt32_crcinit = -1;     ///< initvalue conform to CCIT32
    const uint32_t polynome = 0x4c11db7;     ///< polynome used for table calculation
};

} /* namespace Framework */
} /* namespace Platform */

#endif /* PLATFORM_FRAMEWORK_CRC32SLOW_H_ */
