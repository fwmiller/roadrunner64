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
		p->active = (uchar_t) loadbyte(mbr + partent + PART_OFF_BOOT);
		p->sys = (uchar_t) loadbyte(mbr + partent + PART_OFF_SYS);
		soff = mbr + partent + PART_OFF_START;
		eoff = mbr + partent + PART_OFF_END;
		p->st = (uint_t) loadbyte(soff + 2) |
		    (((uint_t) loadbyte(soff + 1) & 0xc0) << 2);
		p->sh = (uint_t) loadbyte(soff);
		p->ss = (uint_t) loadbyte(soff + 1) & 0x3f;
		p->et = (uint_t) loadbyte(eoff + 2) |
		    (((uint_t) loadbyte(eoff + 1) & 0xc0) << 2);
		p->eh = (uint_t) loadbyte(eoff);
		p->es = (uint_t) loadbyte(eoff + 1) & 0x3f;
		p->off = (uint_t) loaddword(mbr + partent + PART_OFF_OFF);
		p->size = (uint_t) loaddword(mbr + partent + PART_OFF_SIZE);
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
	kprintf("%3d  %5u  %4u %6u %5u  %4u %6u  %6u %12u  ",
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
    "part  track  head sector track  head sector   offset        size  type"

void dump_parttab(part_t parttab)
{
	part_t p;
	int i;

	kprintf("%s\n", PART_HDR1);
	kprintf("%s\n", PART_HDR2);
	for (i = 0, p = parttab; i < PARTS; i++, p++)
		dump_part(i, p);
}
