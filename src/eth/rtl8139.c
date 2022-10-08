#if _DEBUG_ETH
#include <stdio.h>
#endif
#include <sys/io.h>
#include <sys/rtl8139.h>

static uint8_t hwaddr[6];

void
rtl8139_chip_reset(void *ioaddr) {
    int i;
    outb(ioaddr + CR, CmdReset);

    for (i = 1000; i > 0; i--) {
        if ((inb(ioaddr + CR) & CmdReset) == 0)
            break;
    }
}

void
rtl8139_init(pci_func_t f) {
    /* Get Ethernet MAC address */
    for (int i = 0; i < 6; i++)
        hwaddr[i] = inb(f->iobase + i);
#if _DEBUG_ETH
    printf("rtl8139: hwaddr ");
    for (int i = 0; i < 6; i++) {
        printf("%02x", hwaddr[i]);
        if (i < 5)
            printf(":");
    }
    printf("\r\n");
#endif

    /* Register interrupt service routine */

    /* Initalize transmit and receive buffer rings */

    /* Start hardware */

    return;
}
