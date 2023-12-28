#ifndef __IPV4_H
#define __IPV4_H

#include <stdint.h>
#include "cppip.h"

//
// IPv4 header overlay
//
struct ipv4_hdr {
    uint8_t version;
    uint8_t tos;
    uint16_t len;
    uint16_t id;
    uint16_t frag;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t hdr_cksum;
    uint32_t src;
    uint32_t dst;
} __attribute__((packed));

typedef struct ipv4_hdr *ipv4_hdr_t;

//
// IPv4 header processing
//
class ipv4 {
private:
    buf_t hdr;
    uint8_t get_hdr_len();
    uint8_t get_protocol();

public:
    ipv4();
    buf_t get_hdr();
    void set_hdr(buf_t hdr);
    void receive();
    void dump();
};

#endif
