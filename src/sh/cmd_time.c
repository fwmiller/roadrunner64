#include <stdio.h>
#include <sys/sh.h>
#include <sys/time.h>
#include <sys/tmr.h>

void
cmd_time() {
    printf("tmr     %u\r\n", tmrread());
    printf("tick    %u\r\n", tick);

    uint64_t uptime = tick * tmrtick();
    printf("uptime  %02u:%02u:%03u\r\n", uptime / (1000000 * 60),
           (uptime / 1000000) % 60, (uptime / 1000) % 1000);
}
