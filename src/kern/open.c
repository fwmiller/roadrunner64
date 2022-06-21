#include <errno.h>
#include <fcntl.h>
#if _DEBUG
#include <stdio.h>
#endif
#include <sys/fs.h>
#include <sys/isofs.h>

int
open(const char *pathname, int flags) {
    int isdir = 0;
    int fd = (-1);

    /* Locate file in ISO9660 file system on primary volume */
    lba_t lba =
        isofs_find(pathname, isofs_get_root_dir(), ATAPI_SECTOR_SIZE, &isdir);
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
    if (isdir)
        return EISDIR;

    /* Allocate a file descriptor slot */
    fd = file_desc_alloc_slot();
    if (fd < 0)
        return fd;

    fd_t f = &(filetab[fd]);
    f->lba = lba;

    return fd;
}
