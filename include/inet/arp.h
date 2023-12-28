#ifndef __ARP_H
#define __ARP_H

#include "cppip.h"

const static uint16_t ARP_HW_ETH = 0x0001;
const static uint16_t ARP_HW_802 = 0x0006;
const static uint16_t ARP_HW_SER = 0x0014;

const static uint16_t ARP_OP_REQ = 0x0001;
const static uint16_t ARP_OP_REP = 0x0002;
const static uint16_t RARP_OP_REQ = 0x0003;
const static uint16_t RARP_OP_REP = 0x0004;

//
// ARP header overlay
//
struct arp_hdr {
    uint16_t hw;
    uint16_t proto;
    uint8_t hw_addr_len;
    uint8_t proto_addr_len;
    uint16_t opcode;
    uint8_t sha[ETH_ADDR_LEN];
    uint32_t spa;
    uint8_t tha[ETH_ADDR_LEN];
    uint32_t tpa;
} __attribute__((packed));

typedef struct arp_hdr *arp_hdr_t;

//
// ARP header processing
//
class arp {
private:
    buf_t hdr;

public:
    arp();
    buf_t get_hdr();
    void set_hdr(buf_t hdr);
    void receive();
    void dump();
    void generate(uint8_t *hdr, uint16_t hw, uint16_t proto,
                  uint8_t hw_addr_len, uint8_t proto_addr_len,
                  uint16_t opcode, uint8_t *sha, uint32_t spa, uint8_t *tha,
                  uint32_t tpa);
};

#endif
