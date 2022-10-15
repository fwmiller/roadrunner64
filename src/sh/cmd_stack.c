#include <stdint.h>
#include <stdio.h>
#include <sys/sh.h>

extern void *stack_top;
extern void *stack_bottom;

uint64_t getrsp();

void
cmd_stack() {
    uint64_t rsp = getrsp();
    printf("top       0x%016x\r\n", &stack_top);
    printf("rsp       0x%016x\r\n", rsp);
    printf("bottom    0x%016x\r\n", &stack_bottom);
    printf("used        %16u\r\n", ((uint64_t) &stack_top) - rsp);
    printf("remaining   %16u\r\n", rsp - (uint64_t) &stack_bottom);
}
