/**
 *  \brief     Base Class for Checksum calculation
 *  \details   This class provide a unique interface for all checksum algorithms. e.g. CRC
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      12.12.2019
 *  \copyright HS Osnabrueck
 */

/** @file */
#ifndef PLATFORM_FRAMEWORK_CHECKSUM_H_
#define PLATFORM_FRAMEWORK_CHECKSUM_H_

#include <cstdint>


namespace Platform
{
namespace Framework
{

/**
 *  \class checksum inc/private/checksum.h
 *  template base class for checksum calculations.\n
 *  A common interface is provided, all derived classes must implement a pcalc method\n
 *  and have this class as friend.\n
 *  pcalc() is called by \ref calcCheckSum
 *
 *  Derived Classes follow the CRTP design pattern!\n
 *  e.g:\n
 *  \code
 *  class crc : public checksum<crc>
 *  {
 *  protected:
 *     uint32_t pcalc(const uint8_t* data, size_t nBytes) const;
 *     friend checksum<crc>;
 *  };
 *  \endcode
 */

template<class T>
class checksum
{
public:
    /*!
     * \brief calculates checksum for nBytes of byte stream data by calling \n
     * pcalc() method of derived class. (CRTP)
     * \param [in] data Byte pointer to data
     * \param [in] nBytes length of byte stream
     * \return checksum
     */
    std::uint32_t calcCheckSum(const uint8_t* data, std::size_t nBytes) const
    {
        return static_cast<const T*>(this)->T::pcalc(data, nBytes);
    }

    /*!
     *  \brief get algorithm name
     *
     * \return name of algorithm
     */
    const char* getUsedAlgo() const {return usedAlgo;}
protected:
    /*!
     *  \brief Constructor
     * \param [in] algo name of the used algorithm
     */
    checksum(const char* algo):usedAlgo(algo) {};
    //! \cond HIDDEN_DOXYGEN
    ~checksum() = default;
    checksum(const checksum&) = default;
    checksum& operator=(const checksum&) = default;
    //! @endcond
    const char * usedAlgo;  ///< name of used algorithm
};

} /* namespace Framework */
} /* namespace Platform */

#endif /* PLATFORM_FRAMEWORK_CHECKSUM_H_ */
