#include <stdio.h>
#include <sys/sh.h>
#include <sys/time.h>
#include <sys/tmr.h>

void
cmd_time() {
    printf("tmr     %u\r\n", tmrread());
    printf("tick    %u\r\n", tick);

    unsigned uptime = tick * tmrtick();
    printf("uptime  %u seconds\r\n", uptime / 1000000);
}
