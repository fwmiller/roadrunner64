#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/cli.h>
#include <unistd.h>

void
cmd_cat(char *cmdline, int *pos) {
    char arg[CMD_LINE_LEN];

    memset(arg, 0, CMD_LINE_LEN);
    nextarg(cmdline, pos, " ", arg);

    int fd = open(arg, 0);
    if (fd < 0) {
        printf("open file %s failed (%s)\r\n", arg, strerror(fd));
        return;
    }

    for (char ch = 0;;) {
        int len = read(fd, &ch, 1);
        if (len <= 0)
            break;
        printf("%c", ch);
    }
}
