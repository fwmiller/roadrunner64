#include <stdio.h>
#include <sys/ata.h>
#include <sys/fs.h>
#include <sys/isofs.h>

void
fs_init()
{
	ata_init();
	isofs_init();

	lba_t lba =
	    isofs_find("/boot/grub/grub.cfg;1", root_dir, ATAPI_SECTOR_SIZE);
	if (lba == 0)
		printf("fs_init: not found\r\n");
	else
		printf("fs_init: found lba %u\r\n", lba);

}
