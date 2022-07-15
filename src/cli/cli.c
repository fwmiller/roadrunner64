#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/cli.h>
#include <sys/sys.h>
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
    char arg[CMD_LINE_LEN];
    int pos;

    for (;;) {
        printf(PROMPT);

        get_cmdline(cmdline, CMD_LINE_LEN);
        if (strlen(cmdline) == 0)
            continue;
#if 0
        if (cmdline[0] == '/') {
            /*
             * A full path has been specified as the first
             * argument.   Try to load and run the named
             * executable
             */
            int fd = open(cmdline, 0);

            for (char ch = 0;;) {
                int len = read(fd, &ch, 1);
                if (len <= 0)
                    break;

                printf("%c", ch);
            }
        }
#endif
        pos = 0;
        memset(arg, 0, CMD_LINE_LEN);
        nextarg(cmdline, &pos, " ", arg);

        if (strncmp(arg, "cat", 3) == 0) {
            memset(arg, 0, CMD_LINE_LEN);
            nextarg(cmdline, &pos, " ", arg);

            int fd = open(arg, 0);
            if (fd < 0) {
                printf("open %s failed (%s)\r\n", arg, strerror(fd));
                continue;
            }

            for (char ch = 0;;) {
                int len = read(fd, &ch, 1);
                if (len <= 0)
                    break;
                printf("%c", ch);
            }

        } else if (strncmp(arg, "hexdump", 7) == 0) {
            memset(arg, 0, CMD_LINE_LEN);
            nextarg(cmdline, &pos, " ", arg);

            int fd = open(arg, 0);
            if (fd < 0) {
                printf("open %s failed (%s)\r\n", arg, strerror(fd));
                continue;
            }

            char buf[16];
            memset(buf, 0, 16);
            for (int i = 0;; i += 16) {
                int len = read(fd, buf, 16);
                if (len <= 0)
                    break;
                printf("%08x  ", i);
                bufdump(buf, 16);
            }
        } else if (strncmp(arg, "help", 4) == 0) {
            printf("\r\n");
            printf("cat <filename>\r\n");
            printf("  Print file contents as text\r\n");
            printf("hexdump <filename>\r\n");
            printf("  Print file contents as hexadecimal values\r\n");
            printf("\r\n");
        }
    }
}
