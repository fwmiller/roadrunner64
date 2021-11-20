#include <stdio.h>
#include <string.h>
#include <sys/ata.h>

static struct ata_controller atactab[ATA_CONTROLLERS];
static struct ata_drive atadtab[ATA_DRIVES];
static struct ata_partition ataptab[PARTS * ATA_DRIVES];

static void
read_parttab(atad_t atad)
{
	int part, nextpart = 0, result;

	/* Read the partition table */
	result = ata_read_parttab(atad);
	if (result < 0)
		return;

	for (part = 0; part < PARTS; part++) {
		atap_t atap = &(ataptab[nextpart++]);

		atap->atad = atad;
		atap->sectors = atad->parttab[part].size;
		atap->offset = atad->parttab[part].off;
	}
	dump_parttab(atad->parttab);
}

atap_t
ata_get_primary_partition()
{
	/* First partition on the first drive */
	return &(ataptab[0]);
}

int
ata_init()
{
	int drive, result;

	memset(&atactab, 0, ATA_CONTROLLERS * sizeof(struct ata_controller));
	memset(&atadtab, 0, ATA_DRIVES * sizeof(struct ata_drive));

	/* Initial configuration for both controllers */
	atactab[0].iobase = ATA0_IOBASE;
	atactab[1].iobase = ATA1_IOBASE;
	atactab[0].ctlbase = ATA0_CTLBASE;
	atactab[1].ctlbase = ATA1_CTLBASE;

	/* Reset both controllers */
	ata_reset(&(atactab[0]));
	ata_reset(&(atactab[1]));

	/* Scan for attached drives */
	for (drive = 0; drive < ATA_DRIVES; drive++) {
		atad_t atad = &(atadtab[drive]);
		char s[8];

		atad->atac = &(atactab[drive / 2]);
		atad->drive = drive % 2;

		/* Check for an ATA hard drive */
		memset(s, 0, 8);
		sprintf(s, "ata%d", drive);
		result = ata_identify(atad, s);
		if (result == 0 && atad->blks > 0) {
			atad->type = ATA_DRV_HD;
			read_parttab(atad);
			continue;
		}
		/* Check for an ATAPI device */
		result = atapi_identify(atad, s);
		if (result == 0)
			atad->type = ATA_DRV_CDROM;
	}

	struct seek seekargs;
	uint8_t buf[2048];

	kprintf("seek to sector 0\r\n");
	seekargs.offset = 0;
	seekargs.whence = SEEK_SET;
	ata_seek(&(atadtab[0]), &seekargs);
	kprintf("read sector 0\r\n");
	memset(buf, 0, 2048);
	ata_read(&(atadtab[0]), buf, 512);
	bufdump(buf, 520);

	kprintf("seek to sector 1\r\n");
	seekargs.offset = 1;
	seekargs.whence = SEEK_SET;
	ata_seek(&(atadtab[0]), &seekargs);
	kprintf("read sector 0\r\n");
	memset(buf, 0, 2048);
	ata_read(&(atadtab[0]), buf, 512);
	bufdump(buf, 128);

	return 0;
}
