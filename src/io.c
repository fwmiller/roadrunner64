#include <io.h>

void
insb(ushort_t port, uchar_t * dst, int bytes)
{
	for (int i = 0; i < bytes; i++)
		dst[i] = inb(port);
}

void
insw(ushort_t port, ushort_t * dst, int words)
{
	for (int i = 0; i < words; i++)
		((ushort_t *) dst)[i] = inw(port);
}

void
insl(ushort_t port, ulong_t * dst, int dwords)
{
	for (int i = 0; i < dwords; i++)
		((uint_t *) dst)[i] = inl(port);
}

void
outsb(ushort_t port, uchar_t * src, int bytes)
{
	for (int i = 0; i < bytes; i++)
		outb(port, src[i]);
}

void
outsw(ushort_t port, ushort_t * src, int words)
{
	for (int i = 0; i < words; i++)
		outw(port, ((ushort_t *) src)[i]);
}

void
outsl(ushort_t port, ulong_t * src, int dwords)
{
	for (int i = 0; i < dwords; i++)
		outl(port, ((uint_t *) src)[i]);
}

int
bcd2int(uchar_t v)
{
	return (int)((v >> 4) * 10 + (v % 0x10));
}

uchar_t
loadbyte(uchar_t * ptr)
{
	return (uchar_t) * ptr;
}

ushort_t
loadword(uchar_t * ptr)
{
	return (short)*ptr | (ushort_t) (*(ptr + 1) << 8);
}

uint_t
loaddword(uchar_t * ptr)
{
	return (uint_t) * ptr |
	    (uint_t) (*(ptr + 1) << 8) |
	    (uint_t) (*(ptr + 2) << 16) | (uint_t) (*(ptr + 3) << 24);
}

void
storebyte(uchar_t val, uchar_t * ptr)
{
	*ptr = (uchar_t) val & 0xff;
}

void
storeword(uint_t val, uchar_t * ptr)
{
	*ptr = (uchar_t) val & 0xff;
	*(ptr + 1) = (uchar_t) (val >> 8) & 0xff;
}

void
storedword(uint_t val, uchar_t * ptr)
{
	*ptr = (uchar_t) val & 0xff;
	*(ptr + 1) = (uchar_t) (val >> 8) & 0xff;
	*(ptr + 2) = (uchar_t) (val >> 16) & 0xff;
	*(ptr + 3) = (uchar_t) (val >> 24) & 0xff;
}
