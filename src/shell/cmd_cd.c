#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/path.h>
#include <sys/shell.h>
#include <unistd.h>

void
cmd_cd(char *pwd, int pwdlen, char *cmdline, int *pos) {
    char arg[CMD_LINE_LEN];

    memset(arg, 0, CMD_LINE_LEN);
    nextarg(cmdline, pos, " ", arg);

    if (strlen(arg) == 0)
        return;

    else if (strlen(arg) > 0 && arg[0] != '/') {
        path_prepend(pwd, arg);
        path_eval(arg);
    }
    /* Try to open directory */
#if 0
    int fd = open(arg, 0);
    if (fd < 0) {
        printf("open file %s failed\r\n", arg);
        return;
    }
#endif
    /* Update the pwd */
}
