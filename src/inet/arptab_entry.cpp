#include <string.h>
#include "inet/arptab.h"

arptab_entry::arptab_entry() {
    memset(this->ha, 0, ETH_ADDR_LEN);
    this->pa = 0;
}

uint8_t *
arptab_entry::get_ha() {
    return this->ha;
}

void
arptab_entry::set_ha(uint8_t *ha) {
    memcpy(this->ha, ha, ETH_ADDR_LEN);
}

uint32_t
arptab_entry::get_pa() {
    return this->pa;
}

void
arptab_entry::set_pa(uint32_t pa) {
    this->pa = pa;
}
