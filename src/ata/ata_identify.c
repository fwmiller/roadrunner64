#include <ata.h>
#include <errno.h>
#include <io.h>

void kprintf(const char *fmt, ...);

void ata_convert_string(ushort_t * s, int words)
{
	char *s1;
	int i;

	for (i = 0; i < words; i++)
		s[i] = ((s[i] & 0xff) << 8) | ((s[i] >> 8) & 0xff);

	s1 = (char *)s;
	for (i = (words << 1) - 1; i >= 0; i--) {
		if (s1[i] != 0x20)
			break;
		s1[i] = '\0';
	}
}

int ata_identify(atad_t atad, char *drvstr)
{
	/* Issue identify command */
	ata_outb(atad->atac, ATA_DRVHD, 0xa0 | (atad->drive << 4));
	ata_outb(atad->atac, ATA_COMMAND, ATA_CMD_IDENTIFY);

	/* Wait for data ready */
	ata_wait(atad->atac, ATA_CMD_READ, ATA_STAT_DRQ);

	/* Read parameter data */
	insw(atad->atac->iobase + ATA_DATA,
	     (void *)&(atad->param), SECTOR_SIZE / 2);

	/* Check for ATA device */
	if (atad->param.config & 0x8000) {
#if _DEBUG
		if ((atad->param.config & 0xc000) == 0x8000)
			kprintf("ata_identify: detected ATAPI device\n");
#endif
		return EFAIL;
	}
	/* Fill in drive parameters */
	atad->tracks = atad->param.cylinders;
	atad->heads = atad->param.heads;
	atad->sectorspertrack = atad->param.sectors;
	atad->blks = atad->tracks * atad->heads * atad->sectorspertrack;
	atad->size = (atad->blks * SECTOR_SIZE) / 1048576;

	if (atad->blks == 0)
		return EFAIL;

	ata_convert_string(atad->param.model, 20);
	kprintf("%s: ATA hard disk\n", drvstr);
	kprintf("%s: %s\n", drvstr, atad->param.model);
	kprintf("%s: %u blks (%d Mbytes) %u trks %u hds %u sec/trk\n",
		drvstr, atad->blks, atad->size,
		atad->tracks, atad->heads, atad->sectorspertrack);
	atad->flags = ATA_FLAG_FOUND;

	return 0;
}
