#include <stdio.h>
#include <sys/ata.h>
#include <sys/isofs.h>

void
isofs_dump_primary_volume(primary_volume_descriptor_t pri)
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

	kprintf("logical blk size %u bytes\r\n", pri->logical_blk_size_le);
	kprintf("path table size %u bytes\r\n", pri->path_table_size_le);
	kprintf("path table location blk %u\r\n", pri->path_table_loc_le);
}
