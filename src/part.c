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

#include <io.h>
#include <stdio.h>
#include <string.h>
#include <part.h>

void kprintf(const char *fmt, ...);;

void read_parttab(uchar_t * mbr, part_t parttab)
{
	part_t p;
	uint_t partent;
	uchar_t *soff, *eoff;
	int i;

	memset(parttab, 0, PARTS * sizeof(struct part));

	for (i = 0, p = parttab, partent = PART_ENT_1;
	     i < PARTS; i++, p++, partent += PART_ENT_SIZE) {

		kprintf("read_parttab: mbr + partent = 0x%08x\n",
			mbr + partent);
		bufdump(mbr + partent, PART_ENT_SIZE);

		p->active = (uchar_t) loadbyte(mbr + partent + PART_OFF_BOOT);
		kprintf("read_parttab: active = 0x%02x\n", p->active);

		p->sys = (uchar_t) loadbyte(mbr + partent + PART_OFF_SYS);
		soff = mbr + partent + PART_OFF_START;
		eoff = mbr + partent + PART_OFF_END;

		p->st = (uint_t) loadbyte(soff + 2) |
		    (((uint_t) loadbyte(soff + 1) & 0xc0) << 2);
		kprintf("read_parttab: start track = %u\n", p->st);

		p->sh = (uint_t) loadbyte(soff);
		kprintf("read_parttab: start head = %u\n", p->sh);

		p->ss = (uint_t) loadbyte(soff + 1) & 0x3f;
		kprintf("read_parttab: start sector = %u\n", p->ss);

		p->et = (uint_t) loadbyte(eoff + 2) |
		    (((uint_t) loadbyte(eoff + 1) & 0xc0) << 2);
		kprintf("read_parttab: end sector = %u\n", p->et);

		p->eh = (uint_t) loadbyte(eoff);
		kprintf("read_parttab: end head = %u\n", p->eh);

		p->es = (uint_t) loadbyte(eoff + 1) & 0x3f;
		kprintf("read_parttab: end sector = %u\n", p->es);

		p->off = (uint_t) loaddword(mbr + partent + PART_OFF_OFF);
		p->size = (uint_t) loaddword(mbr + partent + PART_OFF_SIZE);

		kprintf("read_parttab: offset = %u\n", p->off);
		kprintf("read_parttab: size = %u\n", p->size);
	}
}

void write_parttab(part_t parttab, uchar_t * mbr)
{
	part_t p;
	uint_t partent;
	int i;

	for (i = 0, p = parttab, partent = PART_ENT_1;
	     i < PARTS; i++, p++, partent += PART_ENT_SIZE) {
		storebyte((uchar_t) p->active, mbr + partent + PART_OFF_BOOT);
		storebyte((uchar_t) p->sh, mbr + partent + PART_OFF_START);
		storebyte(((uchar_t) ((p->st & 0x300) >> 2)) |
			  ((uchar_t) (p->ss & 0x3f)),
			  mbr + partent + PART_OFF_START + 1);
		storebyte((uchar_t) (p->st & 0xff),
			  mbr + partent + PART_OFF_START + 2);
		storebyte((uchar_t) p->sys, mbr + partent + PART_OFF_SYS);
		storebyte((uchar_t) p->eh, mbr + partent + PART_OFF_END);
		storebyte(((uchar_t) ((p->et & 0x300) >> 2)) |
			  ((uchar_t) (p->es & 0x3f)),
			  mbr + partent + PART_OFF_END + 1);
		storebyte((uchar_t) (p->et & 0xff),
			  mbr + partent + PART_OFF_END + 2);
		storedword(p->off, mbr + partent + PART_OFF_OFF);
		storedword(p->size, mbr + partent + PART_OFF_SIZE);
	}
}

static void dump_part(int partno, part_t p)
{
	kprintf("%c", (p->active ? '*' : ' '));
	kprintf("%3d  %5u  %3u     %2u  %5u  %3u     %2u %8u %12u ",
		partno, p->st, p->sh, p->ss, p->et, p->eh, p->es, p->off,
		p->size);
	switch (p->sys) {
	case PART_SYS_NONE:
		kprintf("unused");
		break;
	case PART_SYS_FAT12:
		kprintf("fat12");
		break;
	case PART_SYS_FAT16:
		kprintf("fat16");
		break;
	case PART_SYS_EXT:
		kprintf("extended");
		break;
	case PART_SYS_LARGE:
		kprintf("fat16 large");
		break;
	case PART_SYS_HPFS:
		kprintf("hpfs");
		break;
	case PART_SYS_FAT32:
		kprintf("fat32");
		break;
	case PART_SYS_UFS:
		kprintf("ufs");
		break;
	case PART_SYS_LINUX_SWAP:
		kprintf("linux swap");
		break;
	case PART_SYS_EXT2FS:
		kprintf("ext2fs");
		break;
	case PART_SYS_RRFS:
		kprintf("rrfs");
		break;
	default:
		kprintf("0x%02x", (uchar_t) p->sys);
	}
	kprintf("\n");
}

#define PART_HDR1                                                       \
    "      ------start------- --------end-------"
#define PART_HDR2                                                       \
    "part  track  head sector track  head sector   offset         size type"

void dump_parttab(part_t parttab)
{
	part_t p;
	int i;

	kprintf("%s\n", PART_HDR1);
	kprintf("%s\n", PART_HDR2);
	for (i = 0, p = parttab; i < PARTS; i++, p++)
		dump_part(i, p);
}
