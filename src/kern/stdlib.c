#include <stdlib.h>
#include <sys/mem.h>
#include <sys/tsc.h>

int
atoi(const char *nptr) {
    return 0;
}

long
atol(const char *nptr) {
    return 0;
}

long long
atoll(const char *nptr) {
    return 0;
}

int
rand(void) {
    return tscread();
}

void *
malloc(size_t size) {
    return (void *) mem_alloc(size);
}
