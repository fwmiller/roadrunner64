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
	int result;

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

	kprintf("logical blk size %u bytes\r\n",
		pri->logical_blk_size_le);
	kprintf("path table size %u bytes\r\n",
		pri->path_table_size_le);
	kprintf("path table location blk %u\r\n", pri->path_table_loc);
}

static void
dump_path_table_record(path_table_record_t rec)
{
	kprintf("%10u ", rec->dir_id_len);
	kprintf("%15u ", rec->ext_att_rec_len);
	kprintf("%12u ", rec->lba);
	kprintf("%12u ", rec->parent_dirno);

	for (int i = 0; i < rec->dir_id_len; i++) {
		char *str = ((char *) rec) +
			sizeof(struct path_table_record);
		kprintf("%c", *(str + i));
	}
	kprintf("\r\n");
}

static void
dump_path_table(primary_volume_descriptor_t pri, uint8_t *buf)
{
	kprintf("dir_id_len ext_att_rec_len lba          ");
	kprintf("parent_dirno path\r\n");

	for (int pos = 0; pos < pri->path_table_size_le;) {
		path_table_record_t rec =
			(path_table_record_t) (buf + pos);
		dump_path_table_record(rec);

		unsigned reclen = sizeof(struct path_table_record) +
			rec->dir_id_len;
		if (rec->dir_id_len % 2 == 1)
			reclen++;
		pos += reclen;
	}
}

static uint8_t pri_vol_desc[ATAPI_SECTOR_SIZE];

void
iso9660_init()
{
	uint8_t buf[ATAPI_SECTOR_SIZE];
	atap_t atap = ata_get_primary_partition();
	primary_volume_descriptor_t pri;
	int result;

	/* Read primary volume descriptor */
	memset(pri_vol_desc, 0, ATAPI_SECTOR_SIZE);
	read_blk(atap, RESERVED_SECTORS, pri_vol_desc);

	result = iso9660_verify_primary_volume(
			(volume_descriptor_t) pri_vol_desc);
	if (result < 0) {
		kprintf("ISO9660 primary volume not found\r\n");
		halt();
	}
	pri = (primary_volume_descriptor_t)
		(pri_vol_desc + sizeof(struct volume_descriptor));

	iso9660_dump_primary_volume(pri);

	/* Read path table */
	memset(buf, 0, ATAPI_SECTOR_SIZE);
	read_blk(atap, pri->path_table_loc, buf);
	dump_path_table(pri, buf);
}
