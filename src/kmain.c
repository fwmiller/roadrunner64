#include <stdint.h>

void kprintf(const char *fmt, ...);
void ata_init();

void cli();

static void
word_widths()
{
	kprintf("uint8_t = %u", sizeof(uint8_t));
	kprintf(" uint16_t = %u", sizeof(uint16_t));
	kprintf(" uint32_t = %u", sizeof(uint32_t));
	kprintf(" uint64_t = %u", sizeof(uint64_t));
	kprintf(" void * = %u (bytes)\r\n", sizeof(void *));
}

void kmain()
{
	kprintf("\r\nRoadrunner 64-bit\r\n");

	word_widths();
	ata_init();

	kprintf("Type ctrl-a x to exit\r\n");
	cli();
}
