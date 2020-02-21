#include <ata.h>
#include <io.h>

void kprintf(const char *fmt, ...);

int atapi_read_sector(atad_t atad, uint_t lba, uchar_t * buf)
{
	uchar_t read_cmd[12] = { 0xa8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uchar_t status;
	int size;

	/* Select drive */
	ata_outb(atad->atac, ATA_DRVHD, 0xa0 | (atad->drive << 4));
	ata_select_delay(atad->atac);

	/* Issue read sectors command */
	ata_outb(atad->atac, ATA_FEATURE, 0);
	ata_outb(atad->atac, ATA_TRACKLSB, ATAPI_SECTOR_SIZE & 0xff);
	ata_outb(atad->atac, ATA_TRACKMSB, ATAPI_SECTOR_SIZE >> 8);
	ata_outb(atad->atac, ATA_COMMAND, 0xa0);
	ata_wait(atad->atac, ATA_CMD_ATAPI_READ, ATA_STAT_DRQ);

	while ((status = inb(atad->atac->ctlbase + ATA_ALT_STATUS)) & 0x80) {
#if _DEBUG
		kprintf(".");
#endif
	}
#if 0
	while (!((status = inb(atad->atac->ctlbase +
			       ATA_ALT_STATUS)) & 0x08) && !(status & 0x01))
		kprintf("!");
#endif
	status = inb(atad->atac->ctlbase + ATA_ALT_STATUS);
	if (status & 0x01) {
#if _DEBUG
		kprintf("atapi_read_sector: failed\n");
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
		kprintf("atapi_read_sector: ");
		kprintf("bad sector size read = %d bytes\n", size);
	}
#endif
	/* Read data */
	insw(atad->atac->iobase, (ushort_t *) buf, size >> 1);

 cleanup:
	return size;
}
