#include <stdio.h>
#include <stdlib.h>
#include "inet/inet.h"

void
ipv6::dump() {
    ipv6_hdr_t ih = (ipv6_hdr_t) this->get_hdr();

    printf("ipv6 ver %u", (ih->ver_class >> 4) & 0x0f);

    uint8_t traffic_class =
        ((ih->ver_class & 0x0f) << 2) | ((ih->class_flow & 0xc0) >> 6);
    printf(" class 0x%02x", traffic_class);
    uint8_t ecn = (ih->class_flow >> 4) & 0x03;
    printf(" ecn 0x%02x", ecn);

    uint32_t flow = ((ih->class_flow & 0x0f) << 16) |
                    reverse_byte_order_short(ih->flow_label);
    printf(" flow 0x%08x", flow);

    uint32_t len = reverse_byte_order_short(ih->len);
    printf(" payload len %u", len);

    printf("\r\n");

    printf(" next 0x%04x (", ih->next);
    dump_ipproto(ih->next);
    printf(") hop limit %u\r\n", ih->hop_lmt);

    printf(" dst ");
    dump_ipv6addr((uint8_t *) &(ih->dst));

    printf("\r\n src ");
    dump_ipv6addr((uint8_t *) &(ih->src));

    printf("\r\n");
}
