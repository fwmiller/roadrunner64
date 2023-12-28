#ifndef __MEM_H
#define __MEM_H

#include <stdint.h>

void mem_init();
uint8_t* mem_alloc(uint32_t size);

#endif
