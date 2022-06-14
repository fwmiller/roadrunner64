#include <errno.h>
#include <stdlib.h>
#include <sys/fs.h>
#include <sys/isofs.h>

struct file_desc filetab[MAX_OPEN_FILES];

void
file_desc_clear(fd_t fd) {
    fd->flags = 0;
    fd->lba = 0;
    fd->pos = 0;
}

int
file_desc_alloc_slot() {
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        fd_t fd = &(filetab[i]);
        if (fd->flags & FD_FLAGS_ALLOC)
            continue;

        fd->flags |= FD_FLAGS_ALLOC;
        return i;
    }
    return ENFILE;
}

void
fs_init() {
    ata_init();
    isofs_init();

    /* Clear the file descriptor table */
    for (int i = 0; i < MAX_OPEN_FILES; i++)
        file_desc_clear(&(filetab[i]));
}
