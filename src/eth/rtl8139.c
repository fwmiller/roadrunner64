#include <stdio.h>
#include <string.h>
#include <sys/io.h>
#include <sys/pci.h>

#define CONFIG_SIZE 64

static uint8_t hwaddr[6];

static void
dump_ethaddr(uint8_t *ethaddr) {
    if (ethaddr == NULL)
        return;

    printf("%02x:%02x:%02x:%02x:%02x:%02x", ethaddr[0], ethaddr[1],
           ethaddr[2], ethaddr[3], ethaddr[4], ethaddr[5]);
}

void
rtl8139_init(pci_func_t f) {
    uint8_t buf[CONFIG_SIZE];
    memset(buf, 0, CONFIG_SIZE);

    for (int offset = 0; offset < CONFIG_SIZE; offset += 4)
        *((uint32_t *) (buf + offset)) =
            pci_config_read(f->bus, f->dev, f->func, offset);

    /* PCI config space */
    pci_config_t cfg = (pci_config_t) buf;
    printf("vendorid        0x%04x\r\n", cfg->vendorid);
    printf("devid           0x%04x\r\n", cfg->devid);
    printf("cmd             0x%04x\r\n", cfg->cmd);
    printf("stat            0x%04x\r\n", cfg->stat);

    /* IDR registers contain the Ethernet MAC address */
    for (int i = 0; i < 6; i++)
        hwaddr[i] = inb(f->iobase + i);
    printf("hwaddr ");
    dump_ethaddr(hwaddr);
    printf("\r\n");
}
