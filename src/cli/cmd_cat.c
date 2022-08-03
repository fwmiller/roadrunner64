#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/cli.h>
#include <unistd.h>

void
cmd_cat(char *pwd, char *cmdline, int *pos) {
    char arg[CMD_LINE_LEN];

    memset(arg, 0, CMD_LINE_LEN);
    nextarg(cmdline, pos, " ", arg);

    if (strlen(arg) == 0)
        strcpy(arg, pwd);

    else if (strlen(arg) > 0 && arg[0] != '/') {
        char tmp[CMD_LINE_LEN];
        memset(tmp, 0, CMD_LINE_LEN);
        strcpy(tmp, pwd);
        strcat(tmp, "/");
        strcat(tmp, arg);
        memset(arg, 0, CMD_LINE_LEN);
        strcpy(arg, tmp);
    }
    int fd = open(arg, 0);
    if (fd < 0) {
        printf("open file %s failed\r\n", arg);
        return;
    }

    for (char ch = 0;;) {
        int len = read(fd, &ch, 1);
        if (len <= 0)
            break;
        printf("%c", ch);
    }
}
