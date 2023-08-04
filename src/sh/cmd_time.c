#include <stdio.h>
#include <sys/sh.h>
#include <sys/time.h>
#include <sys/tmr.h>

void
cmd_time() {
    printf("tmr     %u\r\n", tmrread());
    printf("tick    %u\r\n", tick);

    uint64_t uptime = tick * tmrtick();
    uint64_t dur = uptime / 1000000;
    unsigned days = dur / (24 * 3600);

    printf("uptime  %u day", days);
    if (days != 1)
        printf("s");

    printf(" %u hrs %u min %u sec\r\n", (dur / 3600) % 24, (dur / 60) % 60,
           dur % 60);
}
