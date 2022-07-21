#include <dirent.h>
#if _DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <sys/isofs.h>

DIR *
opendir(const char *name) {
    int isdir = 0;
    int filesize = 0;
    int fd = (-1);

    /* Locate file in ISO9660 file system on primary volume */
    lba_t lba = isofs_find(name, isofs_get_root_dir(), ATAPI_SECTOR_SIZE,
                           &isdir, &filesize);
    if (lba == 0)
        return NULL;

#if _DEBUG
    printf("found ");
    if (isdir)
        printf("directory ");
    else
        printf("file ");
    printf("lba %u size %d\r\n", lba, filesize);
#endif
    if (!isdir)
        return NULL;

    /* Allocate a file descriptor slot */
    fd = file_desc_alloc_slot();
    if (fd < 0)
        return NULL;

    fd_t f = &(filetab[fd]);
    f->flags |= FD_FLAGS_ISDIR;
    f->lba = lba;
    f->size = filesize;

    return (DIR *) f;
}
