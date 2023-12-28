#include <stdio.h>
#include <stdlib.h>
#include "inet/icmp.h"

void
icmp::dump() {
    if (this->buf == NULL)
        return;

    icmp_hdr_t ih = (icmp_hdr_t) this->buf;

    printf("icmp type 0x%02x (", ih->type);
    dump_icmp_type(ih->type);
    printf(") code 0x%02x\r\n", ih->code);
}
