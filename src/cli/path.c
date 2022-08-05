#include <stdlib.h>
#include <string.h>
#include <sys/cli.h>

char *
path_eval(char *path) {
    int sep = 0;
    int i, j;

    if (path == NULL)
        return NULL;

    char tmp[CMD_LINE_LEN];
    memset(tmp, 0, CMD_LINE_LEN);

    int len = strlen(path);
    for (i = 0, j = 0; i < len; i++) {
        if (path[i] == '/') {
            if (sep)
                continue;
            else {
                tmp[j++] = path[i];
                sep = 1;
            }
        } else {
            if (sep)
                sep = 0;
            tmp[j++] = path[i];
        }
    }
    memset(path, 0, CMD_LINE_LEN);
    strcpy(path, tmp);
    return path;
}

char *
path_prepend(char *pre, char *path) {
    char tmp[CMD_LINE_LEN];
    memset(tmp, 0, CMD_LINE_LEN);
    strcpy(tmp, pre);
    strcat(tmp, "/");
    strcat(tmp, path);
    memset(path, 0, CMD_LINE_LEN);
    strcpy(path, tmp);
    return path;
}
