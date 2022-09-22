#include <stdio.h>
#include <sys/fs.h>
#include <sys/shell.h>

void
cmd_ft() {
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        fd_t f = &(filetab[i]);
        if (f->flags & FD_FLAGS_ALLOC) {
            if (f->flags & FD_FLAGS_ISROOTDIR || f->flags & FD_FLAGS_ISDIR)
                set_color(CYAN);

            printf("%s", f->path);

            if (f->flags & FD_FLAGS_ISROOTDIR || f->flags & FD_FLAGS_ISDIR)
                set_color(NC);

            printf("\r\n");
        }
    }
}
