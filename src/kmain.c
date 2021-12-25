#include <stdio.h>
#include <sys/ata.h>
#include <sys/isofs.h>

void cli();

static void
word_widths()
{
	int halt = 0;

	if (sizeof(uint8_t) != 1) {
		printf("sizeof(uint8_t) = %u bytes\r\n", sizeof(uint8_t));
		halt = 1;
	}
	if (sizeof(uint16_t) != 2) {
		printf("sizeof(uint16_t) = %u bytes\r\n", sizeof(uint16_t));
		halt = 1;
	}
	if (sizeof(uint32_t) != 4) {
		printf("sizeof(uint32_t) = %u bytes\r\n", sizeof(uint32_t));
		halt = 1;
	}
	if (sizeof(uint64_t) != 8) {
		printf("sizeof(uint64_t) = %u bytes\r\n", sizeof(uint64_t));
		halt = 1;
	}
	if (sizeof(void *) != 8) {
		printf("sizeof(void *) = %u bytes\r\n", sizeof(void *));
		halt = 1;
	}
	if (halt)
		for (;;) ;
}

void
kmain()
{
	printf("\r\nRoadrunner 64-bit\r\n");

	word_widths();
	ata_init();
	isofs_init();

	printf("Type ctrl-a x to exit\r\n");
	cli();
}
