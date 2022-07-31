#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/cli.h>
#include <sys/path.h>

void
cmd_ls(char *pwd, char *cmdline, int *pos) {
    char arg[CMD_LINE_LEN];

    memset(arg, 0, CMD_LINE_LEN);
    nextarg(cmdline, pos, " ", arg);

    if (strlen(arg) == 0)
        strcpy(arg, pwd);

    else if (strlen(arg) > 0 && arg[0] != '/') {
        char tmp[CMD_LINE_LEN];
        memset(tmp, 0, CMD_LINE_LEN);
        path_cat(pwd, arg, tmp);
        memset(arg, 0, CMD_LINE_LEN);
        strcpy(arg, tmp);
    }
    DIR *dir = opendir(arg);
    if (dir == NULL) {
        printf("open directory %s failed\r\n", arg);
        return;
    }
    struct dirent *de;
    while ((de = readdir(dir)) != NULL) {
        printf("%s", de->d_name);
        if (de->d_type == DT_DIR) {
            printf("/");
        }
        printf(" ");
    }
    printf("\r\n");
}
