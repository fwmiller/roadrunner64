#include <errno.h>
#include <stdlib.h>
#include <sys/ata.h>
#include <sys/io.h>

int
ata_read(void *dev, uint8_t * b, int len)
{
	atap_t atap = (atap_t) dev;
	atad_t atad = atap->atad;
	uint16_t *buf;
	int i, nsectors;

	if (dev == NULL || b == NULL || len % SECTOR_SIZE != 0)
		return EINVAL;

	nsectors = len / SECTOR_SIZE;

	/* Select drive */
	ata_outb(atad->atac, ATA_DRVHD,
		 0xa0 | ((uint8_t) atad->head & 0x0f) | (atad->drive << 4));

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
		buf = (uint16_t *) (b + i * SECTOR_SIZE);
		insw(atad->atac->iobase + ATA_DATA, buf, SECTOR_SIZE / 2);

		ata_eoi(atad->atac);
	}
	return 0;
}

static int
ata_read_mbr(atap_t atap, uint8_t * b, int *len)
{
	struct seek seekargs;
	int result;

	seekargs.offset = 0;
	seekargs.whence = SEEK_SET;
	result = ata_seek(atap->atad, &seekargs);
	if (result < 0)
		return result;

	result = ata_read(atap, b, *len);
	if (result < 0)
		return result;

	return 0;
}

int
ata_read_parttab(atad_t atad)
{
	uint8_t b[SECTOR_SIZE];
	struct ata_partition atap;
	int len, result;

	memset(b, 0, SECTOR_SIZE);
	atap.atad = atad;
	atap.sectors = 0;
	atap.offset = 0;
	len = SECTOR_SIZE;
	result = ata_read_mbr(&atap, b, &len);
	if (result < 0)
		return result;

	load_parttab(b, atad->parttab);
	return 0;
}
