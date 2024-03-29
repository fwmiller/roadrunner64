#include <errno.h>
#include <fcntl.h>
#if _DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <sys/fs.h>
#include <sys/isofs.h>

int
open(const char *pathname, int flags) {
    int isdir = 0;
    int filesize = 0;
    int fd = (-1);

    /* Locate file in ISO9660 file system on primary volume */
    lba_t lba = isofs_find(pathname, isofs_get_root_dir(), ATAPI_SECTOR_SIZE,
                           &isdir, &filesize);
    if (lba == 0) {
#if _DEBUG
        printf("not found\r\n");
#endif
        return ENOENT;
    }
#if _DEBUG
    printf("found ");
    if (isdir)
        printf("directory ");
    else
        printf("file ");
    printf("lba %u size %d\r\n", lba, filesize);
#endif
    if (isdir)
        return EISDIR;

    /* Allocate a file descriptor slot */
    fd = file_desc_alloc_slot();
    if (fd < 0)
        return fd;

    fd_t f = &(filetab[fd]);
    strcpy(f->path, pathname);
    f->lba = lba;
    f->size = filesize;

    return fd;
}
