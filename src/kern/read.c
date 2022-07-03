#include <errno.h>
#if _DEBUG
#include <stdio.h>
#endif
#include <sys/ata.h>
#include <sys/fs.h>
#include <unistd.h>

ssize_t
read(int fd, void *buf, size_t count) {
    if (fd < 0 || fd >= MAX_OPEN_FILES)
        return EBADF;

    fd_t f = &(filetab[fd]);

    /* Read the block containing the file position */
    lba_t lba = f->lba + (f->pos / ATAPI_SECTOR_SIZE);
    int result = isofs_read_blk(ata_get_primary_partition(), lba, f->buf);
    if (result < 0) {
#if _DEBUG
        printf("read: isofs_read_blk() failed\r\n");
#endif
        return result;
    }
    /* Copy data from file buffer */

    /*
     * Advance file descriptor position checking whether enough
     * data has been read or the end of file has been reached
     */

    return (-1);
}
