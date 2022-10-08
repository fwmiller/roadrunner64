#include <string.h>
#include <sys/path.h>
#include <sys/sh.h>

char *
path_prepend(char *pre, char *path, int pathbufsize) {
    char tmp[CMD_LINE_LEN];
    memset(tmp, 0, CMD_LINE_LEN);

    /* Use tmp and start with the prepend */
    strcpy(tmp, pre);

    /* Add separator unless the prepend was the root */
    if (strcmp(pre, "/") != 0)
        strcat(tmp, "/");

    /* Conatenate the path */
    strcat(tmp, path);

    /* Overwite path, with the result */
    memset(path, 0, pathbufsize);
    strcpy(path, tmp);

    return path;
}
