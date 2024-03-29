#include <ctype.h>
#include <sys/io.h>
#include <sys/uart.h>

#define COM_TX_FIFO ((uint16_t) 0x3f8)
#define COM_RX_FIFO ((uint16_t) 0x3f8)
#define COM_RX_STATUS ((uint16_t) 0x3fd)

int
uart_getchar() {
    int ch;

    while (!(inb(COM_RX_STATUS) & 0x01))
        ;
    ch = (int) inb(COM_RX_FIFO);
#if 0
    if (!isprint(ch))
	printf("[%02x]", ch);
#endif
    return ch;
}

void
uart_putchar(int ch) {
    outb(COM_TX_FIFO, ch);
}
