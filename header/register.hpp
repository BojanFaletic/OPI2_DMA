#ifndef REGISTER_HPP__
#define REGISTER_HPP__

#include <ostream>
#include <cassert>

#include "constants.hpp"
#include "HW_unit.hpp"


class Register {
protected:
  volatile u32 *phy_address;

public:
  Register(HW_unit &hw, u32 offset);
  ~Register();
  void write(u32 value);
  u32 read();

  void operator=(const u32 value);
  void operator=(const u32 &value);
  friend std::ostream &operator<<(std::ostream &os, Register &r);
};

#endif