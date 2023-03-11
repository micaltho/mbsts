/* This file is auto generated from Rhapsody do not edit! */

#ifndef RXF_CONFIG_H
#define RXF_CONFIG_H

#include <cstdint>

#include "RXF_Defines.h"

#include "RXF_Priority.h"

/* @MISRA_3-4-1=OFF ID-0010: Configuration values must be declared globally, because they are generated and the framework code itself needs to stay untouched */

namespace RXF {

constexpr std::uint32_t REACTIVE_MAX_NULL_STEPS = 10U;

constexpr std::uint32_t MS_PER_TICK = 1U;

constexpr std::uint32_t MAIN_TASK_QUEUE_SIZE = 100U;

constexpr Priority::Type MAIN_TASK_PRIORITY = RXF::Priority::NORMAL;
constexpr std::uint32_t MAIN_TASK_STACK_SIZE = 1024U;

/* @MISRA_3-4-1=ON (end of ID-0010) */

}

#endif /* RXF_CONFIG_H */
