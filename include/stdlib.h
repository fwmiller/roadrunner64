#ifndef __STDLIB_H
#define __STDLIB_H

#include <stddef.h>

#define RAND_MAX 0xffffffff

int atoi(const char *nptr);
long atol(const char *nptr);
long long atoll(const char *nptr);

int rand(void);

void *malloc(size_t size);

void *operator new(size_t size);
void operator delete(void *ptr);

#endif
