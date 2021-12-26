#include <stdio.h>
#include <sys/fs.h>
#include <sys/sys.h>

void cli();

void
kmain()
{
	printf("\r\nRoadrunner 64-bit\r\n");

	word_widths();
	fs_init();

	printf("Type ctrl-a x to exit\r\n");
	cli();
}
