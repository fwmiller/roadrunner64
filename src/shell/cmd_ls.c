#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/path.h>
#include <sys/shell.h>

void
cmd_ls(char *pwd, char *cmdline, int *pos) {
    char arg[CMD_LINE_LEN];

    memset(arg, 0, CMD_LINE_LEN);
    nextarg(cmdline, pos, " ", arg);

    if (strlen(arg) == 0)
        strcpy(arg, pwd);

    else if (strlen(arg) > 0 && arg[0] != '/') {
        path_prepend(pwd, arg, CMD_LINE_LEN);
        path_eval(arg, CMD_LINE_LEN);
    }
    DIR *dir = opendir(arg);
    if (dir == NULL) {
        printf("open directory %s failed\r\n", arg);
        return;
    }
    struct dirent *de;
    while ((de = readdir(dir)) != NULL) {
        if (strcmp((char *) de->d_name, ".") == 0 ||
            strcmp((char *) de->d_name, "..") == 0)
            continue;

        if (de->d_type == DT_DIR)
            printf("%s", CYAN);
        printf("%s", de->d_name);
        if (de->d_type == DT_DIR)
            printf("%s", NC);
        printf(" ");
    }
    printf("\r\n");
}