#ifndef __ICMPV6_H
#define __ICMPV6_H

#include <stdint.h>
#include "cppip.h"

static const uint8_t ICMP_TYPE_DEST_UNRCH = 1;
static const uint8_t ICMP_TYPE_PKT_TOO_BIG = 2;
static const uint8_t ICMP_TYPE_TIME_EXCEEDED = 3;
static const uint8_t ICMP_TYPE_PARAM_PROB = 4;
static const uint8_t ICMP_TYPE_ECHO_REQ = 128;
static const uint8_t ICMP_TYPE_ECHO_REP = 129;
static const uint8_t ICMP_TYPE_MLQ = 130;
static const uint8_t ICMP_TYPE_MLR = 131;
static const uint8_t ICMP_TYPE_MLD = 132;
static const uint8_t ICMP_TYPE_ROUTER_SOL = 133;
static const uint8_t ICMP_TYPE_ROUTER_AD = 134;
static const uint8_t ICMP_TYPE_NEIGHBOR_SOL = 135;
static const uint8_t ICMP_TYPE_NEIGHBOR_AD = 136;
static const uint8_t ICMP_TYPE_REDIRECT = 137;
static const uint8_t ICMP_TYPE_ROUTER_RENUM = 138;
static const uint8_t ICMP_TYPE_NODE_INFO_QUERY = 139;
static const uint8_t ICMP_TYPE_NODE_INFO_RESP = 140;
static const uint8_t ICMP_TYPE_INV_NEIGHBOR_SOL = 141;
static const uint8_t ICMP_TYPE_INV_NEIGHBOR_AD = 142;
static const uint8_t ICMP_TYPE_MLDR = 143;
static const uint8_t ICMP_TYPE_HOME_ADDR_DISC_REQ = 144;
static const uint8_t ICMP_TYPE_HOME_ADDR_DISC_REP = 145;
static const uint8_t ICMP_TYPE_MOBILE_PREFIX_SOL = 146;
static const uint8_t ICMP_TYPE_MOBILE_PREFIX_AD = 147;
static const uint8_t ICMP_TYPE_CERT_PATH_SOL = 148;
static const uint8_t ICMP_TYPE_CERT_PATH_AD = 149;
static const uint8_t ICMP_TYPE_MCAST_ROUTER_AD = 151;
static const uint8_t ICMP_TYPE_MCAST_ROUTER_SOL = 152;
static const uint8_t ICMP_TYPE_MCAST_ROUTER_TERM = 153;
static const uint8_t ICMP_TYPE_RPL_CTL = 155;

//
// ICMPv6 header overlay
//
struct icmpv6_hdr {
    uint8_t type;
    uint8_t code;
    uint16_t cksum;
} __attribute__((packed));

typedef struct icmpv6_hdr *icmpv6_hdr_t;

//
// ICMPv6 header processing
//
class icmpv6 {
private:
    buf_t buf;

public:
    icmpv6();
    buf_t get_buf();
    void set_buf(buf_t buf);
    void receive();
    void dump();
};

#endif
