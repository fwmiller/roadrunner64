#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/path.h>
#include <sys/sh.h>
#include <unistd.h>

void
cmd_cat(char *pwd, char *cmdline, int *pos) {
    char arg[CMD_LINE_LEN];

    memset(arg, 0, CMD_LINE_LEN);
    nextarg(cmdline, pos, " ", arg);

    if (strlen(arg) == 0)
        strcpy(arg, pwd);

    else if (strlen(arg) > 0 && arg[0] != '/')
        path_prepend(pwd, arg, CMD_LINE_LEN);

#if _DEBUG_SHELL
    printf("cmd_cat: path [%s]\r\n", arg);
#endif
    path_eval(arg, CMD_LINE_LEN);

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
    close(fd);
}
