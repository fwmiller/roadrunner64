#include <stdlib.h>
#include "inet/inet.h"

ipv4::ipv4() {
    this->hdr = NULL;
    this->buf = NULL;
}

buf_t
ipv4::get_buf() {
    return this->buf;
}

void
ipv4::set_buf(buf_t buf) {
    this->buf = buf;
}

uint8_t *
ipv4::get_hdr() {
    return this->hdr;
}

void
ipv4::set_hdr(uint8_t *hdr) {
    this->hdr = hdr;
}

uint8_t
ipv4::get_hdr_len() {
    if (this->hdr == NULL)
        return 0;

    ipv4_hdr_t ih = (ipv4_hdr_t) this->hdr;
    return (ih->version & 0x0f) * 32 / 8;
}

uint8_t
ipv4::get_protocol() {
    if (this->hdr == NULL)
        return 0;

    ipv4_hdr_t ih = (ipv4_hdr_t) this->hdr;
    return ih->protocol;
}
