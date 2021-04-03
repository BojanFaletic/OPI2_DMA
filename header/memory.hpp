#pragma once

#include "constants.hpp"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

constexpr u32 PAGE_SIZE = 4096;

void close_devmem();
void open_devmem();
u32 *mapPeripheral(u32 addr);
void unmapPeripheral(u32 *address);
void makeVirtPhysPage(void **virtAddr, void **physAddr);
void freeVirtPhysPage(void *virtAddr);
u32 address_to_value(void *v);
u32 *value_to_address(u32 v);