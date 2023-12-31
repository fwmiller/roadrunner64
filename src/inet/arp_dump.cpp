#include <stdio.h>
#include <stdlib.h>
#include "inet/inet.h"

void
arp::dump() {
    arp_hdr_t ah = (arp_hdr_t) this->get_hdr();

    switch (reverse_byte_order_short(ah->opcode)) {
    case ARP_OP_REQ:
        printf("arp who has ");
        dump_ipaddr(reverse_byte_order_long(ah->tpa));
        printf(" tell ");
        dump_ipaddr(reverse_byte_order_long(ah->spa));
        break;
    case ARP_OP_REP:
        printf("arp ");
        dump_ipaddr(reverse_byte_order_long(ah->spa));
        printf(" is at ");
        dump_ethaddr(ah->sha);
        break;
    case RARP_OP_REQ:
        printf("rarp who has ");
        break;
    case RARP_OP_REP:
        printf("rarp is at ");
        break;
    default:
        printf("UNKNOWN");
        break;
    }
    printf("\r\n");

    printf(" hw 0x%04x (", reverse_byte_order_short(ah->hw));
    switch (reverse_byte_order_short(ah->hw)) {
    case ARP_HW_ETH:
        printf("Ethernet");
        break;
    case ARP_HW_802:
        printf("IEEE 802");
        break;
    case ARP_HW_SER:
        printf("Serial");
        break;
    default:
        printf("UNKNOWN");
        break;
    }
    printf(") proto 0x%04x (", reverse_byte_order_short(ah->proto));
    dump_ethertype(reverse_byte_order_short(ah->proto));
    printf(")\r\n");
    printf(" hw addr len %u proto addr len %u opcode 0x%04x (",
           ah->hw_addr_len, ah->proto_addr_len,
           reverse_byte_order_short(ah->opcode));
    switch (reverse_byte_order_short(ah->opcode)) {
    case ARP_OP_REQ:
        printf("ARP request");
        break;
    case ARP_OP_REP:
        printf("ARP reply");
        break;
    case RARP_OP_REQ:
        printf("RARP request");
        break;
    case RARP_OP_REP:
        printf("RARP reply");
        break;
    default:
        printf("UNKNOWN");
        break;
    }
    printf(")\r\n");
    printf(" sha ");
    dump_ethaddr((uint8_t *) &(ah->sha));
    printf(" spa 0x%08x (", reverse_byte_order_long(ah->spa));
    dump_ipaddr(reverse_byte_order_long(ah->spa));
    printf(")\r\n");
    printf(" tha ");
    dump_ethaddr((uint8_t *) &(ah->tha));
    printf(" tpa 0x%08x (", reverse_byte_order_long(ah->tpa));
    dump_ipaddr(reverse_byte_order_long(ah->tpa));
    printf(")\r\n");
}
