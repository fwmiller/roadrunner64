#include <stdlib.h>
#include <string.h>

char *
path_cat(char *dest, char *src) {
    if (dest != NULL && src != NULL) {
        strcat(dest, "/");
        strcat(dest, src);
    }
    return dest;
}

char *
path_eval(char *path) {
    return NULL;
}
