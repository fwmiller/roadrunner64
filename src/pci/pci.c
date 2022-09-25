#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            printf("vendorid 0x%04x ", vendorid);
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

#define CONFIG_SIZE 64

void
pci_init() {
    for (int i = 0; i < 4; i++)
        pci_scan_bus(i, &pcifuncs);

    /* Search for Ethernet device */
    pci_func_t f = pci_lookup(PCI_CLASS_NETWORK, PCI_NETWORK_ETHERNET);
    if (f != NULL) {
        printf("PCI Ethernet device found iobase 0x%x irq %d\r\n", f->iobase,
               f->irq);

        uint8_t buf[CONFIG_SIZE];
        memset(buf, 0, CONFIG_SIZE);

        for (int offset = 0; offset < CONFIG_SIZE; offset += 4)
            *((uint32_t *) (buf + offset)) =
                pci_config_read(f->bus, f->dev, f->func, offset);

        pci_config_t cfg = (pci_config_t) buf;
        printf("vendorid        0x%04x\r\n", cfg->vendorid);
        printf("devid           0x%04x\r\n", cfg->devid);
        printf("cmd             0x%04x\r\n", cfg->cmd);
        printf("stat            0x%04x\r\n", cfg->stat);
        printf("rev             0x%02x\r\n", cfg->rev);
        printf("progif          0x%02x\r\n", cfg->progif);
        printf("subclass        0x%02x\r\n", cfg->subclass);
        printf("class           0x%02x\r\n", cfg->class);
        printf("cachelinesize   0x%02x\r\n", cfg->cachelinesize);
        printf("latency         0x%02x\r\n", cfg->latency);
        printf("hdrtype         0x%02x\r\n", cfg->hdrtype);
        printf("bist            0x%02x\r\n", cfg->bist);
        printf("base addr reg 0 0x%08x ", cfg->bar0 & 0xfffffff0);
        if (cfg->bar0 & 0x01)
            printf("(I/O)\r\n");
        else
            printf("(Memory)\r\n");
        printf("base addr reg 1 0x%08x ", cfg->bar1 & 0xfffffff0);
        if (cfg->bar1 & 0x01)
            printf("(I/O)\r\n");
        else
            printf("(Memory)\r\n");
        printf("base addr reg 2 0x%08x ", cfg->bar2 & 0xfffffff0);
        if (cfg->bar2 & 0x01)
            printf("(I/O)\r\n");
        else
            printf("(Memory)\r\n");
        printf("base addr reg 3 0x%08x ", cfg->bar3 & 0xfffffff0);
        if (cfg->bar3 & 0x01)
            printf("(I/O)\r\n");
        else
            printf("(Memory)\r\n");
        printf("base addr reg 4 0x%08x ", cfg->bar4 & 0xfffffff0);
        if (cfg->bar4 & 0x01)
            printf("(I/O)\r\n");
        else
            printf("(Memory)\r\n");
        printf("base addr reg 5 0x%08x ", cfg->bar5 & 0xfffffff0);
        if (cfg->bar5 & 0x01)
            printf("(I/O)\r\n");
        else
            printf("(Memory)\r\n");
    }
}
