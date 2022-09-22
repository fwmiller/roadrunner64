#ifndef __PCI_H
#define __PCI_H

#include <stdint.h>

#define PCI_BUSSES 4
#define PCI_SLOTS 32
#define PCI_TAB_SIZE (PCI_BUSSES * PCI_SLOTS)

/* Ports for access to PCI config space */
#define PCI_CONFIG_ADDR 0xcf8
#define PCI_CONFIG_DATA 0xcfc

/* PCI config space register offsets */
#define PCI_CONFIG_VENDOR 0
#define PCI_CONFIG_CMD_STAT 1
#define PCI_CONFIG_CLASS_REV 2
#define PCI_CONFIG_HDR_TYPE 3
#define PCI_CONFIG_BASE_ADDR_0 4
#define PCI_CONFIG_BASE_ADDR_1 5
#define PCI_CONFIG_BASE_ADDR_2 6
#define PCI_CONFIG_BASE_ADDR_3 7
#define PCI_CONFIG_BASE_ADDR_4 8
#define PCI_CONFIG_BASE_ADDR_5 9
#define PCI_CONFIG_CIS 10
#define PCI_CONFIG_SUBSYSTEM 11
#define PCI_CONFIG_ROM 12
#define PCI_CONFIG_CAPABILITIES 13
#define PCI_CONFIG_INTR 15

struct pci_func {
    int bus, dev, func; /* Function logical address */
    uint16_t vendorid;  /* Vendor id */
    uint16_t deviceid;  /* Device id */
    uint32_t iobase;    /* I/O registers base addr */
    int irq;            /* Interrupt number */
};

typedef struct pci_func *pci_func_t;

extern struct pci_func pcitab[];
extern int pcifuncs;

uint32_t pci_config_read(int bus, int dev, int func, int dword);
void pci_init();

#endif
