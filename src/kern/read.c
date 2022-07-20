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
    int n, nleft, bufpos, len, result;

    if (buf == NULL)
        return EFAIL;

    if (fd < 0 || fd >= MAX_OPEN_FILES)
        return EBADF;

    printf("read: count %u\r\n", count);

    f = &(filetab[fd]);

    for (n = 0, nleft = count; f->pos < f->size && nleft > 0;) {
#if _DEBUG
        printf("\r\nread: f->pos %d f->size %d f->lba %u\r\n", f->pos,
               f->size, f->lba);
        printf("read: n %d nleft %d\r\n", n, nleft);
#endif
        /* Read the block containing the file position */
        lba_t lba = f->lba + (f->pos / ATAPI_SECTOR_SIZE);
        result = isofs_read_blk(ata_get_primary_partition(), lba, f->buf);
        if (result < 0) {
#if _DEBUG
            printf("read: isofs_read_blk() lba %u failed\r\n", lba);
#endif
            return result;
        }
        /* Copy data from file buffer */
        bufpos = f->pos % ATAPI_SECTOR_SIZE;
        len = nleft;
        if (len > (ATAPI_SECTOR_SIZE - bufpos))
            len = ATAPI_SECTOR_SIZE - bufpos;
#if _DEBUG
        printf("read: bufpos %d len %d\r\n", bufpos, len);
#endif
        memcpy(buf + n, f->buf + bufpos, len);

        /* Update various state variables */
        f->pos += len;
        n += len;
        nleft -= len;
    }
    return (ssize_t) n;
}
