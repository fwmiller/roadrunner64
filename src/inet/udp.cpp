#include "inet/udp.h"
#include <stdlib.h>

udp::udp() {
    this->buf = NULL;
    this->hdr = NULL;
}

buf_t
udp::get_buf() {
    return this->buf;
}

void
udp::set_buf(buf_t buf) {
    this->buf = buf;
}

uint8_t*
udp::get_hdr() {
    return this->hdr;
}

void
udp::set_hdr(uint8_t* hdr) {
    this->hdr = hdr;
}
