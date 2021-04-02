#ifndef BIT_HPP__
#define BIT_HPP__

#include "constants.hpp"
#include <iostream>

class Bit {
private:
  virtual void write(u32) =0;
  virtual u32 read() = 0;
  void set(u32 bit_num);
  void clear(u32 bit_num);
  u32 read(u32 bit_num);

protected:
  u32 bit_mask;

public:
  Bit &operator=(u32 value);
  friend std::ostream &operator<<(std::ostream &os, Bit &b);
  friend bool operator==(Bit &b, u32 value);
};

#endif