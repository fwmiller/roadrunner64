#include <stdlib.h>
#include <string.h>
#include <sys/path.h>

char *
path_cat(char *path1, char *path2, char *path3) {
    if (path3 == NULL || (path1 == NULL && path2 == NULL))
        return NULL;

    /* Assume path3 has been zeroed */
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
    strcat(path3, path2);
    return path3;
}

char *
path_eval(char *path) {
    return NULL;
}
