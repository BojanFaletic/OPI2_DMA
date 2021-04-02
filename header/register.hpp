#ifndef REGISTER_HPP__
#define REGISTER_HPP__

#include <ostream>
#include <cassert>

#include "constants.hpp"
#include "HW_unit.hpp"
#include "bit.hpp"


class Register : protected Bit{
protected:
  volatile u32 *phy_address;

public:
  Register(HW_unit &hw, u32 offset);
  Register(u32 *address);
  ~Register();

  void write(u32 value);
  u32 read();


  Register& operator=(const u32 value);
  Bit& operator[](u32 bit_num);
  friend bool operator==(Register &r, const u32 value);
  friend std::ostream &operator<<(std::ostream &os, Register &r);
};

#endif