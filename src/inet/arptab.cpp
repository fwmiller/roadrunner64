#include "inet/arptab.h"
#include <stdio.h>
#include <string.h>

class arptab arptab;
class arptab_entry *my_addr;

arptab::arptab() {
    memset(this->table, 0, sizeof(class arptab));
    my_addr = &(this->table[0]);
}

void
arptab::dump() {
    //
    // TODO: Need to lock the ARP table during this operation
    //
    for (int i = 0; i < ARPTAB_ENTRIES; i++) {
        arptab_entry_t ae = (arptab_entry_t) & (this->table[i]);
        if (ae->get_pa() != 0) {
            char s[16];
            int i, len;

            memset(s, 0, 16);

            dump_ipaddr_str(reverse_byte_order_long(ae->get_pa()), s);
            printf("%s", s);
            len = 16 - strlen(s);
            for (i = 0; i < len; i++)
                printf(" ");

            printf(" ");
            dump_ethaddr(ae->get_ha());
            printf("\r\n");
        }
    }
}

int
arptab::add_entry(uint32_t pa, uint8_t *ha) {
    //
    // TODO: Need to lock the ARP table during this operation
    //
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (this->table[i].get_pa() == 0) {
            arptab_entry_t ae = &(this->table[i]);
            ae->set_pa(pa);
            ae->set_ha(ha);
            return 0;
        }
    return (-1);
}

arptab_entry_t
arptab::find_ha(uint8_t *ha) {
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (memcmp(ha, this->table[i].get_ha(), ETH_ADDR_LEN) == 0)
            return &(this->table[i]);
    return NULL;
}

arptab_entry_t
arptab::find_pa(uint32_t pa) {
    for (int i = 0; i < ARPTAB_ENTRIES; i++)
        if (pa == this->table[i].get_pa())
            return &(this->table[i]);
    return NULL;
}
