#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/cli.h>
#include <sys/uart.h>

void cmd_cat(char *cmdline, int *pos);
void cmd_help();
void cmd_hexdump(char *cmdline, int *pos);
void cmd_ls(char *cmdline, int *pos);

static int
get_cmdline(char *cmdline, int len) {
    int pos;
    char ch;

    memset(cmdline, 0, len);
    for (pos = 0;;) {
        ch = uart_getchar();

        if (!isprint(ch) && ch != '\r' && ch != '\n' && ch != '\b' &&
            ch != 0x7f)
            continue;

        if (ch == '\n' || ch == '\r') {
            printf("\r\n");
            break;
        }
        if ((ch == '\b' || ch == 0x7f) && pos > 0) {
            cmdline[--pos] = '\0';
            printf("\b \b");

        } else if (ch != '\b' && ch != '\r' && ch != 0x7f) {
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

        if (strcmp(arg, "cat") == 0)
            cmd_cat(cmdline, &pos);

        else if (strcmp(arg, "hexdump") == 0)
            cmd_hexdump(cmdline, &pos);

        else if (strcmp(arg, "ls") == 0)
            cmd_ls(cmdline, &pos);

        else if (strcmp(arg, "help") == 0)
            cmd_help();
    }
}
