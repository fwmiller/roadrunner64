#if _DEBUG_ETH
#include <stdio.h>
#endif
#include <string.h>
#include <sys/intr.h>
#include <sys/io.h>
#include <sys/rtl8139.h>

static uint8_t hwaddr[6];

struct rtl8139_private rtl8139_priv;

static void
rtl8139_dump_reg(uint32_t ioaddr) {
    uint8_t reg;
    uint32_t regl;

    reg = inb(ioaddr + CR);
    printf("cmd: 0x%02x ", reg);
    if (reg & (1 << 4))
        printf("RST ");
    if (reg & (1 << 3))
        printf("RCVEN ");
    if (reg & (1 << 2))
        printf("TXEN ");
    if (reg & 1)
        printf("BUFE ");
    printf("\r\n");

    printf("imr: 0x%04x\r\n", inw(ioaddr + IMR));
    printf("isr: 0x%04x\r\n", inw(ioaddr + ISR));

    regl = inl(ioaddr + TCR);
    printf("tcr: 0x%08x\r\n", regl);

    regl = inl(ioaddr + RCR);
    printf("rcr: 0x%08x\r\n", regl);
}

static void
rtl8139_init_ring() {
    int i;

    rtl8139_priv.cur_tx = 0;
    rtl8139_priv.dirty_tx = 0;
    for (i = 0; i < NUM_TX_DESC; i++)
        rtl8139_priv.tx_buf[i] = &(rtl8139_priv.tx_bufs[i * TX_BUF_SIZE]);
}

static void
rtl8139_chip_reset(uint32_t ioaddr) {
    outb(ioaddr + CR, CmdReset);

    for (int i = 1000; i > 0; i--) {
        if ((inb(ioaddr + CR) & CmdReset) == 0)
            break;
    }
}

static void
rtl8139_hw_start(uint32_t ioaddr) {
    unsigned int i;

    rtl8139_chip_reset(ioaddr);
    outb(ioaddr + CR, CmdTxEnb | CmdRxEnb);  // enable tx and rx

    /* tx config */
    outl(ioaddr + TCR, 0x000000600);  // DMA burst size 1024

    /* rx config */
    /* rx buffer length (size of ring buffer): 32K + 16
     * max dma burst size: 1024
     * wrap bit: 1
     * accept broadcast packets
     * accept multicast packets
     * accept physical match packets */
    outl(ioaddr + RCR,
         ((1 << 12) | (6 << 8) | (1 << 7) | (1 << 3) | (1 << 2) | (1 << 1)));

    /* set tx descriptor buffer DMA addresses */
    for (i = 0; i < NUM_TX_DESC; i++)
        outl(ioaddr + TSAD0 + (i * 4),
             rtl8139_priv.tx_bufs_dma +
                 (rtl8139_priv.tx_buf[i] - rtl8139_priv.tx_bufs));

    /* init RBSTART */
    outl(ioaddr + RBSTART, rtl8139_priv.rx_ring_dma);

    /* init missed packet counter */
    outl(ioaddr + MPC, 0);

    /* no early-rx interrupts */
    outw(ioaddr + MULINT, (inw(ioaddr + MULINT) & 0xf000));

    /* Enable all known interrupts by setting the interrupt mask */
    outw(ioaddr + IMR, INT_MASK);
}

void
rtl8139_init(pci_func_t f) {
    memset(&rtl8139_priv, 0, sizeof(struct rtl8139_private));
    rtl8139_priv.f = f;

    rtl8139_priv.tx_bufs_dma = rtl8139_priv.tx_bufs;
    rtl8139_priv.rx_ring_dma = rtl8139_priv.rx_ring;

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
    rtl8139_hw_start(f->iobase);

    rtl8139_dump_reg(f->iobase);
}

void
rtl8139_isr() {
    uint32_t ioaddr = rtl8139_priv.f->iobase;
#if _DEBUG_ETH
    printf("rtl8139_isr: ioaddr 0x%08x\r\n", ioaddr);
#endif
    uint16_t isr = inw(ioaddr + ISR);
    printf("rtl8139_isr: isr 0x%04x\r\n", isr);

    /* Clear all interrupts */
    outw(ioaddr + ISR, 0xffff);

    if ((isr & TxOK) || (isr & TxErr)) {
#if _DEBUG_ETH
        printf("rtl8139_isr: tx interrupt\r\n");
#endif
    }
    if (isr & RxErr) {
#if _DEBUG_ETH
        printf("rtl8139_isr: rx error interrupt\r\n");
#endif
    }
    if (isr & RxOK) {
#if _DEBUG_ETH
        printf("rtl8139_isr: rx interrupt\r\n");
#endif
    }

    // Issue End-of-Interrupt to controller
    intr_eoi(IRQ2INTR(rtl8139_priv.f->irq));
}
