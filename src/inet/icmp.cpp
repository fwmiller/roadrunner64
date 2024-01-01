#include "inet/icmp.h"
#include <stdlib.h>

icmp::icmp() {
    return;
}

buf_t
icmp::get_buf() {
    return this->buf;
}

void
icmp::set_buf(buf_t buf) {
    this->buf = buf;
}

uint8_t *
icmp::get_hdr() {
    return this->hdr;
}

void
icmp::set_hdr(uint8_t *hdr) {
    this->hdr = hdr;
}

void
icmp::receive() {
    bp->push((buf_t) this->get_buf());
}
