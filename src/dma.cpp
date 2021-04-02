#include "dma.hpp"
#include "hexdump.hpp"

using namespace std;

#define NORMAL_WAIT	(8 << 0)

// descriptor information for DMA
typedef struct DMA_CB_ {
  u32 configuration;
  u32 source_addr;
  u32 destination_addr;
  u32 byte_counter;
  u32 commity_parameter;
  u32 link;
} DMA_CB;

/* lli: linked list ltem, the DMA block descriptor */
struct sunxi_dma_lli {
  u32 cfg;   /* DMA configuration */
  u32 src;   /* Source address */
  u32 dst;   /* Destination address */
  u32 len;   /* Length of buffers */
  u32 para;  /* Parameter register */
  u32 link;  /* Next lli virtual address (only for cpu) */
} __attribute__((packed));

void reset_DMA(Register &r) {
  r[6] = 0;
  r[6] = 1;
}


int test_dma() {
  HW_unit DMA{0x01c02000};
  HW_unit CCU{0x01c20000};

  ///////////////////////////////////////////////////////////////////
  // register definition DMA
  ///////////////////////////////////////////////////////////////////
  Register BUS_SOFT_RST_REG0{CCU, 0x2c0};

  ///////////////////////////////////////////////////////////////////
  // register definition DMA
  ///////////////////////////////////////////////////////////////////
  Register DMA_SEC_REG{DMA, 0x20};
  Register DMA_AUTO_GATE_REG{DMA, 0x28};
  Register DMA_STA_REG{DMA, 0x30};

  u32 channel = 1;
  u32 channel_offset = channel * 0x40 + 0x100;

  Register DMA_EN_REG{DMA, channel_offset};
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

  makeVirtPhysPage(&virt_page_src, &phy_page_src);
  makeVirtPhysPage(&virt_page_dst, &phy_page_dst);
  makeVirtPhysPage(&virt_page_cb, &phy_page_cb);

  // write test bytes in to source page
  char *srcArray = static_cast<char *>(virt_page_src);
  srcArray[0] = 'h';
  srcArray[1] = 'e';
  srcArray[2] = 'l';
  srcArray[3] = 'l';
  srcArray[4] = 'o';
  srcArray[5] = '_';
  srcArray[6] = 'w';
  srcArray[7] = 'o';
  srcArray[8] = 'r';
  srcArray[9] = 'l';
  srcArray[10] = 'd';
  srcArray[11] = 0;

  // reset dma
  //reset_DMA(BUS_SOFT_RST_REG0);

  // DMA ///////////////
  void* offset_ptr = reinterpret_cast<void*> (reinterpret_cast<u64>(virt_page_cb) + 0x40);

  u32 stop_addr = 0xfffff800;

  sunxi_dma_lli *cb1 = reinterpret_cast<sunxi_dma_lli *>(virt_page_cb);
  cb1->cfg = (1<<0) | (1<<16); //SET src and destination to DRAM
  cb1->src = (u32)phy_page_src;
  cb1->dst = (u32)phy_page_dst;
  cb1->len = 12;
  cb1->para = NORMAL_WAIT;
  cb1->link = stop_addr;



  // follow block diagram
  // enable DMA
  // disable pause
  while( !(DMA_STA_REG == 0)){
    usleep(10000);
    std::cout << "print sleeping\r";
    reset_DMA(BUS_SOFT_RST_REG0);
  }

  #if 1
  // write channel descriptor
  DMA_SEC_REG[channel] = 1;

  cout << "----------------------  Write Descriptor  ----------------\n";
  DMA_DESC_ADDR_REG = (u32)(phy_page_cb);
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
  if (DMA_STA_REG == 0x20){
    std::cout << " Resume dma\n";
    DMA_PAU_REG = 0;
  }
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



  sleep(5);

  // check if msg arrived
  cout << "Send: " << srcArray << endl;
  cout << Hexdump(virt_page_src, 64) << std::endl;
  cout << "Send debug: " << static_cast<char *>(virt_page_dst) << endl;
  cout << Hexdump(virt_page_dst, 64) << std::endl;
  /////////////////////
  #endif

  freeVirtPhysPage(virt_page_src);
  freeVirtPhysPage(virt_page_dst);
  freeVirtPhysPage(virt_page_cb);

  return 0;
}
