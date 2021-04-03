#ifndef DMA_HPP__
#define DMA_HPP__

#include "HW_unit.hpp"
#include "constants.hpp"
#include "memory.hpp"
#include "register.hpp"

class DMA {
  HW_unit CCU_HW{0x01c20000};
  HW_unit DMA_HW{0x01c02000};

  ///////////////////////////////////////////////////////////////////
  // register definition DMA
  ///////////////////////////////////////////////////////////////////
  Register BUS_SOFT_RST_REG0{CCU_HW, 0x2c0};
  Register DMA_SEC_REG{DMA_HW, 0x20};
  Register DMA_AUTO_GATE_REG{DMA_HW, 0x28};
  Register DMA_STA_REG{DMA_HW, 0x30};

  u32 channel = 5;
  u32 channel_offset = channel * 0x40 + 0x100;
  Register DMA_EN_REG{DMA_HW, channel_offset};
  Register DMA_PAU_REG{DMA_HW, channel_offset + 0x4};
  Register DMA_DESC_ADDR_REG{DMA_HW, channel_offset + 0x8};

  Register DMA_CFG_REG{DMA_HW, channel_offset + 0xc};
  Register DMA_CUR_SRC_REG{DMA_HW, channel_offset + 0x10};
  Register DMA_CUR_DEST_REG{DMA_HW, channel_offset + 0x14};
  Register DMA_BCNT_LEFT_REG{DMA_HW, channel_offset + 0x18};
  Register DMA_PARA_REG{DMA_HW, channel_offset + 0x1c};
  Register DMA_FDESC_ADDR_REG{DMA_HW, channel_offset + 0x2c};
  Register DMA_PKG_NUM_REG{DMA_HW, channel_offset + 0x30};

  struct cb {
    u32 configuration;
    u32 source_addr;
    u32 destination_addr;
    u32 length;
    u32 parameter;
    u32 link;
  } __attribute__((packed));

public:
  DMA(const u32 channel);
  void reset();
  void test();
};

#endif