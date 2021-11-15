#include <stdint.h>
#include <string.h>
#include <sys/ata.h>
#include <sys/ioctl.h>
#include <sys/iso9660.h>

typedef uint32_t lba_t;

/*
 * buf must be at least ATAPI_SECTOR_SIZE = 2048 bytes and is assumed to
 * be zeroed
 */
static int
read_blk(atap_t part, lba_t lba, uint8_t * buf)
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
		result = ata_read(part, buf + (i * SECTOR_SIZE), SECTOR_SIZE);
		if (result < 0)
			return (-1);
	}
	return 0;
}

static int
iso9660_verify_primary_volume(volume_descriptor_t vol)
{
	if (vol->type != VOLUME_DESCRIPTOR_TYPE_PRIMARY ||
	    vol->id[0] != 'C' ||
	    vol->id[1] != 'D' ||
	    vol->id[2] != '0' ||
	    vol->id[3] != '0' ||
	    vol->id[4] != '1')
		return (-1);
	return 0;
}

static void
iso9660_dump_primary_volume(primary_volume_descriptor_t pri)
{
	int i;

	kprintf("ISO9660 primary volume\r\n");

	kprintf("system identifier [");
	for (i = 0; i < 32; i++)
		kprintf("%c", pri->sys_id[i]);
	kprintf("]\r\n");

	kprintf("volume identifier [");
	for (i = 0; i < 32; i++)
		kprintf("%c", pri->vol_id[i]);
	kprintf("]\r\n");

	kprintf("%u blks (%u MB)\r\n",
		pri->vol_space_size_le,
		pri->vol_space_size_le * ATAPI_SECTOR_SIZE / 0x100000);
}

void
iso9660_init()
{
	uint8_t buf[ATAPI_SECTOR_SIZE];
	atap_t atap = ata_get_primary_partition();
	int result;

	memset(buf, 0, ATAPI_SECTOR_SIZE);
	read_blk(atap, RESERVED_SECTORS, buf);

	result = iso9660_verify_primary_volume((volume_descriptor_t) buf);
	if (result < 0) {
		kprintf("ISO9660 primary volume not found\r\n");
		halt();
	}
	iso9660_dump_primary_volume(
		(primary_volume_descriptor_t)
		(buf + sizeof(struct volume_descriptor)));
}
