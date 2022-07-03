#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fs.h>
#include <sys/isofs.h>

struct file_desc filetab[MAX_OPEN_FILES];

void
file_desc_clear(fd_t f) {
    f->flags = 0;
    f->lba = 0;
    f->size = 0;
    f->pos = 0;
    memset(f->buf, 0, ATAPI_SECTOR_SIZE);
}

int
file_desc_alloc_slot() {
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        fd_t f = &(filetab[i]);
        if (f->flags & FD_FLAGS_ALLOC)
            continue;

        f->flags |= FD_FLAGS_ALLOC;
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
