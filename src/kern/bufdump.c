#include <ctype.h>
#include <stdio.h>
#include <sys/sys.h>

#define LEN 16

void
bufdump(char *buf, int size) {
    uint8_t *line;
    int i, j, lines;

    lines = (size + LEN - 1) / LEN;
    for (i = 0; i < lines; i++) {
        line = (uint8_t *) buf + i * LEN;
#if 0
        printf("%08x  ", (unsigned long long) buf + i * LEN);
#endif
        for (j = 0; j < LEN; j++) {
            printf("%02x ", line[j]);
            if (j == (LEN / 2) - 1)
                printf(" ");
        }
        printf(" ");
        for (j = 0; j < LEN; j++) {
            if (isprint(line[j]) && line[i] >= 0x20)
                printf("%c", (char) line[j]);
            else
                printf(".");
            if (j == (LEN / 2) - 1)
                printf(" ");
        }
        printf("\r\n");
    }
}
