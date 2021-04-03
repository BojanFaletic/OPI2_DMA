#ifndef REGISTER_HPP__
#define REGISTER_HPP__

#include <cassert>
#include <map>
#include <ostream>

#include "bit.hpp"
#include "constants.hpp"
#include "memory.hpp"

struct entry {
  u32 counter;
  u32 *physical_address;
};
static std::map<u32, entry> mappings;

template <u32 base, u32 offset> class Register : protected Bit {
private:
  static_assert(offset < PAGE_SIZE, "Offset is larger than one page of memory");
  static_assert(offset % 4 == 0, "Offset must be word aligned");

  void add_mapping() {
    u32 *mmap_addr = mapPeripheral(base);
    mappings[base] = {1, mmap_addr};
  }

  void unmap() {
    auto it = mappings.find(base);
    it->second.counter--;
    if (it->second.counter <= 0) {
      unmapPeripheral(it->second.physical_address);
      mappings.erase(it);
    }
    if (mappings.size() == 0) {
      close_devmem();
    }
  }

  void map() {
    if (mappings.size() == 0) {
      open_devmem();
    }
    auto it = mappings.find(base);
    if (it != mappings.end()) {
      it->second.counter++;
    } else {
      add_mapping();
    }
  }

  u32 *lookup() {
    u32 *phy_base = mappings.find(base)->second.physical_address;
    return phy_base + offset / 4;
  }

  volatile u32 *phy_address = nullptr;

public:
  Register() {
    map();
    phy_address = lookup();
  }
  ~Register() { unmap(); }

  void write(u32 value) { *phy_address = value; };

  u32 read() { return *phy_address; }

  Register &operator=(const u32 value) {
    this->write(value);
    return *this;
  }

  Bit &operator[](u32 bit_num) {
    this->bit_mask = bit_num;
    return *this;
  }

  friend bool operator==(Register &r, const u32 value) {
    return r.read() == value;
  }

  friend std::ostream &operator<<(std::ostream &os, Register &r) {
    os << std::hex;
    os << "0x" << r.read() << " ";
    os << std::dec;
    return os;
  }
};

#endif