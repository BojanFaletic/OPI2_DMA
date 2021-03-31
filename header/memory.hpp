#ifndef MEMORY_HPP__
#define MEMORY_HPP__

#include <stdint.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>

#include "constants.hpp"

#define u32 uint32_t
const int PAGE_SIZE = 4096;

/*
int open_devmem();
volatile uint32_t *mapPeripheral(int memfd, int addr);
void makeVirtPhysPage(void *virtAddr, void *physAddr);
void freeVirtPhysPare(void *virtAddr);
*/

#endif