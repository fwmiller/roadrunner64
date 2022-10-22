#ifndef __UNISTD_H
#define __UNISTD_H

#include <stddef.h>
#include <sys/types.h>

ssize_t read(int fd, void *buf, size_t count);
int close(int fd);

#endif
