#include <stdio.h>
#include <stdlib.h>
#include "inet/inet.h"
#include "inet/udptab.h"

void
udp::receive() {
    udp_hdr_t uh = (udp_hdr_t) this->get_hdr();

    uint16_t port = reverse_byte_order_short(uh->dst);
#if _DEBUG_INET
    printf("udp::receive: port %u\r\n", port);
#endif
    class bufq *q = ut->find_port(port);
    if (q == NULL) {
        // No input queue open drop packet data

        // TODO: for fun - just allocating a UDP queue for any incoming
        // UDP packet until the UDP table is filled up...
        q = ut->alloc_port(port);
        if (q == NULL) {
#if _DEBUG_INET
            printf("udp::receive: allocate port queue failed\r\n");
#endif
            bp->push((buf_t) this->get_buf());
            return;
        }
    }
    int len = reverse_byte_order_short(uh->len);
    q->append(this->buf + sizeof(struct udp_hdr), len);

    printf("udp port %u rcvd %d bytes\r\n", port, len);
    // q->dump_contents();
    // printf("\r\n");
}
