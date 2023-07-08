#include <stdio.h>
#include <sys/tsc.h>

void
cmd_tsc() {
    printf("tsc %u\r\n", tscread());
}
