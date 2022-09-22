#include <sys/io.h>
#include <sys/pci.h>

uint32_t
pci_config_read(int bus, int dev, int func, int dword) {
    outl(PCI_CONFIG_ADDR, ((uint32_t) 0x80000000 | (bus << 16) | (dev << 11) |
                           (func << 8) | (dword << 2)));
    return inl(PCI_CONFIG_DATA);
}
