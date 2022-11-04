#include <stdio.h>
#include <stdlib.h>
#include <sys/fs.h>
#include <sys/intr.h>
#include <sys/io.h>
#include <sys/mc146818.h>
#include <sys/pci.h>
#include <sys/sys.h>
#include <sys/tmr.h>

void word_widths();
void sh();

void rtl8139_init(pci_func_t f);

static unsigned
get_cmos_memsize() {
    unsigned short total;
    unsigned char lowmem, highmem;

    outb(MC146818_ADDR, MC146818_EXT_MEM_HI);
    highmem = inb(MC146818_DATA);
    outb(MC146818_ADDR, MC146818_EXT_MEM_LO);
    lowmem = inb(MC146818_DATA);

    total = (highmem << 8) | lowmem;
#if 1
    printf("Available memory %u MB\r\n", total / 1024);
#endif
    return total;
}

void
kmain() {
    printf("\r\nRoadrunner 64-bit\r\n");

    idt_init();
    intr_init();
    tmrstart(tmrcount(0));
    // enable;

    word_widths();
    get_cmos_memsize();
    pci_init();
    fs_init();

    /* Ethernet device */
    pci_func_t f = pci_lookup(PCI_CLASS_NETWORK, PCI_NETWORK_ETHERNET);
    if (f != NULL) {
#if _DEBUG_PCI
        printf("PCI Ethernet device found iobase 0x%x irq %d\r\n", f->iobase,
               f->irq);
#endif
        rtl8139_init(f);
    }
    printf("Type ctrl-a x to exit\r\n");
    sh();
}
