#include "inet/udptab.h"
#include <stdio.h>
#include <stdlib.h>

class udptab udptab;

udptab::udptab() {
#if 0
    for (int i = 0; i < UDPTAB_ENTRIES; i++) {
        this->port[i] = 0;
        this->table[i] = new bufq(16, 64);
    }
#endif
}

void
udptab::dump() {
    for (int i = 0; i < UDPTAB_ENTRIES; i++)
        if (this->port[i] != 0 && this->table[i] != NULL) {
            printf("%5u ", this->port[i]);
            this->table[i]->dump();
            printf("\r\n");
        }
}

bufq_t
udptab::find_port(uint16_t port) {
    for (int i = 0; i < UDPTAB_ENTRIES; i++)
        if (this->port[i] == port)
            return this->table[i];
    return NULL;
}

bufq_t
udptab::alloc_port(uint16_t port) {
    for (int i = 0; i < UDPTAB_ENTRIES; i++)
        if (this->port[i] == 0) {
            bufq_t q = this->table[i];
            this->port[i] = port;
            return q;
        }
    return NULL;
}

void
udptab::free_port(uint16_t port) {
    for (int i = 0; i < UDPTAB_ENTRIES; i++)
        if (this->port[i] == port) {
            this->port[i] = 0;
            // TODO:
            // bufq_t q = this->table[i];
            // q->clear();
            return;
        }
}
