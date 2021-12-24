#ifndef __SYS_H
#define __SYS_H

#include <stdint.h>
#include <sys/mc146818.h>

#define ALIGN(V, SIZE) ((((V) + (SIZE) - 1) / (SIZE)) * (SIZE))

#define inb(port)							\
({									\
    register int _inb_result;						\
    asm volatile ("xorl %%eax,%%eax; inb %%dx,%%al" :			\
		  "=a" (_inb_result) : "d" (port));			\
    _inb_result;							\
})

#define inw(port)							\
({									\
    register int _inb_result;						\
    asm volatile ("xorl %%eax,%%eax; inw %%dx,%%ax" :			\
		  "=a" (_inb_result) : "d" (port));			\
    _inb_result;							\
})

#define inl(port)							\
({									\
    register unsigned long _inb_result;					\
    asm volatile ("xorl %%eax,%%eax; inl %%dx,%%eax" :			\
		  "=a" (_inb_result) : "d" (port));			\
    _inb_result;							\
})

#define outb(port, data)						\
    asm volatile ("outb %%al,%%dx" : : "a" (data), "d" (port))

#define outw(port, data)						\
    asm volatile ("outw %%ax,%%dx" : : "a" (data), "d" (port))

#define outl(port, data)						\
    asm volatile ("outl %%eax,%%dx" : : "a" (data), "d" (port))

void insb(uint16_t port, uint8_t * dst, int bytes);
void insw(uint16_t port, uint16_t * dst, int words);
void insl(uint16_t port, uint32_t * dst, int dwords);
void outsb(uint16_t port, uint8_t * src, int bytes);
void outsw(uint16_t port, uint16_t * src, int words);
void outsl(uint16_t port, uint32_t * src, int dwords);

int bcd2int(uint8_t v);

static inline uint8_t
loadcmosbyte(uint8_t field)
{
	outb(MC146818_ADDR, field);
	return inb(MC146818_DATA);
}

uint8_t loadbyte(uint8_t * ptr);
uint16_t loadword(uint8_t * ptr);
uint32_t loaddword(uint8_t * ptr);

void storebyte(uint8_t val, uint8_t * ptr);
void storeword(uint32_t val, uint8_t * ptr);
void storedword(uint32_t val, uint8_t * ptr);

#endif
