#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

int memcmp(const void *s1, const void *s2, size_t n);
void *memset(void *b, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
char *strcpy(char *dst, const char *src);
char *strcat(char *dest, const char *src);
char *strerror(int errno);
size_t strlen(const char *s);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

#endif
