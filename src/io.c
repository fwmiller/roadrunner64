#include <sys/io.h>

void
insb(uint16_t port, uint8_t * dst, int bytes)
{
	for (int i = 0; i < bytes; i++)
		dst[i] = inb(port);
}

void
insw(uint16_t port, uint16_t * dst, int words)
{
	for (int i = 0; i < words; i++)
		((uint16_t *) dst)[i] = inw(port);
}

void
insl(uint16_t port, uint32_t * dst, int dwords)
{
	for (int i = 0; i < dwords; i++)
		((uint32_t *) dst)[i] = inl(port);
}

void
outsb(uint16_t port, uint8_t * src, int bytes)
{
	for (int i = 0; i < bytes; i++)
		outb(port, src[i]);
}

void
outsw(uint16_t port, uint16_t * src, int words)
{
	for (int i = 0; i < words; i++)
		outw(port, ((uint16_t *) src)[i]);
}

void
outsl(uint16_t port, uint32_t * src, int dwords)
{
	for (int i = 0; i < dwords; i++)
		outl(port, ((uint32_t *) src)[i]);
}

int
bcd2int(uint8_t v)
{
	return (int)((v >> 4) * 10 + (v % 0x10));
}

uint8_t
loadbyte(uint8_t * ptr)
{
	return (uint8_t) * ptr;
}

uint16_t
loadword(uint8_t * ptr)
{
	return (short)*ptr | (uint16_t) (*(ptr + 1) << 8);
}

uint32_t
loaddword(uint8_t * ptr)
{
	return (uint32_t) * ptr |
	    (uint32_t) (*(ptr + 1) << 8) |
	    (uint32_t) (*(ptr + 2) << 16) | (uint32_t) (*(ptr + 3) << 24);
}

void
storebyte(uint8_t val, uint8_t * ptr)
{
	*ptr = (uint8_t) val & 0xff;
}

void
storeword(uint32_t val, uint8_t * ptr)
{
	*ptr = (uint8_t) val & 0xff;
	*(ptr + 1) = (uint8_t) (val >> 8) & 0xff;
}

void
storedword(uint32_t val, uint8_t * ptr)
{
	*ptr = (uint8_t) val & 0xff;
	*(ptr + 1) = (uint8_t) (val >> 8) & 0xff;
	*(ptr + 2) = (uint8_t) (val >> 16) & 0xff;
	*(ptr + 3) = (uint8_t) (val >> 24) & 0xff;
}
