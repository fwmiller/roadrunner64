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

#ifndef __PART_H
#define __PART_H

#include <stdint.h>

#define PARTS			4

#define PART_ENT_SIZE		0x0010
#define PART_ENT_1		0x01be
#define PART_ENT_2		0x01ce
#define PART_ENT_3		0x01de
#define PART_ENT_4		0x01ee

#define PART_OFF_BOOT		0
#define PART_OFF_START		1
#define PART_OFF_SYS		4
#define PART_OFF_END		5
#define PART_OFF_OFF		8
#define PART_OFF_SIZE		12

typedef struct part {
	uint8_t active;		/* Active entry?  */

#define PART_SYS_NONE		0x00
#define PART_SYS_FAT12		0x01
#define PART_SYS_FAT16		0x04
#define PART_SYS_EXT		0x05
#define PART_SYS_LARGE		0x06
#define PART_SYS_HPFS		0x07
#define PART_SYS_FAT32		0x0c
#define PART_SYS_UFS		0xa5
#define PART_SYS_LINUX_SWAP	0x82
#define PART_SYS_EXT2FS		0x83
#define PART_SYS_RRFS		0xcc
	uint8_t sys;		/* File system type */

	uint32_t st;		/* Start track */
	uint32_t sh;		/* Start head */
	uint32_t ss;		/* Start sector */
	uint32_t et;		/* End track */
	uint32_t eh;		/* End head */
	uint32_t es;		/* End sector */
	uint32_t off;		/* Sector offset */
	uint32_t size;		/* Number of sectors */
} *part_t;

void dump_parttab(part_t parttab);
void read_parttab(uint8_t * mbr, part_t parttab);
void write_parttab(part_t parttab, uint8_t * mbr);

#endif
