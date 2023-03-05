#if _DEBUG_ETH
#include <stdio.h>
#endif
#include <string.h>
#include <sys/io.h>
#include <sys/rtl8139.h>

static uint8_t hwaddr[6];

struct rtl8139_private rtl8139_priv;

static void
rtl8139_init_ring() {
    int i;

    rtl8139_priv.cur_tx = 0;
    rtl8139_priv.dirty_tx = 0;
    for (i = 0; i < NUM_TX_DESC; i++)
        rtl8139_priv.tx_buf[i] = &(rtl8139_priv.tx_bufs[i * TX_BUF_SIZE]);
}

static void
rtl8139_chip_reset(void *ioaddr) {
    outb(ioaddr + CR, CmdReset);

    for (int i = 1000; i > 0; i--) {
        if ((inb(ioaddr + CR) & CmdReset) == 0)
            break;
    }
}

void
rtl8139_init(pci_func_t f) {
    memset(&rtl8139_priv, 0, sizeof(struct rtl8139_private));

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
    /* Interrupt service routine registered during bootstrap */

    /* Start hardware */
    rtl8139_init_ring();
}

void
rtl8139_isr() {
#if _DEBUG_ETH
    printf("!");
#endif
}
