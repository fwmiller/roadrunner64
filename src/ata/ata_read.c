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
	ATA_OUTB(atad->atac, ATA_DRVHD,
		 0xa0 | ((uchar_t) atad->head & 0x0f) | (atad->drive << 4));

	/* Wait for drive ready */
	ATA_WAIT(atad->atac, ATA_CMD_READ, ATA_STAT_DRDY, ATA_TIMEOUT_DRDY);

	/* Issue read sectors command */
	ATA_OUTB(atad->atac, ATA_SECTORCNT, nsectors);
	ATA_OUTB(atad->atac, ATA_SECTOR, atad->sector);
	ATA_OUTB(atad->atac, ATA_TRACKLSB, atad->track);
	ATA_OUTB(atad->atac, ATA_TRACKMSB, (atad->track >> 8));
	ATA_OUTB(atad->atac, ATA_COMMAND, ATA_CMD_READ);

	for (i = 0; i < nsectors; i++) {
		/* Wait for data ready */
		ATA_WAIT(atad->atac, ATA_CMD_READ, ATA_STAT_DRQ,
			 ATA_TIMEOUT_DRQ);

		/* Read sector data */
		buf = (ushort_t *) (b + i * SECTOR_SIZE);
		insw(atad->atac->iobase + ATA_DATA, buf, SECTOR_SIZE / 2);

		ata_eoi(atad->atac);
	}
	return 0;
}
