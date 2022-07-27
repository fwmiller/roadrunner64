#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/cli.h>
#include <sys/sys.h>
#include <unistd.h>

void
cmd_hexdump(char *cmdline, int *pos) {
    char arg[CMD_LINE_LEN];

    memset(arg, 0, CMD_LINE_LEN);
    nextarg(cmdline, pos, " ", arg);

    int fd = open(arg, 0);
    if (fd < 0) {
        printf("open file %s failed (%s)\r\n", arg, strerror(fd));
        return;
    }
    char buf[16];
    memset(buf, 0, 16);
    for (int i = 0;; i += 16) {
        int len = read(fd, buf, 16);
        if (len <= 0)
            break;
        printf("%08x  ", i);
        bufdump(buf, 16);
    }
}
