#include <stdarg.h>
#include <stdio.h>
#include <sys/sys.h>

int
sprintf(char *s, const char *fmt, ...) {
    va_list args;
    int pos = 0;

    va_start(args, fmt);
    print(s, &pos, fmt, args);
    return 0;
}
