#include <ata.h>
#include <errno.h>
#include <io.h>

void kprintf(const char *fmt, ...);
void bufdump(char *buf, int size);

int atapi_read_sector(atad_t atad, uint_t lba, uchar_t * buf)
{
	uchar_t read_cmd[12] = { 0xa8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uchar_t status;
	int size;

	ata_outb(atad->atac, ATA_FEATURE, 0);
	ata_outb(atad->atac, ATA_TRACKLSB, ATAPI_SECTOR_SIZE & 0xff);
	ata_outb(atad->atac, ATA_TRACKMSB, ATAPI_SECTOR_SIZE >> 8);
	ata_outb(atad->atac, ATA_DRVHD, 0xa0 | (atad->drive << 4));
	/*ATA_WAIT(atad->atac, ATA_CMD_READ, ATA_STAT_DRQ, ATA_TIMEOUT_DRQ); */
	ata_wait(atad->atac, ATA_CMD_READ, ATA_STAT_DRQ);

	while ((status = inb(atad->atac->iobase + ATA_ALT_STATUS)) & 0x80) ;

	while (!((status = inb(atad->atac->iobase +
			       ATA_ALT_STATUS)) & 0x08) && !(status & 0x01)) ;

	if (status & 0x01) {
#if _DEBUG
		kprintf("atapi_read: failed\n");
#endif
		size = (-1);
		goto cleanup;
	}
	read_cmd[9] = 1;	/* 1 sector */
	read_cmd[2] = (lba >> 0x18) & 0xff;	/* most sig byte of LBA */
	read_cmd[3] = (lba >> 0x10) & 0xff;
	read_cmd[4] = (lba >> 0x08) & 0xff;
	read_cmd[5] = (lba >> 0x00) & 0xff;	/* least sig byte of LBA */

	outsw(atad->atac->iobase, (ushort_t *) read_cmd, sizeof(read_cmd) >> 1);

	/* XXX Wait for data ready IRQ */

	/* Read actual size */
	size = (((int)inb(atad->atac->iobase + ATA_TRACKMSB)) << 8) |
	    (int)(inb(atad->atac->iobase + ATA_TRACKLSB));
#if _DEBUG
	if (size != ATAPI_SECTOR_SIZE) {
		kprintf("atapi_read: bad sector size read = %d bytes\n", size);
	}
#endif
	/* Read data */
	insw(atad->atac->iobase, (ushort_t *) buf, size >> 1);

 cleanup:
	return size;
}

int atapi_identify(atad_t atad, char *drvstr)
{
	uchar_t sig[4];
	uchar_t buf[ATAPI_SECTOR_SIZE];
	int result;

	sig[0] = inb(atad->atac->iobase + 2);
	sig[1] = inb(atad->atac->iobase + 3);
	sig[2] = inb(atad->atac->iobase + 4);
	sig[3] = inb(atad->atac->iobase + 5);

	if (sig[0] != 0x01 || sig[1] != 0x01 ||
	    sig[2] != 0x14 || sig[3] != 0xeb)
		return EFAIL;

	/* Issue identify packet command */
	ata_outb(atad->atac, ATA_DRVHD, 0xa0 | (atad->drive << 4));
	ata_outb(atad->atac, ATA_COMMAND, ATA_CMD_ATAPI_IDENTIFY);

	/* Wait for data ready */
	/*ATA_WAIT(atad->atac, ATA_CMD_READ, ATA_STAT_DRQ, ATA_TIMEOUT_DRQ); */
	ata_wait(atad->atac, ATA_CMD_READ, ATA_STAT_DRQ);

	/* Read parameter data */
	insw(atad->atac->iobase + ATA_DATA,
	     (void *)&(atad->param), SECTOR_SIZE / 2);

	ata_convert_string(atad->param.model, 20);
	kprintf("%s: ATAPI ", drvstr);
	if (((atad->param.config >> 8) & 0x1f) == 5)
		kprintf("CD-ROM drive\n");
	else
		kprintf("device\n");
	kprintf("%s: %s\n", drvstr, atad->param.model);

	result = atapi_read_sector(atad, 0, buf);

	bufdump((char *)buf, 128);

	return result;
}
