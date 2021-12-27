#include <stdio.h>
#include <sys/ata.h>
#include <sys/fs.h>
#include <sys/isofs.h>

void
fs_init()
{
	ata_init();
	isofs_init();

	lba_t lba = isofs_find("/boot.cat", root_dir, ATAPI_SECTOR_SIZE);
	if (lba == 0)
		printf("fs_init: /boot.cat not found\r\n");
	else
		printf("fs_init: /boot.cat found lba %u\r\n", lba);

}
