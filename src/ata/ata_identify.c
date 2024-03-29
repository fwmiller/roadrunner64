#include <errno.h>
#if _DEBUG_ATA
#include <stdio.h>
#endif
#include <sys/ata.h>
#include <sys/io.h>

void
ata_convert_string(uint16_t *s, int words) {
    char *s1;
    int i;

    for (i = 0; i < words; i++)
        s[i] = ((s[i] & 0xff) << 8) | ((s[i] >> 8) & 0xff);

    s1 = (char *) s;
    for (i = (words << 1) - 1; i >= 0; i--) {
        if (s1[i] != 0x20)
            break;
        s1[i] = '\0';
    }
}

int
ata_identify(atad_t atad, char *drvstr) {
    /* Issue identify command */
    ata_outb(atad->atac, ATA_DRVHD, 0xa0 | (atad->drive << 4));
    ata_select_delay(atad->atac);
    ata_outb(atad->atac, ATA_COMMAND, ATA_CMD_IDENTIFY);

    /* Wait for data ready */
    for (int cnt = 100000;
         cnt > 0 && !(inb(atad->atac->iobase + ATA_STATUS) & ATA_STAT_DRDY);
         cnt--)
        ;

    /* Read parameter data */
    insw(atad->atac->iobase + ATA_DATA, (uint16_t *) &(atad->param),
         SECTOR_SIZE / 2);

    /* Check for ATA device */
    if (atad->param.config & 0x8000)
        return EFAIL;

    /* Fill in drive parameters */
    atad->tracks = atad->param.cylinders;
    atad->heads = atad->param.heads;
    atad->sectorspertrack = atad->param.sectors;
    atad->blks = atad->tracks * atad->heads * atad->sectorspertrack;
    atad->size = (atad->blks * SECTOR_SIZE) / 1048576;
    if (atad->blks == 0)
        return EFAIL;

    ata_convert_string(atad->param.model, 20);
#if _DEBUG_ATA
    printf("%s: ATA hard disk\r\n", drvstr);
    printf("%s: %s\r\n", drvstr, atad->param.model);
    printf("%s: %u blks (%d MB) %u trks %u hds %u sec/trk\r\n", drvstr,
           atad->blks, atad->size, atad->tracks, atad->heads,
           atad->sectorspertrack);
#endif
    atad->flags |= ATA_FLAG_FOUND;

    return 0;
}
