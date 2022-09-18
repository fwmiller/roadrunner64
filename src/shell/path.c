#if _DEBUG_SHELL
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <sys/shell.h>

#define PATH_ELEMENTS 32
#define PATH_ELEMENT_LEN 64

#define PF_EXCLUDE 0x01

struct path_element {
    int flags;
    char element[PATH_ELEMENT_LEN];
};

typedef struct path_element *path_element_t;
typedef struct path_element path_elements[PATH_ELEMENTS];

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

/* Break path into list of elements */
static void
path_break(char *path, int pathbufsize, path_elements elem, int *elemidx) {
    int sep = 1;
    int i, j;

    for (i = 1, j = 0; i < pathbufsize; i++) {
        if (path[i] == '/') {
            if (!sep && *elemidx < PATH_ELEMENTS - 1) {
                (*elemidx)++;
                j = 0;
            }
            sep = 1;
        } else {
            sep = 0;
            elem[*elemidx].element[j++] = path[i];
        }
    }
}

static void
path_assemble(path_elements elem, int elemidx, char *path, int pathbufsize) {
    memset(path, 0, pathbufsize);
    for (int i = 0; i < elemidx; i++) {
        if (elem[i].flags != PF_EXCLUDE) {
            strcat(path, "/");
            strcat(path, elem[i].element);
        }
    }
}

/* Evaluate the . and .. commands in a path */
char *
path_eval(char *path, int pathbufsize) {
    path_elements elem;
    int elemidx = 0;

#if _DEBUG_SHELL
    printf("path [%s] pathbufsize %d\r\n", path, pathbufsize);
#endif
    if (path[0] != '/')
        return NULL;

    memset(elem, 0, PATH_ELEMENTS * sizeof(struct path_element));
    path_break(path, pathbufsize, elem, &elemidx);

    /* Evaluate . and .. commands */
    for (int i = 0; i <= elemidx; i++) {
        if (strcmp(elem[i].element, ".") == 0) {
            /* Exclude current path element */
            elem[i].flags = PF_EXCLUDE;

        } else if (strcmp(elem[i].element, "..") == 0) {
            /* Exclude current and previous path element */
            elem[i].flags = PF_EXCLUDE;
            for (int j = i; j >= 0; j--) {
                if (elem[j].flags != PF_EXCLUDE) {
                    elem[j].flags = PF_EXCLUDE;
                    break;
                }
            }
        }
    }
#if _DEBUG_SHELL
    for (int i = 0; i <= elemidx; i++) {
        if (elem[i].flags == PF_EXCLUDE)
            printf("X ");
        else
            printf("  ");
        printf("[%s]\r\n", elem[i].element);
    }
#endif
    path_assemble(elem, elemidx + 1, path, pathbufsize);

#if _DEBUG_SHELL
    printf("final path [%s]\r\n", path);
#endif
    return path;
}
