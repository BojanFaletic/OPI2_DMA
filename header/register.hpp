#ifndef REGISTER_HPP__
#define REGISTER_HPP__

#include "constants.hpp"
#include "memory.hpp"
#include <cassert>
#include <map>

class Register {
protected:
  volatile u32 *phy_address;

public:
  Register(volatile u32 *base, u32 offset);
  ~Register();
  void write(u32 value);
  u32 read();

  void operator=(const u32 value);
  void operator=(const u32 &value);
};

#endif