#pragma once

#include "constants.hpp"
#include "hexdump.hpp"
#include "memory.hpp"
#include "register.hpp"

using namespace std;

constexpr u32 NORMAL_WAIT = (8 << 0);
constexpr u32 stop_addr = 0xfffff800;

// Write to cfg block to read from same address
constexpr u32 IO_mode = (1 << 5);

template <u32 channel> class DMA {
  static constexpr u32 ch = channel * 0x40 + 0x100;

  Register<HW::CCU_BASE, 0x2c0> BUS_SOFT_RST_REG0;

  Register<HW::DMA_BASE, 0x20> DMA_SEC_REG;
  Register<HW::DMA_BASE, 0x28> DMA_AUTO_GATE_REG;
  Register<HW::DMA_BASE, 0x30> DMA_STA_REG;

  Register<HW::DMA_BASE, ch + 0x0> DMA_EN_REG;
  Register<HW::DMA_BASE, ch + 0x4> DMA_PAU_REG;
  Register<HW::DMA_BASE, ch + 0x8> DMA_DESC_ADDR_REG;
  Register<HW::DMA_BASE, ch + 0xc> DMA_CFG_REG;
  Register<HW::DMA_BASE, ch + 0x10> DMA_CUR_SRC_REG;
  Register<HW::DMA_BASE, ch + 0x14> DMA_CUR_DEST_REG;
  Register<HW::DMA_BASE, ch + 0x18> DMA_BCNT_LEFT_REG;
  Register<HW::DMA_BASE, ch + 0x1c> DMA_PARA_REG;
  Register<HW::DMA_BASE, ch + 0x2c> DMA_FDESC_ADDR_REG;
  Register<HW::DMA_BASE, ch + 0x30> DMA_PKG_NUM_REG;

  struct cb {
    u32 configuration;
    u32 source_addr;
    u32 destination_addr;
    u32 length;
    u32 parameter;
    u32 link;
  } __attribute__((packed));

public:
  void reset() {
    const u32 dma_reset_bit = 6;
    BUS_SOFT_RST_REG0[dma_reset_bit] = 0;
    BUS_SOFT_RST_REG0[dma_reset_bit] = 1;
  }

  void test() {
    // source
    void *virt_page_src = nullptr;
    void *phy_page_src = nullptr;
    // destination
    void *virt_page_dst = nullptr;
    void *phy_page_dst = nullptr;
    // control block
    void *virt_page_cb = nullptr;
    void *phy_page_cb = nullptr;

    makeVirtPhysPage(&virt_page_src, &phy_page_src);
    makeVirtPhysPage(&virt_page_dst, &phy_page_dst);
    makeVirtPhysPage(&virt_page_cb, &phy_page_cb);

    // write test bytes in to source page
    char *srcArray = static_cast<char *>(virt_page_src);
    const char msg[] = "Hello world";
    memcpy(srcArray, msg, sizeof(msg));

    cb *cb1 = reinterpret_cast<cb *>(virt_page_cb);
    cb1->configuration =
        (1 << 0) | (1 << 16); // SET src and destination to DRAM,
    cb1->source_addr = address_to_value(phy_page_src);
    cb1->destination_addr = address_to_value(phy_page_dst);
    cb1->length = 12;
    cb1->parameter = NORMAL_WAIT;
    cb1->link = stop_addr;

    while (!(DMA_STA_REG == 0)) {
      usleep(10000);
      std::cout << "print sleeping\r";
      reset();
    }

    DMA_SEC_REG[channel] = 1;

    cout << "----------------------  Write Descriptor  ----------------\n";
    DMA_DESC_ADDR_REG = address_to_value(phy_page_cb);
    usleep(10000);
    cout << "DMA_STA_REG: " << DMA_STA_REG << endl;
    cout << "DMA_EN_REG: " << DMA_EN_REG << endl;
    cout << "DMA_PAU_REG: " << DMA_EN_REG << endl;
    cout << "DMA_DESC_ADDR_REG: " << DMA_DESC_ADDR_REG << endl;
    cout << "DMA_DFG_REG: " << DMA_CFG_REG << endl;
    cout << "DMA_CUR_SRC_REG: " << DMA_CUR_SRC_REG << endl;
    cout << "DMA_CUR_DEST_REG: " << DMA_CUR_DEST_REG << endl;
    cout << "DMA_BCNT_LEFT_REG: " << DMA_BCNT_LEFT_REG << endl;
    cout << "DMA_PARA_REG: " << DMA_PARA_REG << endl;
    cout << "DMA_FDESC_ADDR_REG: " << DMA_FDESC_ADDR_REG << endl;
    cout << "DMA_PKG_NUM_REG: " << DMA_PKG_NUM_REG << endl;

    cout << "----------------------  Enable Channel  ----------------\n";
    DMA_EN_REG = 1;
    usleep(10000);
    cout << "DMA_STA_REG: " << DMA_STA_REG << endl;
    cout << "DMA_EN_REG: " << DMA_EN_REG << endl;
    cout << "DMA_PAU_REG: " << DMA_EN_REG << endl;
    cout << "DMA_DESC_ADDR_REG: " << DMA_DESC_ADDR_REG << endl;
    cout << "DMA_DFG_REG: " << DMA_CFG_REG << endl;
    cout << "DMA_CUR_SRC_REG: " << DMA_CUR_SRC_REG << endl;
    cout << "DMA_CUR_DEST_REG: " << DMA_CUR_DEST_REG << endl;
    cout << "DMA_BCNT_LEFT_REG: " << DMA_BCNT_LEFT_REG << endl;
    cout << "DMA_PARA_REG: " << DMA_PARA_REG << endl;
    cout << "DMA_FDESC_ADDR_REG: " << DMA_FDESC_ADDR_REG << endl;
    cout << "DMA_PKG_NUM_REG: " << DMA_PKG_NUM_REG << endl;

    cout << "----------------------  Start Channel  ----------------\n";

    if (DMA_STA_REG == 0x20) {
      std::cout << " Resume dma\n";
      DMA_PAU_REG = 0;
    }

    sleep(5);

    cout << "Send: " << srcArray << endl;
    cout << Hexdump(virt_page_src, 64) << std::endl;
    cout << "Send debug: " << static_cast<char *>(virt_page_dst) << endl;
    cout << Hexdump(virt_page_dst, 64) << std::endl;

    freeVirtPhysPage(virt_page_src);
    freeVirtPhysPage(virt_page_dst);
    freeVirtPhysPage(virt_page_cb);
  }
};
