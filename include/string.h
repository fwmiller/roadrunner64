#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

void *memset(void *b, int c, size_t n);
void *memcpy(void *dest, void *src, size_t n);
char *strcpy(char *dst, const char *src);
char *strerror(int errno);
size_t strlen(const char *s);
int strncmp(const char *s1, const char *s2, size_t n);

#endif
