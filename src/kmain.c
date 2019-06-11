#include <stdint.h>

#define PROMPT	"> "

void kprintf(const char *fmt, ...);
void ata_init();
int uart_getchar();

void kmain()
{
	unsigned char ch;

	kprintf("Roadrunner\n");

	kprintf("sizeof(uchar_t) = %d\n", sizeof(uchar_t));
	kprintf("sizeof(ushort_t) = %d\n", sizeof(ushort_t));
	kprintf("sizeof(uint_t) = %d\n", sizeof(uint_t));
	kprintf("sizeof(ulong_t) = %d\n", sizeof(ulong_t));

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
