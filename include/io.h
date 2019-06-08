/* 
 *  Roadrunner/pk
 *    Copyright (C) 1989-2001  Cornfed Systems, Inc.
 *
 *  The Roadrunner/pk operating system is free software; you can
 *  redistribute and/or modify it under the terms of the GNU General
 *  Public License, version 2, as published by the Free Software
 *  Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA 02111-1307 USA
 *
 *  More information about the Roadrunner/pk operating system of
 *  which this file is a part is available on the World-Wide Web
 *  at: http://www.cornfed.com.
 *
 */

#ifndef __SYS_H
#define __SYS_H

#include <mc146818.h>
#include <stdint.h>

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

static inline void insb(ushort_t port, uchar_t * dst, int bytes)
{
	int i;

	for (i = 0; i < bytes; i++)
		dst[i] = inb(port);
}

static inline void insw(ushort_t port, ushort_t * dst, int words)
{
	int i;

	for (i = 0; i < words; i++)
		((ushort_t *) dst)[i] = inw(port);
}

static inline void insl(ushort_t port, ulong_t * dst, int dwords)
{
	int i;

	for (i = 0; i < dwords; i++)
		((uint_t *) dst)[i] = inl(port);
}

static inline void outsb(ushort_t port, uchar_t * src, int bytes)
{
	int i;

	for (i = 0; i < bytes; i++)
		outb(port, src[i]);
}

static inline void outsw(ushort_t port, ushort_t * src, int words)
{
	int i;

	for (i = 0; i < words; i++)
		outw(port, ((ushort_t *) src)[i]);
}

static inline void outsl(ushort_t port, ulong_t * src, int dwords)
{
	int i;

	for (i = 0; i < dwords; i++)
		outl(port, ((uint_t *) src)[i]);
}

int bcd2int(uchar_t v);

static inline uchar_t loadcmosbyte(uchar_t field)
{
	outb(MC146818_ADDR, field);
	return inb(MC146818_DATA);
}

uchar_t loadbyte(uchar_t * ptr);
uint_t loadword(uchar_t * ptr);
uint_t loaddword(uchar_t * ptr);

void storebyte(uchar_t val, uchar_t * ptr);
void storeword(uint_t val, uchar_t * ptr);
void storedword(uint_t val, uchar_t * ptr);

void halt();
void reboot();
int load(char *path, char **prog, ulong_t * size, char **start);

#endif
