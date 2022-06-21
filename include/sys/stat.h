#ifndef __STAT_H
#define __STAT_H

struct stat {
    off_t st_size;
};

int fstat(int fd, struct stat *buf);

#endif
