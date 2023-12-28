#ifndef __UDP_H
#define __UDP_H

#include <stdint.h>
#include "cppip.h"

//
// UDP header overlay
//
struct udp_hdr {
    uint16_t src;
    uint16_t dst;
    uint16_t len;
    uint16_t cksum;
} __attribute__((packed));

typedef struct udp_hdr *udp_hdr_t;

//
// UDP header processing
//
class udp {
private:
    buf_t buf;

public:
    udp();
    buf_t get_buf();
    void set_buf(buf_t buf);
    void receive();
    void dump();
};

#endif
