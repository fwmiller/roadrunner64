#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/uart.h>

int
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
