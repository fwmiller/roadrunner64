#ifndef __DIRENT_H
#define __DIRENT_H

#include <sys/fs.h>

#define DT_UNDEF 0
#define DT_REG 1
#define DT_DIR 2

#define DE_NAME_LEN 256

struct dirent {
    uint8_t d_type;
    uint8_t d_size;
    uint8_t d_name[DE_NAME_LEN];
};

typedef struct file_desc DIR;

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);

#endif
