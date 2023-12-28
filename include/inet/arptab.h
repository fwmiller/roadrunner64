#ifndef __ARPTAB_H
#define __ARPTAB_H

#include <stdint.h>
#include "cppip.h"

static const int ARPTAB_ENTRIES = 16;

//
// ARP table entry
//
class arptab_entry {
private:
    uint8_t ha[ETH_ADDR_LEN];  // Hardware address (Ethernet)
    uint32_t pa;               // Protocol address (IPv4)

public:
    arptab_entry();
    uint8_t *get_ha();
    void set_ha(uint8_t *ha);
    uint32_t get_pa();
    void set_pa(uint32_t pa);
};

typedef class arptab_entry *arptab_entry_t;

//
// ARP table
//
class arptab {
private:
    class arptab_entry table[ARPTAB_ENTRIES];

public:
    arptab();
    void dump();
    int add_entry(uint32_t pa, uint8_t *ha);
    arptab_entry_t find_ha(uint8_t *ha);
    arptab_entry_t find_pa(uint32_t pa);
};

extern class arptab arptab;

#endif
