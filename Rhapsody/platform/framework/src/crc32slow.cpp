/*
 * crc32slow.cpp
 *
 *  Created on: 12.12.2019
 *      Author: Wuebbelmann
 */

#include "crc32slow.h"

namespace Platform
{
namespace Framework
{

typedef uint32_t crc;    ///< definition of crc data type!
#define WIDTH (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))

crc crc32slow::pcalc(const uint8_t* data, std::size_t nBytes) const
{
  crc  rest =  ccitt32_crcinit;
  /* Modulo 2 Division, pro Byte */
  for (std::size_t byte = 0; byte < nBytes; ++byte) {
    rest ^= (data[byte] << (WIDTH - 8));
    /*Modulo 2 Division, pro bit. */
    for (int bit = 8; bit > 0; --bit) {
      if (rest & TOPBIT)
        rest = (rest << 1) ^ polynome;
      else
        rest = (rest << 1);
    }
  }
  /* rest contains CRC checksum */
  return rest;
}
} /* namespace Framework */
} /* namespace Platform */
