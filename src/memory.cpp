#include "memory.hpp"

using namespace std;

static int memfd = -1;

void open_devmem() {
  if (memfd == -1) {
    std::cout << "open /dev/mem\n";
    memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (memfd < 0) {
      cout << "Failed to open /dev/mem (run as root)\n";
      exit(1);
    }
  }
}

void close_devmem() {
  std::cout << "Closing /dev/mem\n";
  close(memfd);
  memfd = -1;
}

u32 *mapPeripheral(u32 addr) {
  void *mapped =
      mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, addr);
  if (mapped == MAP_FAILED) {
    cout << "failed to map memory\n";
    exit(1);
  } else {
    printf("mapped %p\n", mapped);
  }
  std::cout << "mapping page\n";
  return static_cast<u32 *>(mapped);
}

void unmapPeripheral(u32 *address) {
  auto status = munmap(address, PAGE_SIZE);
  std::cout << "unmapping " << status << std::endl;
}

void makeVirtPhysPage(void **virtAddr, void **physAddr) {
  // allocate 1 page on RAM
  *virtAddr = static_cast<u8 *>(valloc(PAGE_SIZE));

  // force page into RAM and then lock it there
  static_cast<u8 *>(*virtAddr)[0] = 1;

  // lock page
  mlock(*virtAddr, PAGE_SIZE);

  // write zeros to page
  memset(*virtAddr, 0, PAGE_SIZE);

  // Determine the phyiscal address for this page
  uint64_t pageInfo;
  int file = open("/proc/self/pagemap", 'r');
  off_t offset = reinterpret_cast<off_t>(virtAddr) / PAGE_SIZE * 8;

  lseek(file, offset, SEEK_SET);
  read(file, &pageInfo, 8);

  *physAddr = reinterpret_cast<u8 *>(pageInfo * PAGE_SIZE);

  printf("makeVirtPhsPage: %p -> %p\n", *virtAddr, *physAddr);
}

void freeVirtPhysPage(void *virtAddr) {
  munlock(virtAddr, PAGE_SIZE);
  free(virtAddr);
}

u32 address_to_value(void *v) {
  return reinterpret_cast<u64>(v) & 0xffffffff;
}

u32 *value_to_address(u32 v) { return reinterpret_cast<u32 *>(v); }