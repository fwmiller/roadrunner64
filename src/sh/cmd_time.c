#include <stdio.h>
#include <sys/sh.h>
#include <sys/time.h>
#include <sys/tmr.h>

void
cmd_time() {
    printf("tmr     %u\r\n", tmrread());
    printf("tick    %u\r\n", tick);

    uint64_t uptime = tick * tmrtick();

    uint64_t dur = uptime / 1000;

    printf("uptime  %u days %u hrs %u min %u sec\r\n", dur / (24 * 360000),
           (dur / 360000) % 24, (dur / 60000) % 60, (dur / 1000) % 60);
}
