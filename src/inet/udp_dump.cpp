#include <stdio.h>
#include <stdlib.h>
#include "inet/inet.h"

void
udp::dump() {
    if (this->buf == NULL)
        return;

    udp_hdr_t uh = (udp_hdr_t) this->buf;

    printf("udp dst %u src %u len %u cksum 0x%04x\r\n",
           reverse_byte_order_short(uh->dst),
           reverse_byte_order_short(uh->src),
           reverse_byte_order_short(uh->len),
           reverse_byte_order_short(uh->cksum));
}
