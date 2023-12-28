#include <stdlib.h>
#include <sys/mem.h>

/* Heap starts at 2 MB for the moment */
#define HEAP_START 0x200000

static uint8_t *heap = NULL;

void
mem_init() {
    heap = (uint8_t *) HEAP_START;
}

uint8_t *
mem_alloc(uint32_t size) {
    uint8_t *ptr = heap;

    /* TODO: size should be at least 64-bit aligned */
    heap += size;

    return ptr;
}
