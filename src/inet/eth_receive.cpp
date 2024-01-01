#include "inet/inet.h"
#include "inet/stats.h"

void
eth::receive() {
    uint16_t ethertype;
    buf_t hdr = this->get_frame() + sizeof(struct eth_hdr);

    ethertype = this->get_ethertype();
    if (ethertype < ETH_MTU_SIZE) {
        stats.inc_ieee802_2_count();

        class ieee802_2 llc;
        llc.set_buf(this->get_buf());
        llc.set_hdr(hdr);
        if (dump_enabled)
            llc.dump();
        llc.receive();
        return;
    }
    stats.inc_eth_count();

    switch (ethertype) {
    case ETHERTYPE_ARP:
    case ETHERTYPE_RARP: {
        if (ethertype == ETHERTYPE_ARP)
            stats.inc_arp_count();
        else if (ethertype == ETHERTYPE_RARP)
            stats.inc_rarp_count();

        class arp arp;
        arp.set_buf(this->get_buf());
        arp.set_hdr(hdr);
#if _DEBUG_ARP
        if (dump_enabled)
            arp.dump();
#endif
        arp.receive();
    } break;
    case ETHERTYPE_IPV4: {
        stats.inc_ipv4_count();

        class ipv4 ipv4;
        ipv4.set_buf(this->get_buf());
        ipv4.set_hdr(hdr);
        if (dump_enabled)
            ipv4.dump();
        ipv4.receive();
    } break;
    case ETHERTYPE_IPV6: {
        stats.inc_ipv6_count();

        class ipv6 ipv6;
        ipv6.set_buf(this->get_buf());
        ipv6.set_hdr(hdr);
        if (dump_enabled)
            ipv6.dump();
        ipv6.receive();
    } break;
    default: {
        bp->push((buf_t) this->get_buf());
    } break;
    }
}
