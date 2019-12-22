#include <ata.h>
#include <errno.h>
#include <io.h>

#define ITERATIONS	1000000

int
ata_wait(atac_t atac, uchar_t cmd, uchar_t mask)
{
	int i;
	uchar_t status;

	for (i = 0; i < ITERATIONS; i++) {
		status = inb(atac->iobase + ATA_ALT_STATUS);
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
