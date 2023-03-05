#ifndef __RTL8139_H
#define __RTL8139_H

#include <sys/pci.h>

#define RTL_VENDOR_ID 0x10EC
#define RTL_DEVICE_ID 0x8139

#define NUM_TX_DESC 4
#define TX_BUF_SIZE 1536
#define TOTAL_TX_BUF_SIZE (TX_BUF_SIZE * NUM_TX_DESC)

#define RX_BUF_LEN_IDX 2 /* 0==8K, 1==16K, 2==32K, 3==64K */
#define RX_BUF_LEN (8192 << RX_BUF_LEN_IDX)
#define RX_BUF_PAD 16        /* Bit 11-12 of RCR: 0x44 */
#define RX_BUF_WRAP_PAD 2048 /* spare padding to handle packet wrap */
#define TOTAL_RX_BUF_SIZE (RX_BUF_LEN + RX_BUF_PAD + RX_BUF_WRAP_PAD)

#define TSD0 0x10
#define TSAD0 0x20
#define RBSTART 0x30
#define CR 0x37
#define CAPR 0x38
#define IMR 0x3C
#define ISR 0x3E
#define TCR 0x40
#define RCR 0x44
#define MPC 0x4C
#define MULINT 0x5C

#define TxUnderrun 0x4000
#define TxStatOK 0x8000
#define TxAborted 0x40000000

#define RxBufEmpty 0x01
#define CmdReset 0x10
#define CmdTxEnb 0x04
#define CmdRxEnb 0x08

#define RxOK 0x01
#define RxErr 0x02
#define TxOK 0x04
#define TxErr 0x08
#define RxOverFlow 0x10
#define RxUnderrun 0x20
#define RxFIFOOver 0x40
#define CableLen 0x2000
#define TimeOut 0x4000
#define SysErr 0x8000

#define INT_MASK                                                          \
    (RxOK | RxErr | TxOK | TxErr | RxOverFlow | RxUnderrun | RxFIFOOver | \
     CableLen | TimeOut | SysErr)

struct rtl8139_private {
    /* pci device info */
    pci_func_t f;

    /* rx status info */
    unsigned char rx_ring[TOTAL_RX_BUF_SIZE];
    unsigned char *rx_ring_dma;
    unsigned int cur_rx;

    /* tx status info */
    unsigned int tx_flag;
    unsigned int cur_tx;
    unsigned int dirty_tx;
    unsigned char *tx_buf[NUM_TX_DESC];
    unsigned char *tx_bufs_dma;
    unsigned char tx_bufs[TOTAL_TX_BUF_SIZE];

    /* device statistics */
    // struct net_device_stats stats;
};

extern struct rtl8139_private rtl8139_priv;

void rtl8139_init(pci_func_t f);
void rtl8139_isr();

#endif
