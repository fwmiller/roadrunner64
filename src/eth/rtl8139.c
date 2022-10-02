#include <sys/io.h>
#include <sys/rtl8139.h>

void
rtl8139_chip_reset(void *ioaddr) {
    int i;
    outb(ioaddr + CR, CmdReset);

    for (i = 1000; i > 0; i--) {
        if ((inb(ioaddr + CR) & CmdReset) == 0)
            break;
    }
}

void
rtl8139_init(pci_func_t f) {
    return;
}
