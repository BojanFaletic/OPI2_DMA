#include "HW_unit.hpp"

static u32 num_of_units = 0;

HW_unit::HW_unit(u32 base_address) {
  open_devmem();
  this->phy_address = mapPeripheral(base_address);
  num_of_units++;
}

HW_unit::~HW_unit() {
  num_of_units--;
  unmapPeripheral(this->phy_address);
  if (num_of_units == 0) {
    close_devmem();
  }
}

u32 *HW_unit::address() const { return phy_address; }