#include "register.hpp"

using namespace std;

Register::Register(HW_unit &hw, u32 offset) {
  assertm(offset < PAGE_SIZE, "Offset is larger than one page of memory");
  phy_address = reinterpret_cast<volatile u32 *>(
      reinterpret_cast<u64>(hw.address()) + offset);
}

Register::Register(u32 *address) { phy_address = address; }

Register::~Register() {}

void Register::write(u32 value) { *phy_address = value; }

u32 Register::read() { return *phy_address; }

Register &Register::operator=(const u32 value) {
  this->write(value);
  return *this;
}

Bit &Register::operator[](u32 bit_num){
  this->bit_mask = bit_num;
  return *this;
}

bool operator==(Register &r, const u32 value) { return r.read() == value; }

std::ostream &operator<<(std::ostream &os, Register &r) {
  os << hex;
  os << "0x" << r.read() << " ";
  os << dec;
  return os;
}
