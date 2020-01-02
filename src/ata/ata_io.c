#include <ata.h>
#include <errno.h>
#include <io.h>

#define ITERATIONS	100000

int ata_wait(atac_t atac, uchar_t cmd, uchar_t mask)
{
	int i;
	uchar_t status;

	for (i = 0; i < ITERATIONS; i++) {
		status = inb(atac->ctlbase + ATA_ALT_STATUS);
		if (!(status & ATA_STAT_BSY)) {
			if (status & ATA_STAT_ERR) {
				switch (cmd) {
				case ATA_CMD_READ:
					return EDEVREAD;
				case ATA_CMD_WRITE:
					return EDEVWRITE;
				}
				return ENOSYS;
			}
			if ((status & (mask)) == (mask)) {
				break;
			}
		}
	}
	return 0;
}

void ata_outb(atac_t atac, ushort_t port, uchar_t val)
{
	int i;
	uchar_t status;

	for (i = 0; i < 1000000; i++) {
		status = inb(atac->ctlbase + ATA_ALT_STATUS);
		if (!(status & ATA_STAT_BSY) && !(status & ATA_STAT_DRQ)) {
			outb(atac->iobase + port, val);
			break;
		}
	}
}

#if 0
#define ATA_OUTB(ATAC, PORT, VAL)
{
	time_t start;
	uchar_t status;

	for (start = time();;) {
		status = inb((ATAC)->ctlbase + ATA_ALT_STATUS);
		if (!(status & ATA_STAT_BSY) && !(status & ATA_STAT_DRQ)) {
			outb((ATAC)->iobase + (PORT), (VAL));
			break;
		}
		if (time() - start >= ATA_TIMEOUT_OUTB) {
			ata_reset(ATAC);
			return ETIMEDOUT;
		}
	}
}

#define ATA_WAIT(ATAC, CMD, MASK, TIMEOUT)
{
	time_t start;
	uchar_t status;
	int i;

	for (start = time();;) {
		status = inb((ATAC)->ctlbase + ATA_ALT_STATUS);
		if (!(status & ATA_STAT_BSY)) {
			if (status & ATA_STAT_ERR)
				switch (CMD) {
				case ATA_CMD_READ:
					return EDEVREAD;
				case ATA_CMD_WRITE:
					return EDEVWRITE;
				default:
					return ENOSYS;
				}
			if ((status & (MASK)) == (MASK))
				break;
		}
		if (time() - start >= (TIMEOUT))
			return ETIMEDOUT;
	}
}
#endif
