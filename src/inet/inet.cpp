#include "inet/inet.h"
#include <stdlib.h>

// The global buffer pool
bufpool_t bp = NULL;

uint16_t
reverse_byte_order_short(uint16_t x) {
    return (((x & 0xff) << 8) | ((x & 0xff00) >> 8));
}

uint32_t
reverse_byte_order_long(uint32_t x) {
    return (((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) |
            ((x & 0xff000000) >> 24));
}

void
inet_init() {
    bp = new bufpool(32, 1518);
}
