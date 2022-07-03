#ifndef __FS_H
#define __FS_H

#include <sys/isofs.h>

#define MAX_OPEN_FILES 16

#define FD_FLAGS_ISDIR 0x01
#define FD_FLAGS_ALLOC 0x02

struct file_desc {
    uint8_t flags;
    lba_t lba;
    unsigned size;
    int pos;
    uint8_t buf[ATAPI_SECTOR_SIZE];
};

typedef struct file_desc *fd_t;

extern struct file_desc filetab[];

void fs_init();
void file_desc_clear(fd_t f);
int file_desc_alloc_slot();

#endif
