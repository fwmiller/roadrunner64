#include <stdio.h>
#include <stdlib.h>
#include "inet/inet.h"
#include "inet/stats.h"

void
ipv4::receive() {
    switch (this->get_protocol()) {
    case IP_PROTO_ICMP: {
        stats.inc_icmp_count();

        class icmp icmp;
        icmp.set_buf(this->get_buf());
        icmp.set_hdr(this->get_hdr() + this->get_hdr_len());
#if _DEBUG_INET
        if (dump_enabled)
            icmp.dump();
#endif
        icmp.receive();
    } break;
    case IP_PROTO_UDP: {
        stats.inc_udp_count();

        class udp udp;
        udp.set_buf(this->get_buf());
        udp.set_hdr(this->get_hdr() + this->get_hdr_len());
#if _DEBUG_INET
        if (dump_enabled)
            udp.dump();
#endif
        udp.receive();
    } break;
    case IP_PROTO_TCP: {
        stats.inc_tcp_count();
        bp->push((buf_t) this->get_buf());
    } break;
    default: {
        bp->push((buf_t) this->get_buf());
    } break;
    }
}
