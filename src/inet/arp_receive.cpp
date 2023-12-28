#include <stdlib.h>
#include "inet/arp.h"
#include "inet/arptab.h"

void
arp::receive() {
    if (this->hdr == NULL)
        return;

    arp_hdr_t ah = (arp_hdr_t) this->hdr;

    switch (reverse_byte_order_short(ah->opcode)) {
    case ARP_OP_REQ:
    case ARP_OP_REP:
        /*
         * TODO: Check for an update to the Ethernet MAC address if
         * the spa is found
         */
        if (arptab.find_pa(ah->spa) == NULL)
            arptab.add_entry(ah->spa, ah->sha);
        break;
    }
}
