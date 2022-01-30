#include <errno.h>
#include <fcntl.h>
#if _DEBUG
#include <stdio.h>
#endif
#include <sys/isofs.h>

int
open(const char *pathname, int flags)
{
	int isdir = 0;

	/* Locate file in ISO9660 file system on primary volume */
	lba_t lba = isofs_find(pathname, isofs_get_root_dir(),
			       ATAPI_SECTOR_SIZE, &isdir);
	if (lba == 0)
		return ENOENT;
#if _DEBUG
	printf("found ");
	if (isdir)
		printf("directory ");
	else
		printf("file ");
	printf("lba %u\r\n", lba);
#endif
	return 0;
}
