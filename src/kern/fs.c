#include <stdlib.h>
#include <sys/fs.h>
#include <sys/isofs.h>

struct file_desc filetab[MAX_OPEN_FILES];

void
file_desc_clear(fd_t fd) {
    fd->buf = NULL;
    fd->pos = 0;
}

void
fs_init() {
    ata_init();
    isofs_init();

    /* Clear the file descriptor table */
    for (int i = 0; i < MAX_OPEN_FILES; i++)
        file_desc_clear(&(filetab[i]));
}
