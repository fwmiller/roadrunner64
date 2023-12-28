#include <stdio.h>
#include <stdlib.h>
#include "inet/cppip.h"

void
eth::send() {
    if (this->frame == NULL)
        return;

    printf("eth::send()\r\n");
    bufdump(this->frame, this->framelen);

    /* Send down the packet */
#if 0
    if (pcap_sendpacket(intf_handl, this->frame, this->framelen) != 0) {
        printf("eth::send: pcap_sendpacket() failed ");
        pcap_perror(intf_handl, (char *) "eth::send() ");
    }
#endif
}
