#ifndef GPIO_HPP__
#define GPIO_HPP__

#include "HW_unit.hpp"
#include "register.hpp"

class GPIO {
public:
  GPIO();

  void write();
  u32 read();
};

#endif