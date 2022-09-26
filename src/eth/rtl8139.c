#include <stdio.h>
#include <string.h>
#include <sys/io.h>
#include <sys/pci.h>

#define CONFIG_SIZE 64

static void
pci_dump_bar(uint32_t bar) {
    printf("0x%08x (%s)", bar & 0xfffffff0, (bar & 0x01 ? "I/O" : "Memory"));
}

void
rtl8139_init(pci_func_t f) {
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

    printf("bar0            ");
    pci_dump_bar(cfg->bar0);
    printf("\r\nbar1            ");
    pci_dump_bar(cfg->bar1);
    printf("\r\nbar2            ");
    pci_dump_bar(cfg->bar2);
    printf("\r\nbar3            ");
    pci_dump_bar(cfg->bar3);
    printf("\r\nbar4            ");
    pci_dump_bar(cfg->bar4);
    printf("\r\nbar5            ");
    pci_dump_bar(cfg->bar5);
    printf("\r\n");
}
