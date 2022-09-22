#include <stdio.h>
#include <sys/fs.h>
#include <sys/shell.h>

extern uint64_t stack_bottom, stack_top;

void
cmd_stack() {
    printf("bottom 0x%016x\r\n", stack_bottom);
    printf("top    0x%016x\r\n", stack_top);
    printf("size   %u (MB)\r\n", (stack_top - stack_bottom) / 0x100000);
}
