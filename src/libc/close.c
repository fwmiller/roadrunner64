#include <errno.h>
#include <sys/fs.h>
#include <unistd.h>

int
close(int fd) {
    if (fd < 0 || fd >= MAX_OPEN_FILES || filetab[fd].fd != fd)
        return EBADF;

    if (filetab[fd].flags & FD_FLAGS_ISROOTDIR ||
        filetab[fd].flags & FD_FLAGS_ISDIR)
        return EISDIR;

    file_desc_clear(&(filetab[fd]));
    return 0;
}
