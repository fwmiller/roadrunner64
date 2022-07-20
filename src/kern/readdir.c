#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fs.h>
#include <unistd.h>

static struct dirent de;

struct dirent *
readdir(DIR *dirp) {
    uint8_t buf[256];

    memset(&de, 0, sizeof(struct dirent));
    memset(buf, 0, 256);

    /* Read directory record size */
    read(((fd_t) dirp)->fd, buf, 1);

    /* Read directory record file id */
    read(((fd_t) dirp)->fd, buf + 1, ((size_t) buf[0]) - 1);

    isofs_dump_directory(buf, (int) buf[0]);

    return NULL;
}
