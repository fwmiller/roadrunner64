#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sys.h>

void
printf(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);

    print(NULL, NULL, fmt, args);
}
