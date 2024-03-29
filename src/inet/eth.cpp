#include <stdlib.h>
#include "inet/inet.h"
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
eth::get_buf() {
    return this->buf;
}

void
eth::set_buf(buf_t buf) {
    this->buf = buf;
}

uint8_t*
eth::get_frame() {
    return this->frame;
}

void
eth::set_frame(uint8_t* frame) {
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
