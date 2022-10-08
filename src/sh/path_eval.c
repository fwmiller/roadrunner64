#if _DEBUG_SHELL
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <sys/sh.h>

#define PATH_ELEMENTS 32
#define PATH_ELEMENT_LEN 64

#define PF_EXCLUDE 0x01

struct path_element {
    int flags;
    char element[PATH_ELEMENT_LEN];
};

typedef struct path_element *path_element_t;
typedef struct path_element path_elements[PATH_ELEMENTS];

/*
 * The path is broken into the array of strings in the elem parameter.
 * The index of the last element in the array is returned through the
 * reference parameter elemidx
 */
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

/*
 * The element strings are reassembled into a normal form path string
 * excluding those that were previously flagged during the path evaluation
 */
static void
path_assemble(path_elements elem, int elemidx, char *path, int pathbufsize) {
    memset(path, 0, pathbufsize);
    for (int i = 0; i < elemidx; i++)
        if (!(elem[i].flags & PF_EXCLUDE)) {
            strcat(path, "/");
            strcat(path, elem[i].element);
        }
}

/*
 * Evaluate full path taking actions to remove multiple separators and
 * executing the . and .. path elements for directory tree traversal
 */
char *
path_eval(char *path, int pathbufsize) {
    path_elements elem;
    int elemidx = 0;

    if (path == NULL || path[0] != '/')
        return NULL;

    memset(elem, 0, PATH_ELEMENTS * sizeof(struct path_element));

    /* Break the input path into its elements strings */
    path_break(path, pathbufsize, elem, &elemidx);

    /* Evaluate . and .. commands */
    for (int i = 0; i <= elemidx; i++) {
        if (strcmp(elem[i].element, ".") == 0) {
            /* Exclude current path element */
            elem[i].flags |= PF_EXCLUDE;

        } else if (strcmp(elem[i].element, "..") == 0) {
            /* Exclude current and previous path elements */
            elem[i].flags |= PF_EXCLUDE;

            /*
             * Need to search backwards for the previous path element that
             * is not already excluded
             */
            for (int j = i; j >= 0; j--)
                if (!(elem[j].flags & PF_EXCLUDE)) {
                    elem[j].flags |= PF_EXCLUDE;
                    break;
                }
        }
    }
    /* Reassemble the normalized path after evaluation */
    path_assemble(elem, elemidx + 1, path, pathbufsize);

    if (strlen(path) == 0)
        strcat(path, "/");
#if _DEBUG_SHELL
    printf("path_eval: [%s]\r\n", path);
#endif
    return path;
}
