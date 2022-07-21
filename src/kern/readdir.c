#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fs.h>
#include <sys/isofs.h>
#include <unistd.h>

static struct dirent de;

struct dirent *
readdir(DIR *dirp) {
    fd_t f = (fd_t) dirp;
    uint8_t buf[256];

    memset(&de, 0, sizeof(struct dirent));
    memset(buf, 0, 256);

    /* Read directory record size */
    ssize_t n = read(f->fd, buf, 1);
    if (n <= 0)
        return NULL;

    /* Read directory record file id */
    n = read(f->fd, buf + 1, ((size_t) buf[0]) - 1);
    if (n <= 0)
        return NULL;
#if _DEBUG
    isofs_dump_directory(buf, (int) buf[0]);
#endif

    /* Load the directory entry record */
    directory_record_t dr = (directory_record_t) buf;
    if (dr->flags & FILE_FLAGS_DIRECTORY)
        de.d_type = DT_DIR;
    else
        de.d_type = DT_REG;

    de.d_size = dr->size_le;

    char *name = (char *) buf + sizeof(struct directory_record);
    if (name[0] == 0)
        memcpy(de.d_name, ".", 1);
    else if (name[0] == 1)
        memcpy(de.d_name, "..", 2);
    else
        memcpy(de.d_name, name, dr->file_id_len);

    return &de;
}
