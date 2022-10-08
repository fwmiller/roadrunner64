#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/path.h>
#include <sys/sh.h>

void
cmd_cd(char *pwd, int pwdlen, char *cmdline, int *pos) {
    char arg[CMD_LINE_LEN];

    memset(arg, 0, CMD_LINE_LEN);
    nextarg(cmdline, pos, " ", arg);

    if (strlen(arg) == 0)
        return;

    else if (strlen(arg) > 0 && arg[0] != '/')
        path_prepend(pwd, arg, CMD_LINE_LEN);

#if _DEBUG_SHELL
    printf("cmd_cd: path [%s]\r\n", arg);
#endif
    path_eval(arg, CMD_LINE_LEN);

    /* Try to open directory */
    DIR *dir = opendir(arg);
    if (dir == NULL) {
        printf("open directory %s failed\r\n", arg);
        return;
    }
    /* Update the pwd */
    memset(pwd, 0, pwdlen);
    strcpy(pwd, arg);
}
