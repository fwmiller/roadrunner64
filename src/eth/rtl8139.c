#include <inet/buf.h>
#include <inet/inet.h>
#if _DEBUG_ETH
#include <stdio.h>
#endif
#include <string.h>
#include <sys/i8259.h>
#include <sys/intr.h>
#include <sys/io.h>
#include <sys/rtl8139.h>

static uint8_t hwaddr[6];

struct rtl8139_private rtl8139_priv;

void bufdump(char *buf, int size);

#if _DEBUG_ETH
static void
rtl8139_dump_reg(uint32_t ioaddr) {
    uint8_t reg;

    reg = inb(ioaddr + CR);
    printf("cmd    : 0x%02x (", reg);
    if (reg & (1 << 4))
        printf("RST ");
    if (reg & (1 << 3))
        printf("RCVEN ");
    if (reg & (1 << 2))
        printf("TXEN ");
    if (reg & 1)
        printf("BUFE ");
    printf("\b)\r\n");

    printf("isr    : 0x%04x\r\n", inw(ioaddr + ISR));
    printf("imr    : 0x%04x\r\n", inw(ioaddr + IMR));
    printf("tcr    : 0x%08x\r\n", inl(ioaddr + TCR));
    printf("rcr    : 0x%08x\r\n", inl(ioaddr + RCR));
    printf("rbstart: 0x%08x\r\n", inl(ioaddr + RBSTART));
    printf("capr   : 0x%04x\r\n", inw(ioaddr + CAPR));
    printf("cbr    : 0x%04x\r\n", inw(ioaddr + CBR));
}

static void
rtl8139_dump_rx_status(uint16_t rx_status) {
    printf("rx_status 0x%04x (", rx_status);
    if (rx_status & SysErr)
        printf("SysErr ");
    if (rx_status & TimeOut)
        printf("TimeOut ");
    if (rx_status & CableLen)
        printf("CableLen ");
    if (rx_status & RxFIFOOver)
        printf("RxFIFOOver ");
    if (rx_status & RxUnderrun)
        printf("RxUnderrun ");
    if (rx_status & RxOverFlow)
        printf("RxOverFlow ");
    if (rx_status & TxErr)
        printf("TxErr ");
    if (rx_status & TxOK)
        printf("TxOK ");
    if (rx_status & RxErr)
        printf("RxErr ");
    if (rx_status & RxOK)
        printf("RxOK ");
    printf("\b)");
}
#endif

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
    for (unsigned i = 0; i < NUM_TX_DESC; i++)
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
#if _DEBUG_ETH
    printf("rtl8139: tx_bufs 0x%08x  tx_bufs_dma 0x%08x\r\n",
           rtl8139_priv.tx_bufs, rtl8139_priv.tx_bufs_dma);
    printf("rtl8139: rx_ring 0x%08x  rx_ring_dma 0x%08x\r\n",
           rtl8139_priv.rx_ring, rtl8139_priv.rx_ring_dma);
    printf("rtl8139: capr 0x%04x cbr 0x%04x\r\n", inw(f->iobase + CAPR),
           inw(f->iobase + CBR));
#endif

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

    /* Enable PCI Bus Mastering */
    uint32_t pcr =
        pci_config_read(f->bus, f->dev, f->func, PCI_CONFIG_CMD_STAT);
    if (!(pcr & (1 << 2))) {
        pcr |= (1 << 2);
        pci_config_writel(f->bus, f->dev, f->func, PCI_CONFIG_CMD_STAT, pcr);
    }
    rtl8139_hw_start(f->iobase);
#if _DEBUG_ETH
    rtl8139_dump_reg(f->iobase);
#endif
}

void
rtl8139_isr() {
    uint32_t ioaddr = rtl8139_priv.f->iobase;
    uint16_t isr = inw(ioaddr + ISR);

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
        uint16_t rx_status;
#endif
        uint16_t rx_size;
        uint16_t pkt_size;

        while ((inb(ioaddr + CR) & RxBufEmpty) == 0) {
            uint8_t *pkt =
                (uint8_t *) rtl8139_priv.rx_ring + rtl8139_priv.cur_rx;
#if _DEBUG_ETH
            rx_status = *((uint16_t *) pkt);
#endif
            rx_size = *((uint16_t *) (pkt + 2));
            pkt_size = rx_size - 4;
#if _DEBUG_ETH
            printf("rtl8139_isr: ");
            rtl8139_dump_rx_status(rx_status);
            printf(" rx_size %u\r\n", rx_size);
            rtl8139_dump_reg(ioaddr);
#endif
#if _DEBUG_ETH
            bufdump((char *) pkt, rx_size);
#endif
            /* Get a packet buffer */
            buf_t buf = bp->pop();
            if (buf == NULL) {
#if _DEBUG_ETH
                printf("rtl8139_isr: get packet buffer failed\r\n");
#endif
            } else {
                /*
                 * Copy packet data into packet buffer without the 4 bytes
                 * used by the hardware ring buffer
                 */
                memcpy(buf, pkt + 4, pkt_size);
            }

            /* Reuse the ring buffer */
            rtl8139_priv.cur_rx =
                (rtl8139_priv.cur_rx + rx_size + 4 + 3) & ~3;
            rtl8139_priv.cur_rx = rtl8139_priv.cur_rx % RX_BUF_LEN;
            outw(ioaddr + CAPR, rtl8139_priv.cur_rx - 16);

            /* Pass packet buffer up the Internet stack */
            if (buf != NULL) {
                class eth eth;
                eth.set_buf(buf);
                eth.set_frame((uint8_t *) buf);
                eth.set_framelen(pkt_size);
#if _DEBUG_INET
                if (dump_enabled)
                    eth.dump();
#endif
                eth.receive();
            }
#if _DEBUG_ETH
            printf("rtl8139_isr: cur_rx 0x%04x capr 0x%04x\r\n",
                   rtl8139_priv.cur_rx, inw(ioaddr + CAPR));
#endif
        }
    }
    /* Clear all interrupts */
    outw(ioaddr + ISR, 0xffff);
}
