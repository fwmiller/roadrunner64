#ifndef __CPPIP_STATS
#define __CPPIP_STATS

class cppip_stats {
private:
    unsigned frame_count;
    unsigned eth_count;
    unsigned ieee802_2_count;
    unsigned arp_count;
    unsigned rarp_count;
    unsigned ipv4_count;
    unsigned ipv6_count;
    unsigned icmp_count;
    unsigned udp_count;
    unsigned tcp_count;

public:
    cppip_stats();
    unsigned get_frame_count();
    void set_frame_count(unsigned frame_count);
    void inc_frame_count();
    unsigned get_eth_count();
    void set_eth_count(unsigned eth_count);
    void inc_eth_count();
    unsigned get_ieee802_2_count();
    void set_ieee802_2_count(unsigned ieee802_2_count);
    void inc_ieee802_2_count();
    unsigned get_arp_count();
    void set_arp_count(unsigned arp_count);
    void inc_arp_count();
    unsigned get_rarp_count();
    void set_rarp_count(unsigned rarp_count);
    void inc_rarp_count();
    unsigned get_ipv4_count();
    void set_ipv4_count(unsigned ipv4_count);
    void inc_ipv4_count();
    unsigned get_ipv6_count();
    void set_ipv6_count(unsigned ipv6_count);
    void inc_ipv6_count();
    unsigned get_icmp_count();
    void set_icmp_count(unsigned icmp_count);
    void inc_icmp_count();
    unsigned get_udp_count();
    void set_udp_count(unsigned udp_count);
    void inc_udp_count();
    unsigned get_tcp_count();
    void set_tcp_count(unsigned tcp_count);
    void inc_tcp_count();
};

extern class cppip_stats stats;

#endif
