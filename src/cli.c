#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/uart.h>

#define PROMPT	"> "

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
	char cmdline[80];

	kprintf(PROMPT);
	for (;;) {
		get_cmdline(cmdline, 80);
		if (strlen(cmdline) > 0)
			kprintf("%s\r\n", cmdline);
		kprintf(PROMPT);
	}
}
