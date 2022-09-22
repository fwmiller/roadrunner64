#if _DEBUG_PCI
#include <stdio.h>
#endif
#include <sys/io.h>
#include <sys/pci.h>

struct pci_func pcitab[PCI_TAB_SIZE];
int pcifuncs = 0;

static void
pci_scan_bus(int bus, int *pcifunc) {
    uint32_t dword, iobase;
    uint16_t vendorid, deviceid;
    uint8_t class, subclass, intrpin;
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
            printf("class 0x%02x subclass 0x%02x", class, subclass);
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
            intrpin = (uint8_t)(dword >> 8) & 0xff;
            intrline = dword & 0xff;
#if _DEBUG_PCI
            if (intrpin > 0 && intrpin < 5 && intrline < 32)
                printf(" irq %d", intrline);
            printf(" \n");
#endif

            /* Fill in pci device table entry */
            pcitab[*pcifunc].bus = bus;
            pcitab[*pcifunc].dev = dev;
            pcitab[*pcifunc].func = 0;
            pcitab[*pcifunc].vendorid = (uint16_t) vendorid;
            pcitab[*pcifunc].class = class;
            pcitab[*pcifunc].subclass = subclass;
            pcitab[*pcifunc].deviceid = deviceid;
            pcitab[*pcifunc].iobase = iobase;
            pcitab[*pcifunc].irq = intrline;

            (*pcifunc)++;
        }
    }
}

void
pci_init() {
    for (int i = 0; i < 4; i++)
        pci_scan_bus(i, &pcifuncs);
}
