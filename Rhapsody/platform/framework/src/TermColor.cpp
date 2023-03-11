/**
 *  \brief     cout definition.
 *  \details   This file defines a global reference to a singleton object cout \n
 *  of type \ref Platform::BSP::TermColor
 *
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      14.06.2016
 *  \copyright HS Osnabrueck
 */

/** @file */

#include "TermColor.h"

namespace Platform
{
namespace BSP
{
TermColor& cout = TermColor::getInstance();  ///< reference to TermColor object, can be used for C++ like output
                                             ///< without iostream / newlib nano memory overhead.
}
}
