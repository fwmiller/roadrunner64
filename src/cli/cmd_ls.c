#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/cli.h>

static char *
path_cat(char *path1, char *path2, char *path3)
{
    if (path3 == NULL || (path1 == NULL && path2 == NULL))
	return NULL;

    if (path1 == NULL) {
	strcpy(path3, path2);
	return path3;
    }
    if (path2 == NULL) {
	strcpy(path3, path1);
	return path3;
    }

    int len1 = strlen(path1);
    int len2 = strlen(path2);

    if (len1 == 0) {
	strcpy(path3, path2);
	return path3;
    }
    if (len2 == 0) {
	strcpy(path3, path1);
	return path3;
    }
    strcpy(path3, path1);
    if (path3[strlen(path3) - 1] != '/' && path2[0] != '/')
	strcat(path3, "/");
    strcpy(path3, path2);
    return path3;
}

static char *
path_eval(char *path)
{
	return NULL;
}

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
        strcpy(tmp, pwd);
        strcpy(tmp + strlen(tmp), "/");
        strcpy(tmp + strlen(tmp), arg);
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
