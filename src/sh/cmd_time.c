#include <stdio.h>
#include <sys/sh.h>
#include <sys/tmr.h>

void
cmd_time() {
    printf("tmr %u\r\n", tmrread());
}
