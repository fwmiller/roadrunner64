#include <sys/fs.h>
#include <sys/isofs.h>

void
fs_init()
{
	ata_init();
	isofs_init();
}
