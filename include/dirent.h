#ifndef __DIRENT_H
#define __DIRENT_H

#include <sys/fs.h>

typedef struct file_desc DIR;

DIR *opendir(const char *name);

#endif
