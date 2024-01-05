#include "inet/inet.h"

void
ipv6::receive() {
    ipv6_hdr_t ih = (ipv6_hdr_t) this->hdr;

    switch (ih->next) {
    case IP_PROTO_IPV6_ICMP: {
        class icmpv6 ic;
        ic.set_buf(this->get_hdr() + this->get_hdr_len());
        if (dump_enabled)
            ic.dump();
        ic.receive();
    } break;
    default: {
        bp->push((buf_t) this->get_buf());
    } break;
    }
}
