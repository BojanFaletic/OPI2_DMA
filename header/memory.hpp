#ifndef MEMORY_HPP__
#define MEMORY_HPP__

#include <fcntl.h>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstring>

#include "constants.hpp"

const int PAGE_SIZE = 4096;

void close_devmem();
void open_devmem();
u32 *mapPeripheral(u32 addr);
void unmapPeripheral(u32 *address);
void makeVirtPhysPage(void **virtAddr, void **physAddr);
void freeVirtPhysPage(void *virtAddr);
u32 address_to_value(void *v);
u32 *value_to_address(u32 v);
#endif