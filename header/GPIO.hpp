#ifndef GPIO_HPP__
#define GPIO_HPP__

#include "HW_unit.hpp"
#include "register.hpp"

class GPIO {
    HW_unit GPIO_HW{HW::GPIO_BASE};
public:
  GPIO();

  void write();
  u32 read();
};

#endif