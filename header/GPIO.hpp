#pragma once

#include "register.hpp"

class GPIO {
private:
  Register<HW::GPIO_BASE, 0x00> PN_CFG0;

public:
  GPIO();

  void write();
  u32 read();
};
