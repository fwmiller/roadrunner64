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

typedef struct pci_func *pci_func_t;

extern struct pci_func pcitab[];
extern int pcifuncs;

uint32_t pci_config_read(int bus, int dev, int func, int dword);
void pci_init();
pci_func_t pci_lookup(uint8_t class, uint8_t subclass);

#endif
