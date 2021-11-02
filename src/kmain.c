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
	kprintf("uint8_t = %u", sizeof(uint8_t));
	kprintf(" uint16_t = %u", sizeof(uint16_t));
	kprintf(" uint32_t = %u", sizeof(uint32_t));
	kprintf(" uint64_t = %u", sizeof(uint64_t));
	kprintf(" void * = %u (bytes)\r\n", sizeof(void *));
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

	word_widths();
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
