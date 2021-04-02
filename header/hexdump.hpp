#ifndef HEXDUMP_HPP
#define HEXDUMP_HPP

#include <cctype>
#include <iomanip>
#include <ostream>
#include "constants.hpp"

template <unsigned RowSize, bool ShowAscii> struct CustomHexdump {
  CustomHexdump(void *data, unsigned length)
      : mData(static_cast<unsigned char *>(data)), mLength(length) {}
  const unsigned char *mData;
  const unsigned mLength;
};

template <unsigned RowSize, bool ShowAscii>
std::ostream &operator<<(std::ostream &out,
                         const CustomHexdump<RowSize, ShowAscii> &dump) {
  out.fill('0');
  for (u32 i = 0; i < dump.mLength; i += RowSize) {
    out << "0x" << std::setw(6) << std::hex << i << ": ";
    for (u32 j = 0; j < RowSize; ++j) {
      if (i + j < dump.mLength) {
        out << std::hex << std::setw(2) << static_cast<int>(dump.mData[i + j])
            << " ";
      } else {
        out << "   ";
      }
    }

    out << " ";
    if (ShowAscii) {
      for (u32 j = 0; j < RowSize; ++j) {
        if (i + j < dump.mLength) {
          if (std::isprint(dump.mData[i + j])) {
            out << static_cast<char>(dump.mData[i + j]);
          } else {
            out << ".";
          }
        }
      }
    }
    out << std::endl;
  }
  return out;
}

typedef CustomHexdump<16, true> Hexdump;

#endif // HEXDUMP_HPP