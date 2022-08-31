#include <stdio.h>
#include <sys/fs.h>

void
cmd_ft() {
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        fd_t f = &(filetab[i]);
        if (f->flags & FD_FLAGS_ALLOC) {
            printf("%s", f->path);
            if (f->flags & FD_FLAGS_ISDIR || f->flags & FD_FLAGS_ISROOTDIR)
                printf("/");
            printf("\r\n");
        }
    }
}
