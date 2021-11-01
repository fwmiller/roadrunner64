#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PROMPT	"> "

void kprintf(const char *fmt, ...);
void ata_init();
int uart_getchar();

static void
word_widths()
{
	kprintf("uchar_t %d ushort_t %d uint_t %d ulong_t %d void* %d\n",
		sizeof(uchar_t), sizeof(ushort_t), sizeof(uint_t),
		sizeof(ulong_t), sizeof(void *));
}

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
			kprintf("\n");
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


void kmain()
{
	char cmdline[80];

	kprintf("\nRoadrunner 64-bit\n");
#if 0
	word_widths();
#endif
	ata_init();

	kprintf("Type ctrl-a x to exit\n");

	kprintf(PROMPT);
	for (;;) {
		get_cmdline(cmdline, 80);
		if (strlen(cmdline) > 0)
			kprintf("%s\r\n", cmdline);
		kprintf(PROMPT);
	}
}
