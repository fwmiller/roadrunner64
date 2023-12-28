#include <stdio.h>
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
    void *ptr = (void *) mem_alloc(size);
#if 1
    printf("malloc: ptr = 0x%016x\r\n", (unsigned long) ptr);
#endif
    return ptr;
}

// These are required to be able to link g++
void *__gxx_personality_v0 = 0;
void *_Unwind_Resume = 0;

void *
operator new(size_t size) {
    return malloc(size);
}

void
operator delete(void *ptr) {
    return;
}
