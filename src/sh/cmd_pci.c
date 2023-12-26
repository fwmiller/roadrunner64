#include <stdio.h>
#include <sys/pci.h>
#include <sys/sh.h>

#define PCI_HDR "bus dev vendor     class      iobase     irq"

void dump_pci_vendorid(uint32_t vendorid);
void dump_pci_class(uint8_t devclass);

void
cmd_pci() {
    printf("%s\r\n", PCI_HDR);
    for (int i = 0; i < pcifuncs; i++) {
        pci_func_t f = &(pcitab[i]);

        printf("%3d %3d ", f->bus, f->dev);
        dump_pci_vendorid(f->vendorid);
        printf(" ");
        dump_pci_class(f->devclass);

        if (f->iobase > 0)
            printf(" 0x%08x", f->iobase);
        else
            printf("       ");

        if (f->irq > 0)
            printf(" %d", f->irq);

        printf("\r\n");
    }
}
