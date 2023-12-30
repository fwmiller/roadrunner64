#include <inet/buf.h>
#include <stdio.h>
#include <sys/sh.h>

void
cmd_bp() {
    printf("nbufs %d\r\n", bp->get_nbufs());
    printf("free  %d\r\n", bp->get_nfree());
}
