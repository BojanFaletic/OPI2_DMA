#include "bit.hpp"
#include <iostream>

void Bit::set(u32 bit_num) {
  u32 value = this->read();
  value |= (1 << bit_num);
  this->write(value);
}

void Bit::clear(u32 bit_num) {
  u32 value = this->read();
  value &= ~(1 << bit_num);
  this->write(value);
}

u32 Bit::read(u32 bit_num) {
  u32 value = this->read();
  value &= (1 << bit_num);
  return value >> bit_num;
}

Bit &Bit::operator=(u32 value) {
  if (value == 0) {
    this->clear(bit_mask);
  } else {
    this->set(bit_mask);
  }
  return *this;
}

std::ostream &operator<<(std::ostream &os, Bit &b) {
  os << "0b";
  os << std::hex;
  os << b.read(b.bit_mask);
  os << std::dec;
  os << " ";
  return os;
}

bool operator==(Bit &b, u32 value){
  return b.read(b.bit_mask) == value;
}
