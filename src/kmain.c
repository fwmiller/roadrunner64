#include <stdint.h>
#include <stdio.h>

#define PROMPT	"> "

void kprintf(const char *fmt, ...);
void ata_init();
int uart_getchar();

static
void word_widths()
{
	kprintf("uchar_t %d ushort_t %d uint_t %d ulong_t %d void* %d\n",
		sizeof(uchar_t), sizeof(ushort_t), sizeof(uint_t),
		sizeof(ulong_t), sizeof(void *));
}

void kmain()
{
	unsigned char ch;

	kprintf("Roadrunner 64-bit\n");

	word_widths();
	ata_init();

	kprintf("Type ctrl-a x to exit\n");

	kprintf(PROMPT);
	for (;;) {
		ch = uart_getchar();
		kprintf("%c", ch);
		if (ch == '\r') {
			kprintf("\n");
			kprintf(PROMPT);
		}
	}
}
