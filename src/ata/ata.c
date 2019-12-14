/* 
 *  Roadrunner/pk
 *    Copyright (C) 1989-2001  Cornfed Systems, Inc.
 *
 *  The Roadrunner/pk operating system is free software; you can
 *  redistribute and/or modify it under the terms of the GNU General
 *  Public License, version 2, as published by the Free Software
 *  Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA 02111-1307 USA
 *
 *  More information about the Roadrunner/pk operating system of
 *  which this file is a part is available on the World-Wide Web
 *  at: http://www.cornfed.com.
 *
 */

#include <ata.h>
#include <errno.h>
#include <i8259.h>
#include <io.h>
#include <ioctl.h>
#include <part.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct ata_controller atactab[ATA_CONTROLLERS];
static struct ata_drive atadtab[ATA_DRIVES];

static struct ata_partition ataptab[PARTS * ATA_DRIVES];
static int nextpart = 0;

void kprintf(const char *fmt, ...);

int ata_init()
{
	int drive, result;

	memset(&atactab, 0, ATA_CONTROLLERS * sizeof(struct ata_controller));
	memset(&atadtab, 0, ATA_DRIVES * sizeof(struct ata_drive));
#if 0
	bzero(&ataptab, PARTS * ATA_DRIVES * sizeof(struct ata_partition));
#endif
	/* Initial configuration for both controllers */
	atactab[0].iobase = ATA0_IOBASE;
	atactab[1].iobase = ATA1_IOBASE;
#if 0
	mutex_clear(&(atactab[0].mutex));
	mutex_clear(&(atactab[1].mutex));
#endif
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
			int part;

			/* Read the partition table */
			atad->type = ATA_DRV_HD;
			result = ata_read_parttab(atad);
			if (result < 0)
				continue;

			for (part = 0; part < PARTS; part++) {
				atap_t atap;
#if 0
				struct hd hd;
#endif
				atap = &(ataptab[nextpart++]);
				atap->atad = atad;
				atap->sectors = atad->parttab[part].size;
				atap->offset = atad->parttab[part].off;
#if 0
				hd.ioctl = ata_ioctl;
				hd.read = ata_read;
				hd.write = ata_write;
				hd.part = atap;
				result = hd_alloc(&hd);
				if (result < 0)
					kprintf
					    ("ata_init: allocate hd failed (%s)\n",
					     strerror(result));
#endif
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

void ata_eoi(atac_t atac)
{
	/* Clear drive interrupt */
	inb(atac->iobase + ATA_STATUS);

	/* Clear interrupt controllers */
	if (atac->iobase == ATA0_IOBASE)
		outb(I8259_SLV_CTRL, I8259_EOI_HD);
	else
		outb(I8259_SLV_CTRL, I8259_EOI_HD + 1);
	outb(I8259_MSTR_CTRL, I8259_EOI_CAS);
}
