#include <ata.h>
#include <io.h>
#include <stdint.h>

void kprintf(const char *fmt, ...);

int atapi_read_sector(atad_t atad, uint_t lba, uchar_t * buf)
{
	uint8_t read_cmd[12] = { 0xa8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	uint8_t status;

	/* Setup read sectors command */
	read_cmd[9] = 1;	/* 1 sector */
	read_cmd[2] = (lba >> 0x18) & 0xff;	/* most sig byte of LBA */
	read_cmd[3] = (lba >> 0x10) & 0xff;
	read_cmd[4] = (lba >> 0x08) & 0xff;
	read_cmd[5] = (lba >> 0x00) & 0xff;	/* least sig byte of LBA */

	/* Select drive */
	ata_outb(atad->atac, ATA_DRVHD, 0xa0 | (atad->drive << 4));
	ata_select_delay(atad->atac);

	/* Issue read sectors command */
	ata_outb(atad->atac, ATA_FEATURE, 0);
	ata_outb(atad->atac, ATA_TRACKLSB, ATAPI_SECTOR_SIZE & 0xff);
	ata_outb(atad->atac, ATA_TRACKMSB, ATAPI_SECTOR_SIZE >> 8);
	ata_outb(atad->atac, ATA_COMMAND, ATA_CMD_ATAPI_READ);

	outsw(atad->atac->iobase, (ushort_t *) read_cmd,
	      sizeof(read_cmd) >> 1);

	ata_wait(atad->atac, ATA_CMD_ATAPI_READ, ATA_TIMEOUT_DRQ);

	/* Read actual size */
	int size = ((int) ata_inb(atad->atac, ATA_TRACKMSB)) << 8 |
		   (int) ata_inb(atad->atac, ATA_TRACKLSB);
#if _DEBUG
	kprintf("atapi_read_sector: read %d bytes\n", size);
#endif
	/* Read data */
	insw(atad->atac->iobase, (ushort_t *) buf, size >> 1);

	ata_eoi(atad->atac);

	return size;
}

#if 0
int
atapi_drive_read_sector (uint32_t bus, uint32_t drive, uint32_t lba, uint8_t *buffer)
{
/* 0xA8 is READ SECTORS command byte. */
uint8_t read_cmd[12] = { 0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
uint8_t status;
int size;
/* Tell the scheduler that this process is using the ATA subsystem. */
ata_grab ();
/* Select drive (only the slave-bit is set) */
outb (drive & (1 << 4), ATA_DRIVE_SELECT (bus));      
ATA_SELECT_DELAY (bus);       /* 400ns delay */
outb (0x0, ATA_FEATURES (bus));       /* PIO mode */
outb (ATAPI_SECTOR_SIZE & 0xFF, ATA_ADDRESS2 (bus));
outb (ATAPI_SECTOR_SIZE >> 8, ATA_ADDRESS3 (bus));
outb (0xA0, ATA_COMMAND (bus));       /* ATA PACKET command */
while ((status = inb (ATA_COMMAND (bus))) & 0x80)     /* BUSY */
asm volatile ("pause");
while (!((status = inb (ATA_COMMAND (bus))) & 0x8) && !(status & 0x1))
asm volatile ("pause");
/* DRQ or ERROR set */
if (status & 0x1) {
size = -1;
goto cleanup;
}
read_cmd[9] = 1;              /* 1 sector */
read_cmd[2] = (lba >> 0x18) & 0xFF;   /* most sig. byte of LBA */
read_cmd[3] = (lba >> 0x10) & 0xFF;
read_cmd[4] = (lba >> 0x08) & 0xFF;
read_cmd[5] = (lba >> 0x00) & 0xFF;   /* least sig. byte of LBA */
/* Send ATAPI/SCSI command */
outsw (ATA_DATA (bus), (uint16_t *) read_cmd, 6);
/* Wait for IRQ that says the data is ready. */
schedule ();
/* Read actual size */
size =
(((int) inb (ATA_ADDRESS3 (bus))) << 8) |
(int) (inb (ATA_ADDRESS2 (bus)));
/* This example code only supports the case where the data transfer
* 	* of one sector is done in one step. */
ASSERT (size == ATAPI_SECTOR_SIZE);
/* Read data. */
insw (ATA_DATA (bus), buffer, size / 2);
/* The controller will send another IRQ even though we've read all
* 	* the data we want.  Wait for it -- so it doesn't interfere with
* 		* subsequent operations: */
schedule ();
/* Wait for BSY and DRQ to clear, indicating Command Finished */
while ((status = inb (ATA_COMMAND (bus))) & 0x88) 
asm volatile ("pause");
cleanup:
/* Exit the ATA subsystem */
ata_release ();
return size;
}
#endif
