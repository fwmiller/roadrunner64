#include <errno.h>
#include <sys/fs.h>
#include <unistd.h>

ssize_t
read(int fd, void *buf, size_t count) {
    if (fd < 0 || fd >= MAX_OPEN_FILES)
        return EBADF;

    fd_t f = &(filetab[fd]);

    /* Get file length and file descriptor position */

    /* Get the size to read in */

    /* Read the block containing the file descriptor position */

    /* Copy data from file buffer */

    /*
     * Advance file descriptor position checking whether enough
     * data has been read or the end of file has been reached
     */

    return (-1);
}
