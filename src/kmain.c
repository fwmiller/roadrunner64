#include <stdio.h>
#include <sys/fs.h>
#include <sys/io.h>
#include <sys/sys.h>

void cli();

static unsigned
get_cmos_memsize()
{
	unsigned short total;
	unsigned char lowmem, highmem;

	outb(0x70, 0x30);
	lowmem = inb(0x71);
	outb(0x70, 0x31);
	highmem = inb(0x71);

	total = lowmem | highmem << 8;

	printf("Available memory %u MB\r\n", total / 1024);

	return total;
}

void
kmain()
{
	printf("\r\nRoadrunner 64-bit\r\n");

	word_widths();
	get_cmos_memsize();
	fs_init();

	printf("Type ctrl-a x to exit\r\n");
	cli();
}
