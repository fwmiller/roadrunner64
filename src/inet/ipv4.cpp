#include <stdio.h>
#include <stdlib.h>
#include "inet/inet.h"
#include "inet/stats.h"

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

void
ipv4::receive() {
    switch (this->get_protocol()) {
    case IP_PROTO_ICMP: {
        stats.inc_icmp_count();

        class icmp icmp;
        icmp.set_buf(this->get_buf());
        icmp.set_hdr(this->get_hdr() + this->get_hdr_len());
        if (dump_enabled)
            icmp.dump();
        icmp.receive();
    } break;
    case IP_PROTO_UDP: {
        stats.inc_udp_count();

        class udp udp;
        udp.set_buf(this->get_buf());
        udp.set_hdr(this->get_hdr() + this->get_hdr_len());
        if (dump_enabled)
            udp.dump();
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
