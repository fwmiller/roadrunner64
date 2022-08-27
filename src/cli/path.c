#if 1
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <sys/cli.h>

static char *
path_eval_dirs(char *path) {
    int i, j;

    char tmp[CMD_LINE_LEN];
    memset(tmp, 0, CMD_LINE_LEN);

    int len = strlen(path);
    for (i = 0, j = 0; i < len; i++) {
        if (path[i] == '/' && i + 1 < len && path[i + 1] == '.') {
            /* "/." in the path */
            if (i + 2 >= len) {
                /* "/." at end of path */

            } else if (path[i + 2] == '/') {
                /* "/./" in the path */

            } else if (path[i + 2] == '.') {
                /* "/.." in the path */
                if (i + 3 >= len) {
                    /* "/.." at end of path */

                } else if (path[i + 3] == '/') {
                    /* "/../" in the path */

                } else {
                    /* "/.." with something else after it in the path */
                    /* This is an error case */
                }
            } else {
                /* "/." with something else after it in the path */
                /* This is an error case */
            }
        }
        tmp[j++] = path[i];
    }
    memset(path, 0, CMD_LINE_LEN);
    strcpy(path, tmp);
#if 1
    printf("path_eval_dirs: %s\r\n", path);
#endif
    return path;
}

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
            /* Skip over multiple '/' separators */
            if (sep)
                continue;
            else {
                tmp[j++] = path[i];
                sep = 1;
            }

        } else if (path[i] == '.') {
            /* Collapse '.' and '..' path elements */
            if (sep && i > 0 && path[i - 1] != '/')
                sep = 0;

        } else {
            if (sep)
                sep = 0;
            tmp[j++] = path[i];
        }
    }
    memset(path, 0, CMD_LINE_LEN);
    strcpy(path, tmp);
#if 1
    printf("path_eval: %s\r\n", path);
#endif
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
