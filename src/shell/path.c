#if _DEBUG_SHELL
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <sys/shell.h>

#define PATH_ELEMENTS 8
#define PATH_ELEMENT_LEN 32

typedef char path_elements[PATH_ELEMENTS][PATH_ELEMENT_LEN];

static void
path_break(char *path, int pathbufsize, path_elements elem, int *elemidx) {
    int sep = 1;
    int i, j;

    /* Break path into list of elements */
    for (i = 1, j = 0; i < pathbufsize; i++) {
        if (path[i] == '/') {
            if (!sep && *elemidx < PATH_ELEMENTS - 1) {
                (*elemidx)++;
                j = 0;
            }
            sep = 1;
        } else {
            sep = 0;
            elem[*elemidx][j++] = path[i];
        }
    }
}

char *
path_eval(char *path, int pathbufsize) {
    path_elements elem;
    int elemidx = 0;

#if _DEBUG_SHELL
    printf("path [%s] pathbufsize %d\r\n", path, pathbufsize);
#endif
    memset(elem, 0, sizeof(path_elements));

    if (path[0] != '/')
        return NULL;

    path_break(path, pathbufsize, elem, &elemidx);

#if _DEBUG_SHELL
    for (int i = 0; i <= elemidx; i++)
        printf("[%s]\r\n", elem[i]);
#endif
    /* Evaluate . and .. commands */

    return path;
}

char *
path_prepend(char *pre, char *path, int pathbufsize) {
    char tmp[CMD_LINE_LEN];
    memset(tmp, 0, CMD_LINE_LEN);
    strcpy(tmp, pre);
    strcat(tmp, "/");
    strcat(tmp, path);
    memset(path, 0, pathbufsize);
    strcpy(path, tmp);
    return path;
}
