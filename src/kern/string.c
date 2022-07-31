#include <stdlib.h>
#include <string.h>

size_t
strlen(const char *s) {
    int i;

    if (s == NULL)
        return 0;

    for (i = 0; s[i] != '\0'; i++)
        ;

    return (size_t) i;
}

int
strcmp(const char *s1, const char *s2) {
    const unsigned char *p1 = (const unsigned char *) s1;
    const unsigned char *p2 = (const unsigned char *) s2;

    while (*p1 && *p1 == *p2)
        ++p1, ++p2;

    return (*p1 > *p2) - (*p2 > *p1);
}

int
strncmp(const char *s1, const char *s2, size_t n) {
    int i = 0;

    if (s1 == NULL || s2 == NULL)
        return (-1);

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

    if (dst == NULL || src == NULL)
        return NULL;

    for (i = 0; src[i] != '\0'; i++)
        dst[i] = src[i];

    dst[i] = '\0';
    return dst;
}

char *
strcat(char *dest, const char *src) {
    if (dest == NULL || src == NULL)
        return NULL;
    strcpy(dest + strlen(dest), src);
    return dest;
}

void *
memset(void *b, int c, size_t n) {
    int i;

    if (b == NULL)
        return NULL;

    for (i = 0; i < (int) n; i++)
        ((char *) b)[i] = c;

    return b;
}

void *
memcpy(void *dest, void *src, size_t n) {
    int i;

    if (dest == NULL || src == NULL)
        return NULL;

    for (i = 0; i < (int) n; i++)
        ((char *) dest)[i] = ((char *) src)[i];

    return dest;
}
