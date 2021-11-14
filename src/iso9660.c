#include <stdint.h>
#include <string.h>
#include <sys/ata.h>
#include <sys/ioctl.h>

typedef uint32_t lba_t;

/* buf must be at least 2048 bytes and is assumed to be zeroed */
int
read_blk(atap_t part, lba_t lba, uint8_t *buf)
{
	struct seek seekargs;
	int i, result;

	/* Convert lba to sector */
	uint32_t sectorno = lba << 2;

	for (i = 0; i < 4; i++) {
		/* Seek to sector */
		seekargs.offset = sectorno + i;
		seekargs.whence = SEEK_SET;

		result = ata_seek(part->atad, &seekargs);
		if (result < 0)
			return (-1);

		/* Read sector data */
		result = ata_read(part, buf + (i * 512), 512);
		if (result < 0)
			return (-1);
	}
	return 0;
}

void
iso9660_init()
{
	uint8_t buf[2048];
	atap_t atap = ata_get_primary_partition();

	memset(buf, 0, 2048);
	read_blk(atap, 0x10, buf);
	bufdump(buf, 128);
}
