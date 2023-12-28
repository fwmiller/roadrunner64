#include <stdio.h>
#include <stdlib.h>
#include "inet/cppip.h"

ieee802_2::ieee802_2() {
    this->hdr = NULL;
}

buf_t
ieee802_2::get_hdr() {
    return this->hdr;
}

void
ieee802_2::set_hdr(buf_t hdr) {
    this->hdr = hdr;
}

void
ieee802_2::receive() {
    return;
}

void
ieee802_2::dump() {
    if (this->hdr == NULL)
        return;

    ieee802_2_hdr_t llc_hdr = (ieee802_2_hdr_t) this->hdr;

    printf("802.2 LLC dsap 0x%02x ssap 0x%02x", llc_hdr->dsap, llc_hdr->ssap);

    if ((llc_hdr->control & 0x03) == 0x03)
        printf(" control 0x%02x (U-format)", llc_hdr->control);
    else {
        uint16_t control;
        control =
            reverse_byte_order_short(*((uint16_t *) &(llc_hdr->control)));
        printf(" control 0x%04x", control);
    }
    printf("\r\n");
}
