#include "register.hpp"

using namespace std;

Register::Register(volatile u32 *base, u32 offset) {
  assertm(offset >= PAGE_SIZE, "Offset is larger than one page of memory");

  phy_address =
      reinterpret_cast<volatile u32 *>(reinterpret_cast<u64>(base) + offset);
}

void Register::write(u32 value) { *phy_address = value; }

u32 Register::read() { return *phy_address; }

void Register::operator=(const u32 value) { this->write(value); }

void Register::operator=(const u32 &value) {
  u32 v = value;
  this->write(v);
}