#include <stdlib.h>
#include "inet/inet.h"

ipv6::ipv6() {
    this->hdr = NULL;
    this->buf = NULL;
}

buf_t
ipv6::get_buf() {
    return this->buf;
}

void
ipv6::set_buf(buf_t buf) {
    this->buf = buf;
}

uint8_t*
ipv6::get_hdr() {
    return this->hdr;
}

void
ipv6::set_hdr(uint8_t* hdr) {
    this->hdr = hdr;
}

uint8_t
ipv6::get_hdr_len() {
    // TODO: Fixme
    return 0;
}
