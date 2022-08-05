#include <dirent.h>
#if _DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <sys/isofs.h>

DIR *
opendir(const char *name) {
    int isdir = 0;
    int filesize = 0;
    int fd = (-1);

    /* Check for root directory */
    if (strcmp(name, "/") == 0) {
        fd = file_desc_alloc_slot();
        if (fd < 0)
            return NULL;
#if _DEBUG
        printf("found root directory\r\n");
#endif
        fd_t f = &(filetab[fd]);
        f->flags |= FD_FLAGS_ISROOTDIR;
        f->size = isofs_get_root_dir_size();
        return (DIR *) f;
    }
    /* Not root directory */

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
    strcpy(f->path, name);
    f->lba = lba;
    f->size = filesize;

    return (DIR *) f;
}
