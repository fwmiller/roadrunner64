#if _DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <sys/isofs.h>

static void
nextelem(const char *ln, int *pos, char *arg) {
    int i;
    char ch;

    /* Consume leading slashes */
    while (ln[*pos] == '/')
        (*pos)++;

    for (i = 0;; (*pos)++) {
        ch = ln[*pos];
        if (ch == '\0' || ch == '/')
            break;
        arg[i++] = ch;
    }
}

/*
 * This routine uses a specified full path to search the file system
 * directories for a file or directory
 */
lba_t
isofs_find(const char *path, uint8_t *rootdir, int size, int *isdir) {
    uint8_t *dir = rootdir;
    uint8_t buf[ATAPI_SECTOR_SIZE];
    char elem[80];
    lba_t lba = 0;
    int result;

#if _DEBUG
    printf("isofs_find: path [%s]\r\n", path);
#endif
    for (int pos = 0;;) {
        if (path[pos++] != '/')
            break;

        memset(elem, 0, 80);
        nextelem(path, &pos, elem);
#if _DEBUG
        printf("isofs_find: elem [%s]\r\n", elem);
#endif
        lba = isofs_search_dir(elem, dir, size, isdir);
        if (lba == 0)
            return 0;

        /* Read next directory */
        dir = buf;
        size = ATAPI_SECTOR_SIZE;
        memset(buf, 0, size);
        atap_t atap = ata_get_primary_partition();
        result = isofs_read_blk(atap, lba, buf);
        if (result < 0)
            return 0;
    }
    return lba;
}
