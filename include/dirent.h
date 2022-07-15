#ifndef __DIRENT_H
#define __DIRENT_H

#include <sys/fs.h>

struct dirent {
    uint8_t d_type;
    uint8_t d_size;
};

typedef struct file_desc DIR;

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);

#endif
