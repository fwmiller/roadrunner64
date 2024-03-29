#include <stdio.h>
#include <stdlib.h>
#include "inet/inet.h"

icmpv6::icmpv6() {
    this->buf = NULL;
    this->hdr = NULL;
}

buf_t
icmpv6::get_buf() {
    return this->buf;
}

void
icmpv6::set_buf(buf_t buf) {
    this->buf = buf;
}

uint8_t*
icmpv6::get_hdr() {
    return this->hdr;
}

void
icmpv6::set_hdr(uint8_t* hdr) {
    this->hdr = hdr;
}

void
icmpv6::receive() {
    bp->push((buf_t) this->get_buf());
}

void
icmpv6::dump() {
    if (this->buf == NULL)
        return;

    icmpv6_hdr_t ih = (icmpv6_hdr_t) this->buf;

    printf("icmpv6 type 0x%02x (", ih->type);
    dump_icmp_type(ih->type);
    printf(") code 0x%02x chksum 0x%04x\r\n", ih->code,
           reverse_byte_order_short(ih->cksum));
}
