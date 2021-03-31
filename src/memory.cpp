#include "memory.hpp"

using namespace std;

int open_devmem()
{
    int memfd = open("/dev/mem", O_RDWR | O_SYNC);
    if (memfd < 0)
    {
        cout << "Failed to open /dev/mem (run as root)\n";
        exit(1);
    }
    return memfd;
}

volatile uint32_t *mapPeripheral(int memfd, int addr)
{
    void *mapped = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE,
                        MAP_SHARED, memfd, addr);
    if (mapped == MAP_FAILED)
    {
        cout << "failed to map memory\n";
        exit(1);
    }
    else
    {
        printf("mapped %p\n", mapped);
    }
    return static_cast<volatile uint32_t *>(mapped);
}

void makeVirtPhysPage(void *virtAddr, void *physAddr)
{
    // allocate 1 page on RAM
    virtAddr = static_cast<u32 *>(valloc(PAGE_SIZE));

    // force page into RAM and then lock it there
    static_cast<u32 *>(virtAddr)[0] = 1;

    mlock(virtAddr, PAGE_SIZE);

    // write zeros to page
    for (u32 i = 0; i < PAGE_SIZE / sizeof(u32); i++)
    {
        static_cast<u32 *>(virtAddr)[i] = 0;
    }

    // Determine the phyiscal address for this page
    uint64_t pageInfo;
    int file = open("/proc/self/pagemap", 'r');
    size_t offset = reinterpret_cast<size_t>(virtAddr) / PAGE_SIZE * 8;

    lseek(file, offset, SEEK_SET);
    read(file, &pageInfo, 8);

    physAddr = reinterpret_cast<void *>(pageInfo * PAGE_SIZE);

    printf("makeVirtPhsPage: %p -> %p\n", virtAddr, physAddr);
}

void freeVirtPhysPage(void *virtAddr)
{
    munlock(virtAddr, PAGE_SIZE);
    free(virtAddr);
}