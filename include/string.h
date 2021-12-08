#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

size_t strlen(const char *s);
int strncmp(const char *s1, const char *s2, size_t n);
void *memset(void *b, int c, size_t len);

#endif
