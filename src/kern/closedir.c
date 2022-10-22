#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

int
closedir(DIR *dirp) {
    if (dirp == NULL)
        return EBADF;

    int fd = ((fd_t) dirp)->fd;

    if (!(filetab[fd].flags & FD_FLAGS_ISROOTDIR) &&
        !(filetab[fd].flags & FD_FLAGS_ISDIR))
        return ENOTDIR;

    file_desc_clear(&(filetab[fd]));
    return 0;
}
