#include <ata.h>
#include <stdio.h>
#include <string.h>

static struct ata_controller atactab[ATA_CONTROLLERS];
static struct ata_drive atadtab[ATA_DRIVES];
static struct ata_partition ataptab[PARTS * ATA_DRIVES];

void kprintf(const char *fmt, ...);

int ata_init()
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
			int part, nextpart = 0;

			/* Read the partition table */
			atad->type = ATA_DRV_HD;
			result = ata_read_parttab(atad);
			if (result < 0)
				continue;

			for (part = 0; part < PARTS; part++) {
				atap_t atap;

				atap = &(ataptab[nextpart++]);
				atap->atad = atad;
				atap->sectors = atad->parttab[part].size;
				atap->offset = atad->parttab[part].off;
			}
			dump_parttab(atad->parttab);
			continue;
		}
		/* Check for an ATAPI device */
		result = atapi_identify(&(atadtab[drive]), s);
		if (result == 0)
			atadtab[drive].type = ATA_DRV_CDROM;
	}
	return 0;
}
