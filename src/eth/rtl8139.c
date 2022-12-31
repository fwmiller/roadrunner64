#if _DEBUG_ETH
#include <stdio.h>
#endif
#include <string.h>
#include <sys/io.h>
#include <sys/rtl8139.h>

static uint8_t hwaddr[6];
static struct rtl8139_private rtl8139_priv;

struct rtl8139_private *eth_priv = &rtl8139_priv;

void
rtl8139_chip_reset(void *ioaddr) {
    outb(ioaddr + CR, CmdReset);

    for (int i = 1000; i > 0; i--) {
        if ((inb(ioaddr + CR) & CmdReset) == 0)
            break;
    }
}

void
rtl8139_init(pci_func_t f) {
    memset(eth_priv, 0, sizeof(struct rtl8139_private));

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

void
rtl8139_isr() {
#if _DEBUG_ETH
    printf("!");
#endif
}
