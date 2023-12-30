#ifndef __ETHERNET_H
#define __ETHERNET_H

#include "inet/inet.h"

static const unsigned ETH_MTU_SIZE = 1536;

//
// Ethernet header overlay
//
struct eth_hdr {
    uint8_t dst[ETH_ADDR_LEN];
    uint8_t src[ETH_ADDR_LEN];
    uint16_t ethertype;
} __attribute__((packed));

typedef struct eth_hdr *eth_hdr_t;

//
// Ethernet header processing
//
class eth {
private:
    buf_t buf;
    uint8_t *frame;
    unsigned framelen;
    uint16_t get_ethertype();

public:
    eth();
    buf_t get_buf();
    void set_buf(buf_t buf);
    uint8_t *get_frame();
    void set_frame(uint8_t *frame);
    unsigned get_framelen();
    void set_framelen(unsigned framelen);
    void receive();
    void send();
    void dump();
};

#endif
