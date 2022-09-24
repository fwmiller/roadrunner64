#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <sys/pci.h>

struct pci_func pcitab[PCI_TAB_SIZE];
int pcifuncs = 0;

static void
pci_scan_bus(int bus, int *pcifunc) {
    uint32_t dword, iobase;
    uint16_t vendorid, deviceid;
    uint8_t class, subclass;
#if _DEBUG_PCI
    uint8_t intrpin;
#endif
    int dev, intrline, i;

    for (dev = 0; dev < PCI_SLOTS; dev++) {
        /* Function and vendor ids */
        dword = pci_config_read(bus, dev, 0, PCI_CONFIG_VENDOR);
        vendorid = dword & 0xffff;
        deviceid = dword >> 16;

        if (vendorid != 0xffff) {
#if _DEBUG_PCI
            printf("bus %d dev %d ", bus, dev);
            printf("vendorid 0x%08x ", vendorid);
#endif
            /* Function class code */
            dword = pci_config_read(bus, dev, 0, PCI_CONFIG_CLASS_REV);
            class = dword >> 24;
            subclass = (dword >> 16) & 0xff;
#if _DEBUG_PCI
            printf("class 0x%02x sub 0x%02x", class, subclass);
#endif
            /* Function iobase addresses */
            for (iobase = 0, i = 0; i < 6; i++) {
                dword =
                    pci_config_read(bus, dev, 0, PCI_CONFIG_BASE_ADDR_0 + i);
                if (dword & 0x01) {
                    iobase = dword & 0xfffffffc;
#if _DEBUG_PCI
                    printf(" iobase 0x%x", iobase);
#endif
                }
            }
            /* Function interrupt line */
            dword = pci_config_read(bus, dev, 0, PCI_CONFIG_INTR);
#if _DEBUG_PCI
            intrpin = (uint8_t)(dword >> 8) & 0xff;
#endif
            intrline = dword & 0xff;
#if _DEBUG_PCI
            if (intrpin > 0 && intrpin < 5 && intrline < 32)
                printf(" irq %d", intrline);
            printf("\r\n");
#endif
            /* Fill in pci device table entry */
            pci_func_t f = &(pcitab[*pcifunc]);
            f->bus = bus;
            f->dev = dev;
            f->func = 0;
            f->vendorid = (uint16_t) vendorid;
            f->class = class;
            f->subclass = subclass;
            f->deviceid = deviceid;
            f->iobase = iobase;
            f->irq = intrline;

            (*pcifunc)++;
        }
    }
}

void
pci_init() {
    for (int i = 0; i < 4; i++)
        pci_scan_bus(i, &pcifuncs);

    /* Search for Ethernet device */
    pci_func_t f = pci_lookup(PCI_CLASS_NETWORK, PCI_NETWORK_ETHERNET);
    if (f != NULL)
        printf("PCI Ethernet device found iobase 0x%x irq %d\r\n", f->iobase,
               f->irq);
}
