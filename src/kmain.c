#include <stdint.h>

void kprintf(const char *fmt, ...);
void ata_init();

void cli();

static void
word_widths()
{
	int halt = 0;

	if (sizeof(uint8_t) != 1) {
		kprintf("sizeof(uint8_t) = %u bytes\r\n", sizeof(uint8_t));
		halt = 1;
	}
	if (sizeof(uint16_t) != 2) {
		kprintf("sizeof(uint16_t) = %u bytes\r\n", sizeof(uint16_t));
		halt = 1;
	}
	if (sizeof(uint32_t) != 4) {
		kprintf("sizeof(uint32_t) = %u bytes\r\n", sizeof(uint32_t));
		halt = 1;
	}
	if (sizeof(uint64_t) != 8) {
		kprintf("sizeof(uint64_t) = %u bytes\r\n", sizeof(uint64_t));
		halt = 1;
	}
	if (sizeof(void *) != 8) {
		kprintf("sizeof(void *) = %u bytes\r\n", sizeof(void *));
		halt = 1;
	}
	if (halt)
		for (;;);
}

void kmain()
{
	kprintf("\r\nRoadrunner 64-bit\r\n");

	word_widths();
	ata_init();

	kprintf("Type ctrl-a x to exit\r\n");
	cli();
}
