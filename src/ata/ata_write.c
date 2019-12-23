#include <ata.h>

#if 0
int ata_write(void *dev, buf_t * b)
{
	atap_t atap = (atap_t) dev;
	atad_t atad = atap->atad;
	ushort_t *buf;
	int i, j, nsectors;

	if (b == NULL || *b == NULL || blen(*b) % SECTOR_SIZE != 0)
		return EINVAL;

	nsectors = blen(*b) / SECTOR_SIZE;

	/* Select drive */
	ata_outb(atad->atac, ATA_DRVHD,
		 0xa0 | ((uchar_t) atad->head & 0x0f) | (atad->drive << 4));

	/* Wait for drive ready */
	ata_wait(atad->atac, ATA_CMD_WRITE, ATA_STAT_DRDY);

	/* Issue write sectors command */
	ata_outb(atad->atac, ATA_SECTORCNT, nsectors);
	ata_outb(atad->atac, ATA_SECTOR, atad->sector);
	ata_outb(atad->atac, ATA_TRACKLSB, atad->track);
	ata_outb(atad->atac, ATA_TRACKMSB, (atad->track >> 8));
	ata_outb(atad->atac, ATA_COMMAND, ATA_CMD_WRITE);

	for (i = 0; i < nsectors; i++) {
		/* Wait for data ready */
		ata_wait(atad->atac, ATA_CMD_WRITE, ATA_STAT_DRQ);

		/* Write sector data */
		buf = (ushort_t *) (bstart(*b) + i * SECTOR_SIZE);
		for (j = 0; j < SECTOR_SIZE / 2; j++)
			outw(atad->atac->iobase + ATA_DATA, buf[j]);

		ata_eoi(atad->atac);
	}
	brel(*b);
	*b = NULL;

	return 0;
}
#endif
