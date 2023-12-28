#include <stdlib.h>
#include "inet/cppip.h"
#include "inet/stats.h"

eth::eth() {
    this->frame = NULL;
    this->framelen = 0;
}

uint16_t
eth::get_ethertype() {
    if (this->frame == NULL)
        return 0;

    eth_hdr_t eh = (eth_hdr_t) this->frame;
    return reverse_byte_order_short(eh->ethertype);
}

buf_t
eth::get_frame() {
    return this->frame;
}

void
eth::set_frame(buf_t frame) {
    this->frame = frame;
}

unsigned
eth::get_framelen() {
    return this->framelen;
}

void
eth::set_framelen(unsigned framelen) {
    this->framelen = framelen;
}
