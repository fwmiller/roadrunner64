#include <ata.h>
#include <errno.h>
#include <io.h>
#include <string.h>

void kprintf(const char *fmt, ...);
void bufdump(char *buf, int size);

int atapi_identify(atad_t atad, char *drvstr)
{
	uchar_t sig[4];
	uchar_t buf[ATAPI_SECTOR_SIZE];
	int result;

	sig[0] = inb(atad->atac->iobase + ATA_SECTORCNT);
	sig[1] = inb(atad->atac->iobase + ATA_SECTOR);
	sig[2] = inb(atad->atac->iobase + ATA_TRACKLSB);
	sig[3] = inb(atad->atac->iobase + ATA_TRACKMSB);

	if (sig[0] != 0x01 || sig[1] != 0x01 ||
	    sig[2] != 0x14 || sig[3] != 0xeb)
		return EFAIL;

	/* Issue identify packet command */
	ata_outb(atad->atac, ATA_DRVHD, 0xa0 | (atad->drive << 4));
	ata_select_delay(atad->atac);
	ata_outb(atad->atac, ATA_COMMAND, ATA_CMD_ATAPI_IDENTIFY);

	/* Wait for data ready */
	ata_wait(atad->atac, ATA_CMD_READ, ATA_STAT_DRQ);

	/* Read parameter data */
	insw(atad->atac->iobase + ATA_DATA,
	     (void *)&(atad->param), SECTOR_SIZE / 2);

	ata_convert_string(atad->param.model, 20);
	kprintf("%s: ATAPI ", drvstr);
	if (((atad->param.config >> 8) & 0x1f) == 5)
		kprintf("CD-ROM drive");
	else
		kprintf("device");
	kprintf("\n");

	kprintf("%s: %s\n", drvstr, atad->param.model);
#if 0
	kprintf("atapi_identify: sector 0\n");
	memset(buf, 0, ATAPI_SECTOR_SIZE);
	result = atapi_read_sector(atad, 0, buf);
	bufdump((char *)buf, 128);

	kprintf("atapi_identify: sector 1\n");
	memset(buf, 1, ATAPI_SECTOR_SIZE);
	result = atapi_read_sector(atad, 0, buf);
	bufdump((char *)buf, 128);
#endif
	return result;
}
