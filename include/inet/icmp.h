#ifndef __ICMP_H
#define __ICMP_H

#include <stdint.h>
#include "cppip.h"

static const uint8_t ICMPTYPE_ECHO_REPLY = 0;
static const uint8_t ICMPTYPE_DEST_UNREACH = 3;
static const uint8_t ICMPTYPE_SOURCE_QUENCH = 4;
static const uint8_t ICMPTYPE_REDIRECT = 5;
static const uint8_t ICMPTYPE_ALT_HOST_ADDRESS = 6;
static const uint8_t ICMPTYPE_ECHO = 8;
static const uint8_t ICMPTYPE_ROUTER_ADVERTISEMENT = 9;
static const uint8_t ICMPTYPE_ROUTER_SELECTION = 10;
static const uint8_t ICMPTYPE_TIME_EXCEEDED = 11;
static const uint8_t ICMPTYPE_PARAM_PROBLEM = 12;
static const uint8_t ICMPTYPE_TIMESTAMP = 13;
static const uint8_t ICMPTYPE_TIMESTAMP_REPLY = 14;
static const uint8_t ICMPTYPE_INFO_REQUEST = 15;
static const uint8_t ICMPTYPE_INFO_REPLY = 16;
static const uint8_t ICMPTYPE_ADDR_MASK_REQUEST = 17;
static const uint8_t ICMPTYPE_ADDR_MASK_REPLY = 18;
static const uint8_t ICMPTYPE_TRACEROUTE = 30;
static const uint8_t ICMPTYPE_DGRAM_CONV_ERROR = 31;
static const uint8_t ICMPTYPE_MOBILE_HOST_REDIRECT = 32;
static const uint8_t ICMPTYPE_IPV6_WHERE_ARE_YOU = 33;
static const uint8_t ICMPTYPE_IPV6_I_AM_HERE = 34;
static const uint8_t ICMPTYPE_MOBILE_REG_REQUEST = 35;
static const uint8_t ICMPTYPE_MOBILE_REG_REPLY = 36;
static const uint8_t ICMPTYPE_DOMAIN_NAME_REQUEST = 37;
static const uint8_t ICMPTYPE_DOMAIN_NAME_REPLY = 38;
static const uint8_t ICMPTYPE_SKIP = 39;
static const uint8_t ICMPTYPE_PHOTURIS = 40;
static const uint8_t ICMPTYPE_EXT_ECHO_REQUEST = 42;
static const uint8_t ICMPTYPE_EXT_ECHO_REPLY = 43;

//
// ICMPv4 header overlay
//
struct icmp_hdr {
    uint8_t type;
    uint8_t code;
    uint16_t cksum;
} __attribute__((packed));

typedef struct icmp_hdr *icmp_hdr_t;

//
// ICMPv4 header processing
//
class icmp {
private:
    buf_t buf;

public:
    icmp();
    buf_t get_buf();
    void set_buf(buf_t buf);
    void receive();
    void dump();
};

#endif
