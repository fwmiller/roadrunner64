#include <stdio.h>
#include <stdlib.h>
#include "inet/inet.h"

void
eth::dump() {
    eth_hdr_t eh = (eth_hdr_t) this->get_frame();

    printf("ethernet dst ");
    dump_ethaddr(eh->dst);
    printf(" src ");
    dump_ethaddr(eh->src);

    uint16_t ethertype = reverse_byte_order_short(eh->ethertype);
    if (ethertype < ETH_MTU_SIZE)
        printf(" len %u (802.3", ethertype);
    else {
        printf(" type 0x%04x (", ethertype);
        dump_ethertype(ethertype);
    }
    printf(")\r\n");
}
