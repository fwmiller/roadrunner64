#if _DEBUG_PCI
#include <stdio.h>
#endif
#include <stdint.h>
#include <sys/io.h>

#define PCI_SLOTS 32

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

static uint32_t
pci_config_read(int bus, int dev, int func, int dword) {
    outl(PCI_CONFIG_ADDR, ((uint32_t) 0x80000000 | (bus << 16) | (dev << 11) |
                           (func << 8) | (dword << 2)));
    return inl(PCI_CONFIG_DATA);
}

static int
pci_device_count(int bus) {
    uint32_t vendorid;
    int devcnt = 0;

#if _DEBUG_PCI
    printf("pci bus %d\r\n", bus);
#endif
    for (int dev = 0; dev < PCI_SLOTS; dev++) {
        vendorid = pci_config_read(bus, dev, 0, PCI_CONFIG_VENDOR) & 0xffff;
        if (vendorid != 0xffff) {
            devcnt++;
#if _DEBUG_PCI
            printf("vendorid 0x%08x\r\n", vendorid);
#endif
        }
    }
    return devcnt;
}

void
pci_init() {
    for (int i = 0; i < 4; i++)
        pci_device_count(i);
}
