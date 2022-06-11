#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/uart.h>
#include <unistd.h>

#define PROMPT "> "
#define CMD_LINE_LEN 80

static int
get_cmdline(char *cmdline, int len) {
    int pos;
    char ch;

    memset(cmdline, 0, len);
    for (pos = 0;;) {
        ch = uart_getchar();

        if (!isprint(ch) && ch != '\r' && ch != '\n' && ch != '\b')
            continue;

        if (ch == '\n' || ch == '\r') {
            printf("\r\n");
            break;
        }
        if (ch == '\b' && pos > 0) {
            cmdline[--pos] = '\0';
            printf("\b \b");

        } else if (ch != '\b' && ch != '\r') {
            cmdline[pos++] = ch;
            printf("%c", ch);
            if (pos == len - 1)
                break;
        }
    }
    return pos;
}

void
cli() {
    char cmdline[CMD_LINE_LEN];

    for (;;) {
        printf(PROMPT);

        get_cmdline(cmdline, CMD_LINE_LEN);
        if (strlen(cmdline) == 0)
            continue;

        if (cmdline[0] == '/') {
            /*
             * A full path has been specified as the first
             * argument.   Try to load and run the named
             * executable
             */
            int fd = open(cmdline, 0);

            for (char ch = 0;;) {
                int len = read(fd, &ch, 1);
                if (len < 0) {
                    break;
                }
                if (len == 0)
                    break;

                printf("%c", ch);
            }
        }
    }
}
