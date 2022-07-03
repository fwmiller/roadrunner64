#include <errno.h>
#if _DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <sys/ata.h>
#include <sys/fs.h>
#include <unistd.h>

ssize_t
read(int fd, void *buf, size_t count) {
    fd_t f;
    int n = 0;
    int nleft = count;
    int bufpos, len, result;

    if (buf == NULL)
        return EFAIL;

    if (fd < 0 || fd >= MAX_OPEN_FILES)
        return EBADF;

    f = &(filetab[fd]);

    /* Read the block containing the file position */
    lba_t lba = f->lba + (f->pos / ATAPI_SECTOR_SIZE);
    result = isofs_read_blk(ata_get_primary_partition(), lba, f->buf);
    if (result < 0) {
#if _DEBUG
        printf("read: isofs_read_blk() failed\r\n");
#endif
        return result;
    }
    /* Copy data from file buffer */
    bufpos = f->pos % ATAPI_SECTOR_SIZE;
    len = ATAPI_SECTOR_SIZE - bufpos;
    if (len >= nleft)
        len = nleft;
    memcpy(buf + n, f->buf + bufpos, len);

    /*
     * Advance file descriptor position checking whether enough
     * data has been read or the end of file has been reached
     */

    return EFAIL;
}
