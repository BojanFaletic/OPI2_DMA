#ifndef CONSTANTS_HPP__
#define CONSTANTS_HPP__

#include <stdint.h>

#define assertm(exp, msg) assert(((void)msg, exp))

typedef unsigned short u8;
typedef unsigned int u32;
typedef unsigned short int u16;
typedef unsigned long long u64;

namespace HW {
constexpr u32 CCU_BASE = 0x01C20000;
constexpr u32 GPIO_BASE = 0x01C20800;
constexpr u32 PWM_BASE = 0x01C21400;
constexpr u32 DMA_BASE = 0x01c02000;
constexpr u32 TWI0_BASE = 0x01C2AC00;
} // namespace HW

#endif