#include <stdio.h>
#include <stdlib.h>
#include "inet/inet.h"

void
ipv4::dump() {
    if (this->hdr == NULL)
        return;

    ipv4_hdr_t ih = (ipv4_hdr_t) this->hdr;

    printf("ipv4 ver %u hdr len %u tos 0x%02x", (ih->version >> 4) & 0x0f,
           this->get_hdr_len(), ih->tos);

    if (ih->tos) {
        uint8_t prec = (ih->tos >> 5) & 0x03;
        uint8_t delay = (ih->tos >> 4) & 0x01;
        uint8_t throughput = (ih->tos >> 3) & 0x01;
        uint8_t reliability = (ih->tos >> 2) & 0x01;
        uint8_t cost = (ih->tos >> 1) & 0x01;

        switch (prec) {
        case 1:
            printf(" PRIORITY");
            break;
        case 2:
            printf(" IMMEDIATE");
            break;
        case 3:
            printf(" FLASH");
            break;
        case 4:
            printf(" FLASH-OVERRIDE");
            break;
        case 5:
            printf(" CRITICAL");
            break;
        case 6:
            printf(" INET-CTL");
            break;
        case 7:
            printf(" NET-CTL");
            break;
        }
        if (delay)
            printf(" MIN_DELAY");
        if (throughput)
            printf(" MAX_THROUGHPUT");
        if (reliability)
            printf(" MAX_RELIABILITY");
        if (cost)
            printf(" MIN_COST");
    }
    printf(" len %u id 0x%04x\r\n", reverse_byte_order_short(ih->len),
           reverse_byte_order_short(ih->id));

    uint16_t frag = reverse_byte_order_short(ih->frag);
    printf(" frag 0x%04x", frag);
    uint16_t flags = frag >> 13;
    if (flags) {
        printf(" (");
        if (flags & 0x01)
            printf("MF");
        if (flags & 0x02)
            printf("DF");
        printf(")");
    }
    printf(" offset %u ttl %u protocol 0x%02x (",
           reverse_byte_order_short(ih->frag) & 0x1fff, ih->ttl,
           ih->protocol);
    dump_ipproto(ih->protocol);
    printf(") hdr cksum 0x%04x\r\n", ih->hdr_cksum);
    printf(" dst ");
    dump_ipaddr(reverse_byte_order_long(ih->dst));
    printf(" src ");
    dump_ipaddr(reverse_byte_order_long(ih->src));
    printf("\r\n");
}
