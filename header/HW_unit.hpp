#ifndef HW_UNIT_HPP__
#define HW_UNIT_HPP__

#include "memory.h"
#include "register.hpp"

class HW_unit {
private:
  u32 *phy_address;

public:
  HW_unit(u32 base_address);
  ~HW_unit();
};

#endif