#include <stdint.h>
#include <stdio.h>
#include <sys/sh.h>

uint64_t
getrsp() {
    __asm__("movq %rsp, %rax");
}

void
cmd_stack() {
    printf("rsp 0x%016x\r\n", getrsp());
}
