#include "dma.hpp"

using namespace std;

int test_dma() {
  HW_unit DMA{0x01c02000};
  HW_unit CCU{0x01c20000};

  ///////////////////////////////////////////////////////////////////
  // register definition
  ///////////////////////////////////////////////////////////////////
  Register DMA_SEC{DMA, 0x20};
  Register DMA_AUTO_GATE{DMA, 0x28};
  Register DMA_STA{DMA, 0x30};

  u32 channel = 5;
  u32 channel_offset = channel * 0x40 + 0x100;

  Register DMA_EN_STA{DMA, channel_offset};
  Register DMA_PAU_REG{DMA, channel_offset + 0x4};
  Register DMA_DESC_ADDR_REG{DMA, channel_offset + 0x8};

  Register DMA_CFG_REG{DMA, channel_offset + 0xc};
  Register DMA_CUR_SRC_REG{DMA, channel_offset + 0x10};
  Register DMA_CUR_DEST_REG{DMA, channel_offset + 0x14};
  Register DMA_BCNT_LEFT_REG{DMA, channel_offset + 0x18};
  Register DMA_PARA_REG{DMA, channel_offset + 0x1c};
  Register DMA_FDESC_ADDR_REG{DMA, channel_offset + 0x2c};
  Register DMA_PKG_NUM_REG{DMA, channel_offset + 0x30};
  ///////////////////////////////////////////////////////////////////

  // source
  void *virt_page_src = nullptr;
  void *phy_page_src = nullptr;
  // destination
  void *virt_page_dst = nullptr;
  void *phy_page_dst = nullptr;
  // control block
  void *virt_page_cb = nullptr;
  void *phy_page_cb = nullptr;

  makeVirtPhysPage(virt_page_src, phy_page_src);
  makeVirtPhysPage(virt_page_dst, phy_page_dst);
  makeVirtPhysPage(virt_page_cb, phy_page_cb);

  // DMA ///////////////

  cout << "DMA region\n";
  cout << DMA_STA << " end" << endl;
  /////////////////////

  freeVirtPhysPage(virt_page_src);
  freeVirtPhysPage(virt_page_dst);
  freeVirtPhysPage(virt_page_cb);

  return 0;
}
