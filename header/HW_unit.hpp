#ifndef HW_UNIT_HPP__
#define HW_UNIT_HPP__

#include "constants.hpp"
#include "memory.hpp"

class HW_unit {
private:
  u32 *phy_address;

public:
  HW_unit(u32 base_address);
  ~HW_unit();

  u32* address();
};

#endif