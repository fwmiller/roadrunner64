#include <stdlib.h>
#include "inet/arp.h"
#include "inet/arptab.h"

void
arp::receive() {
    arp_hdr_t ah = (arp_hdr_t) this->get_hdr();

    switch (reverse_byte_order_short(ah->opcode)) {
    case ARP_OP_REQ:
    case ARP_OP_REP:
        /*
         * TODO: Check for an update to the Ethernet MAC address if
         * the spa is found
         */
        if (at->find_pa(ah->spa) == NULL)
            at->add_entry(ah->spa, ah->sha);
        break;
    }
    bp->push((buf_t) this->get_buf());
}
