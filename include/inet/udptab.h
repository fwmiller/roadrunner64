#ifndef __UDPTAB_H
#define __UDPTAB_H

#include "buf.h"

static const int UDPTAB_ENTRIES = 16;

extern class udptab udptab;

//
// UDP table
//
class udptab {
private:
    uint16_t port[UDPTAB_ENTRIES];
    bufq_t table[UDPTAB_ENTRIES];

public:
    udptab();
    void dump();
    bufq_t find_port(uint16_t port);
    bufq_t alloc_port(uint16_t port);
    void free_port(uint16_t port);
};

#endif
