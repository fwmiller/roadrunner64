#include <stdio.h>
#include <sys/pci.h>
#include <sys/shell.h>

#define PCI_HDR "bus dev func vendor     class      subclass"

void dump_pci_vendorid(uint32_t vendorid);
void dump_pci_class(uint8_t class);
void dump_pci_subclass(uint8_t class, uint8_t subclass);

void
cmd_pci() {
    printf("%s\r\n", PCI_HDR);
    for (int i = 0; i < pcifuncs; i++) {
        printf("%3d %3d %4d ", pcitab[i].bus, pcitab[i].dev, pcitab[i].func);
        dump_pci_vendorid(pcitab[i].vendorid);
        printf(" ");
        dump_pci_class(pcitab[i].class);
        printf(" 0x%02x\r\n", pcitab[i].subclass);
    }
}
