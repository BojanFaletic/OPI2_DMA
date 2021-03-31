#include "dma.hpp"

using namespace std;
const u32 dma_base_address = 0x01c02000;
const u32 ccu_base_address = 0x01c20000;

int test_dma() {
  HW_unit DMA{dma_base_address};
  HW_unit CCU{ccu_base_address};

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
  /////////////////////

  freeVirtPhysPage(virt_page_src);
  freeVirtPhysPage(virt_page_dst);
  freeVirtPhysPage(virt_page_cb);

  return 0;
}
