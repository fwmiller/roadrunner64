#include <string.h>

size_t
strlen(const char *s) {
    int i = 0;

    while (s[i] != '\0')
        i++;
    return (size_t) i;
}

int
strncmp(const char *s1, const char *s2, size_t n) {
    int i = 0;

    while (i < n) {
        if (s1[i] == '\0' && s2[i] == '\0')
            return 0;
        else if (s1[i] == '\0' && s2[i] != '\0')
            return (-1);
        else if (s1[i] != '\0' && s2[i] == '\0')
            return 1;

        if (s1[i] == s2[i])
            i++;
        else if (s1[i] < s2[i])
            return (-1);
        else
            return 1;
    }
    return 0;
}

char *
strcpy(char *dst, const char *src) {
    int i;

    for (i = 0; src[i] != '\0'; i++)
        dst[i] = src[i];
    dst[i] = '\0';
    return dst;
}

void *
memset(void *b, int c, size_t len) {
    int i;

    for (i = 0; i < (int) len; i++)
        ((char *) b)[i] = c;
    return b;
}
