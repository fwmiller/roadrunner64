#include <sys/io.h>

#define COM_TX_FIFO	((short) 0x3f8)
#define COM_RX_FIFO	((short) 0x3f8)
#define COM_RX_STATUS	((short) 0x3fd)

/**
 *   This reads a character from the UART.  The function returns a byte
 *   cast as an integer from the UART
 *   return value.
 *
 *   @retval		A byte cast to an integer from the UART
 **/
int
uart_getchar()
{
	while (!(inb(COM_RX_STATUS) & 0x01)) ;
	return (int)inb(COM_RX_FIFO);
}

/**
 *   This function writes a character to the UART.  The function has no
 *   return value.
 *
 *   @param ch		The character value of this int iw written
 *   			to the UART.
 **/
void
uart_putchar(int ch)
{
	outb(COM_TX_FIFO, ch);
}
