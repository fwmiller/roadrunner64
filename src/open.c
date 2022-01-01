#include <fcntl.h>
#include <sys/isofs.h>

int
open(const char *pathname, int flags)
{
	/* Locate file in ISO9660 file system on primary volume */
	lba_t lba = isofs_find(pathname, isofs_get_root_dir(),
			       ATAPI_SECTOR_SIZE);
	if (lba == 0)
		return (-1);

	return 0;
}
