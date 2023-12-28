#ifndef __IEEE_802_3_H
#define __IEEE_802_3_H

#include <stdint.h>
#include "cppip.h"

//
// IEEE 802.2 header overlay
//
struct ieee802_2_hdr {
    uint8_t dsap;
    uint8_t ssap;
    uint8_t control;
    uint8_t ext_control;
} __attribute__((packed));

typedef struct ieee802_2_hdr *ieee802_2_hdr_t;

//
// IEEE 802.2 header processing
//
class ieee802_2 {
private:
    buf_t hdr;

public:
    ieee802_2();
    buf_t get_hdr();
    void set_hdr(buf_t hdr);
    void receive();
    void dump();
};

#endif
