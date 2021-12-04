#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/uart.h>

#define PROMPT		"> "
#define CMD_LINE_LEN	80

static int
get_cmdline(char *cmdline, int len)
{
	int pos;
	char ch;

	memset(cmdline, 0, len);
	for (pos = 0;;) {
		ch = uart_getchar();

		if (!isprint(ch) && ch != '\r' && ch != '\n' && ch != '\b')
			continue;

		if (ch == '\n' || ch == '\r') {
			kprintf("\r\n");
			break;
		}
		if (ch == '\b' && pos > 0) {
			cmdline[--pos] = '\0';
			kprintf("\b \b");

		} else if (ch != '\b' && ch != '\r') {
			cmdline[pos++] = ch;
			kprintf("%c", ch);
			if (pos == len - 1)
				break;
		}
	}
	return pos;
}

void
cli()
{
	char cmdline[CMD_LINE_LEN];

	for (;;) {
		kprintf(PROMPT);

		get_cmdline(cmdline, CMD_LINE_LEN);
		if (strlen(cmdline) == 0)
			continue;
	}
}
