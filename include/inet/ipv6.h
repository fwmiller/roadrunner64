#ifndef __IPV6_H
#define __IPV6_H

#include <stdint.h>
#include "cppip.h"

//
// IPv6 header overlay
//
struct ipv6_hdr {
    uint8_t ver_class;
    uint8_t class_flow;
    uint16_t flow_label;
    uint16_t len;
    uint8_t next;
    uint8_t hop_lmt;
    uint8_t src[16];
    uint8_t dst[16];
} __attribute__((packed));

typedef struct ipv6_hdr *ipv6_hdr_t;

//
// IPv6 header processing
//
class ipv6 {
private:
    buf_t hdr;

public:
    ipv6();
    buf_t get_hdr();
    void set_hdr(buf_t hdr);
    void receive();
    void dump();
};

#endif
