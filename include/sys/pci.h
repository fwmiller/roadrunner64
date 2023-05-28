#ifndef __PCI_H
#define __PCI_H

#include <stdint.h>
#include <sys/pci_const.h>

struct pci_func {
    int bus, dev, func; /* Function logical address */
    uint16_t vendorid;  /* Vendor id */
    uint16_t deviceid;  /* Device id */
    uint8_t class;      /* Device class */
    uint8_t subclass;   /* Device subclass */
    uint32_t iobase;    /* I/O registers base addr */
    int irq;            /* Interrupt number */
};

struct pci_config {
    uint16_t vendorid;
    uint16_t devid;
    uint16_t cmd;
    uint16_t stat;
    uint8_t rev;
    uint8_t progif;
    uint8_t subclass;
    uint8_t class;
    uint8_t cachelinesize;
    uint8_t latency;
    uint8_t hdrtype;
    uint8_t bist;
    uint32_t bar0;
    uint32_t bar1;
    uint32_t bar2;
    uint32_t bar3;
    uint32_t bar4;
    uint32_t bar5;
} __attribute__((packed));

typedef struct pci_func *pci_func_t;
typedef struct pci_config *pci_config_t;

extern struct pci_func pcitab[];
extern int pcifuncs;

uint32_t pci_config_read(int bus, int dev, int func, int dword);
void pci_config_writel(int bus, int dev, int func, int dword, uint32_t val);
void pci_init();
pci_func_t pci_lookup(uint8_t class, uint8_t subclass);

#endif
