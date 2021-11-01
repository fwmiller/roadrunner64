#include <ata.h>
#include <errno.h>
#include <io.h>
#include <stdlib.h>

int ata_read(void *dev, uchar_t * b, int *len)
{
	atap_t atap = (atap_t) dev;
	atad_t atad = atap->atad;
	ushort_t *buf;
	int i, nsectors;

	if (dev == NULL ||
	    b == NULL || len == NULL || (*len) % SECTOR_SIZE != 0)
		return EINVAL;

	nsectors = *len / SECTOR_SIZE;

	/* Select drive */
	ata_outb(atad->atac, ATA_DRVHD,
		 0xa0 | ((uchar_t) atad->head & 0x0f) | (atad->drive << 4));

	/* Wait for drive ready */
	ata_wait(atad->atac, ATA_CMD_READ, ATA_STAT_DRDY);

	/* Issue read sectors command */
	ata_outb(atad->atac, ATA_SECTORCNT, nsectors);
	ata_outb(atad->atac, ATA_SECTOR, atad->sector);
	ata_outb(atad->atac, ATA_TRACKLSB, atad->track);
	ata_outb(atad->atac, ATA_TRACKMSB, (atad->track >> 8));
	ata_outb(atad->atac, ATA_COMMAND, ATA_CMD_READ);

	for (i = 0; i < nsectors; i++) {
		/* Wait for data ready */
		ata_wait(atad->atac, ATA_CMD_READ, ATA_STAT_DRQ);

		/* Read sector data */
		buf = (ushort_t *) (b + i * SECTOR_SIZE);
		insw(atad->atac->iobase + ATA_DATA, buf, SECTOR_SIZE / 2);

		ata_eoi(atad->atac);
	}
#if 1
	bufdump(b, 64);
#endif
	return 0;
}
