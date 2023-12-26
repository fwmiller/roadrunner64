#ifndef __STDDEF_H
#define __STDDEF_H

#include <stdint.h>

#define NULL 0
#define offsetof(st, m) __builtin_offsetof(st, m)

typedef int64_t ptrdiff_t;
#if 0
typedef uint16_t wchar_t;
#endif
typedef uint64_t size_t;

#endif
