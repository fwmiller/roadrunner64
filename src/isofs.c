#include <stdio.h>
#include <string.h>
#include <sys/ata.h>
#include <sys/isofs.h>
#include <sys/sys.h>

typedef uint32_t lba_t;

static uint8_t pri_vol_desc[ATAPI_SECTOR_SIZE];
static uint8_t path_table[ATAPI_SECTOR_SIZE];
static uint8_t root_dir[ATAPI_SECTOR_SIZE];

/*
 * buf must be at least ATAPI_SECTOR_SIZE = 2048 bytes and is assumed to
 * be zeroed
 */
static int
isofs_read_blk(atap_t part, lba_t lba, uint8_t * buf)
{
	struct seek seekargs;
	int result;

	kprintf("blkno %u\r\n", lba);

	/* Convert lba to sector */
	uint32_t sectorno = lba << 2;

	/* Seek to sector */
	seekargs.offset = sectorno;
	seekargs.whence = SEEK_SET;
	result = ata_seek(part->atad, &seekargs);
	if (result < 0)
		return (-1);

	/* Read sector data */
	return ata_read(part, buf, ATAPI_SECTOR_SIZE);
}

static int
isofs_verify_primary_volume(volume_descriptor_t vol)
{
	if (vol->type != VOLUME_DESCRIPTOR_TYPE_PRIMARY ||
	    vol->id[0] != 'C' || vol->id[1] != 'D' || vol->id[2] != '0' ||
	    vol->id[3] != '0' || vol->id[4] != '1')
		return (-1);
	return 0;
}

void
isofs_init()
{
	atap_t atap = ata_get_primary_partition();
	primary_volume_descriptor_t pri;
	int result;

	/* Read primary volume descriptor */
	memset(pri_vol_desc, 0, ATAPI_SECTOR_SIZE);
	isofs_read_blk(atap, RESERVED_SECTORS, pri_vol_desc);

	result = isofs_verify_primary_volume((volume_descriptor_t)
					     pri_vol_desc);
	if (result < 0) {
		kprintf("ISO9660 primary volume not found\r\n");
		halt();
	}
	pri = (primary_volume_descriptor_t)
	    (pri_vol_desc + sizeof(struct volume_descriptor));
#if 0
	isofs_dump_primary_volume(pri);
#endif
	/* Read path table */
	memset(path_table, 0, ATAPI_SECTOR_SIZE);
#if 0
	isofs_read_blk(atap, pri->path_table_loc_le, path_table);
	isofs_dump_path_table(pri, path_table);
#endif
	isofs_dump_directory((uint8_t *) pri->root_dir_entry,
			     sizeof(pri->root_dir_entry));

	/* Read / directory */
	kprintf("\r\n/\r\n");
	directory_record_t rec = (directory_record_t) pri->root_dir_entry;
	memset(root_dir, 0, ATAPI_SECTOR_SIZE);
	isofs_read_blk(atap, rec->lba_le, root_dir);
	isofs_dump_directory((uint8_t *) root_dir, ATAPI_SECTOR_SIZE);

	static uint8_t dir[ATAPI_SECTOR_SIZE];

	/* Read /boot directory */
	kprintf("\r\n/boot\r\n");
	memset(dir, 0, ATAPI_SECTOR_SIZE);
	isofs_read_blk(atap, 21, dir);
	isofs_dump_directory(dir, ATAPI_SECTOR_SIZE);

	/* Read /boot/grub directory */
	kprintf("\r\n/boot/grub\r\n");
	memset(dir, 0, ATAPI_SECTOR_SIZE);
	isofs_read_blk(atap, 22, dir);
	isofs_dump_directory(dir, ATAPI_SECTOR_SIZE);
}
