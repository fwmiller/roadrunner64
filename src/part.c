#include <stdio.h>
#include <string.h>
#include <sys/io.h>
#include <sys/part.h>

void
load_parttab(uint8_t * mbr, part_t parttab)
{
	part_t p;
	uint32_t partent;
	uint8_t *soff, *eoff;
	int i;

	memset(parttab, 0, PARTS * sizeof(struct part));

	for (i = 0, p = parttab, partent = PART_ENT_1;
	     i < PARTS; i++, p++, partent += PART_ENT_SIZE) {
		p->active = (uint8_t) loadbyte(mbr + partent + PART_OFF_BOOT);
		p->sys = (uint8_t) loadbyte(mbr + partent + PART_OFF_SYS);
		soff = mbr + partent + PART_OFF_START;
		eoff = mbr + partent + PART_OFF_END;
		p->st = (uint32_t) loadbyte(soff + 2) |
		    (((uint32_t) loadbyte(soff + 1) & 0xc0) << 2);
		p->sh = (uint32_t) loadbyte(soff);
		p->ss = (uint32_t) loadbyte(soff + 1) & 0x3f;
		p->et = (uint32_t) loadbyte(eoff + 2) |
		    (((uint32_t) loadbyte(eoff + 1) & 0xc0) << 2);
		p->eh = (uint32_t) loadbyte(eoff);
		p->es = (uint32_t) loadbyte(eoff + 1) & 0x3f;
		p->off = (uint32_t) loaddword(mbr + partent + PART_OFF_OFF);
		p->size = (uint32_t) loaddword(mbr + partent + PART_OFF_SIZE);
	}
}

void
write_parttab(part_t parttab, uint8_t * mbr)
{
	part_t p;
	uint32_t partent;
	int i;

	for (i = 0, p = parttab, partent = PART_ENT_1;
	     i < PARTS; i++, p++, partent += PART_ENT_SIZE) {
		storebyte((uint8_t) p->active, mbr + partent + PART_OFF_BOOT);
		storebyte((uint8_t) p->sh, mbr + partent + PART_OFF_START);
		storebyte(((uint8_t) ((p->st & 0x300) >> 2)) |
			  ((uint8_t) (p->ss & 0x3f)),
			  mbr + partent + PART_OFF_START + 1);
		storebyte((uint8_t) (p->st & 0xff),
			  mbr + partent + PART_OFF_START + 2);
		storebyte((uint8_t) p->sys, mbr + partent + PART_OFF_SYS);
		storebyte((uint8_t) p->eh, mbr + partent + PART_OFF_END);
		storebyte(((uint8_t) ((p->et & 0x300) >> 2)) |
			  ((uint8_t) (p->es & 0x3f)),
			  mbr + partent + PART_OFF_END + 1);
		storebyte((uint8_t) (p->et & 0xff),
			  mbr + partent + PART_OFF_END + 2);
		storedword(p->off, mbr + partent + PART_OFF_OFF);
		storedword(p->size, mbr + partent + PART_OFF_SIZE);
	}
}

static void
dump_part(int partno, part_t p)
{
	printf("%c", (p->active ? '*' : ' '));
	printf("%3d  %5u  %4u %6u %5u  %4u %6u   %6u %11u  ",
	       partno, p->st, p->sh, p->ss, p->et, p->eh, p->es, p->off,
	       p->size);
	switch (p->sys) {
	case PART_SYS_NONE:
		printf("unused");
		break;
	case PART_SYS_FAT12:
		printf("fat12");
		break;
	case PART_SYS_FAT16:
		printf("fat16");
		break;
	case PART_SYS_EXT:
		printf("extended");
		break;
	case PART_SYS_LARGE:
		printf("fat16 large");
		break;
	case PART_SYS_HPFS:
		printf("hpfs");
		break;
	case PART_SYS_FAT32:
		printf("fat32");
		break;
	case PART_SYS_UFS:
		printf("ufs");
		break;
	case PART_SYS_LINUX_SWAP:
		printf("linux swap");
		break;
	case PART_SYS_EXT2FS:
		printf("ext2fs");
		break;
	case PART_SYS_RRFS:
		printf("rrfs");
		break;
	default:
		printf("0x%02x", (uint8_t) p->sys);
	}
	printf("\r\n");
}

#define PART_HDR1                                                       \
    "      ------start------- --------end-------"
#define PART_HDR2                                                       \
    "part  track  head sector track  head sector   offset        size  type"

void
dump_parttab(part_t parttab)
{
	part_t p;
	int i;

	printf("%s\r\n", PART_HDR1);
	printf("%s\r\n", PART_HDR2);
	for (i = 0, p = parttab; i < PARTS; i++, p++)
		dump_part(i, p);
}
