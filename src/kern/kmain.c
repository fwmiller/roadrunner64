#include <stdio.h>
#include <sys/fs.h>
#include <sys/io.h>
#include <sys/mc146818.h>
#include <sys/pci.h>
#include <sys/sys.h>

void word_widths();
void shell();

static unsigned
get_cmos_memsize() {
    unsigned short total;
    unsigned char lowmem, highmem;

    outb(MC146818_ADDR, MC146818_EXT_MEM_LO);
    lowmem = inb(MC146818_DATA);
    outb(MC146818_ADDR, MC146818_EXT_MEM_HI);
    highmem = inb(MC146818_DATA);

    total = lowmem | (highmem << 8);
#if _DEBUG
    printf("Available memory %u MB\r\n", total / 1024);
#endif
    return total;
}

void
kmain() {
    printf("\r\nRoadrunner 64-bit\r\n");

    word_widths();
    get_cmos_memsize();
    pci_init();
    fs_init();

    printf("Type ctrl-a x to exit\r\n");
    shell();
}
