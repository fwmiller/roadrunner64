#include <errno.h>
#if _DEBUG_ATA
#include <stdio.h>
#endif
#include <string.h>
#include <sys/ata.h>
#include <sys/io.h>

int
atapi_identify(atad_t atad, char *drvstr) {
    uint8_t sig[4];

    sig[0] = inb(atad->atac->iobase + ATA_SECTORCNT);
    sig[1] = inb(atad->atac->iobase + ATA_SECTOR);
    sig[2] = inb(atad->atac->iobase + ATA_TRACKLSB);
    sig[3] = inb(atad->atac->iobase + ATA_TRACKMSB);

    if (sig[0] != 0x01 || sig[1] != 0x01 || sig[2] != 0x14 || sig[3] != 0xeb)
        return EFAIL;

    /* Issue identify packet command */
    ata_outb(atad->atac, ATA_DRVHD, 0xa0 | (atad->drive << 4));
    ata_select_delay(atad->atac);
    ata_outb(atad->atac, ATA_COMMAND, ATA_CMD_ATAPI_IDENTIFY);

    /* Wait for data ready */
    ata_wait(atad->atac, ATA_CMD_READ, ATA_STAT_DRQ);

    /* Read parameter data */
    insw(atad->atac->iobase + ATA_DATA, (uint16_t *) &(atad->param),
         SECTOR_SIZE / 2);
#if _DEBUG_ATA
    ata_convert_string(atad->param.model, 20);
    printf("%s: ATAPI ", drvstr);
    if (((atad->param.config >> 8) & 0x1f) == 5)
        printf("CD-ROM drive");
    else
        printf("device");
    printf("\r\n");

    printf("%s: %s\r\n", drvstr, atad->param.model);
#endif
    return 0;
}
