#ifndef __FS_H
#define __FS_H

#include <stdint.h>

#define MAX_OPEN_FILES 16

struct file_desc {
    uint8_t *buf;
    int pos;
};

typedef struct file_desc *fd_t;

extern struct file_desc filetab[];

void fs_init();
void file_desc_clear(fd_t fd);

#endif
