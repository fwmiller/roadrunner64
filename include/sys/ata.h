#ifndef __ATA_H
#define __ATA_H

#include <stdint.h>
#include <sys/part.h>

#define SECTOR_SIZE		512
#define ATAPI_SECTOR_SIZE	2048

/* Partitions per drive */
#define PARTS			4

#define ATA_CONTROLLERS		2
#define ATA_DRIVES		4

#define ATA0_IOBASE		0x01f0
#define ATA1_IOBASE		0x0170

#define ATA0_CTLBASE		0x03f6
#define ATA1_CTLBASE		0x0376

/* Controller I/O register offsets */
#define ATA_DATA		0	/* 16-bit port */
#define ATA_ERR			0x001	/* Error register (R) */
#define ATA_FEATURE		0x001	/* Features register (W) */
#define ATA_SECTORCNT		0x002	/* Sector count register (RW) */
#define ATA_SECTOR		0x003	/* Sector number reg (LBAlo) (RW) */
#define ATA_TRACKLSB		0x004	/* Cylinder low reg (LBAmid) (RW) */
#define ATA_TRACKMSB		0x005	/* Cylinder High reg (LBAhi) (RW) */
#define ATA_DRVHD		0x006	/* Drive/head register (RW) */
#define ATA_STATUS		0x007	/* Status register (R) */
#define ATA_COMMAND		0x007	/* Command register (W) */

/* Controller Ctl register offsets */
#define ATA_ALT_STATUS		0x00	/* Alternate status register */
#define ATA_DEV_CONTROL		0x00	/* Device control register */
#define ATA_DRVADDR		0x01	/* Drive address register */

/* Controller commands */
#define ATA_CTL_NIEN		0x02	/* nIEN disable interrupt */
#define ATA_CTL_RESET		0x04	/* Reset controller */

/* Drive commands */
#define ATA_CMD_READ		0x20	/* Read sectors with retry */
#define ATA_CMD_WRITE		0x30	/* Write sectors with retry */
#define ATA_CMD_ATAPI_READ	0xa0	/* Identify packet device */
#define ATA_CMD_ATAPI_IDENTIFY	0xa1	/* Identify packet device */
#define ATA_CMD_IDENTIFY	0xec	/* Identify device */

/* Controller status bits */
#define ATA_STAT_ERR		0x01	/* Error */
#define ATA_STAT_IDX		0x02	/* Index */
#define ATA_STAT_CORR		0x04	/* Corrected data */
#define ATA_STAT_DRQ		0x08	/* Data request */
#define ATA_STAT_DSC		0x10	/* Drive seek complete */
#define ATA_STAT_DWF		0x20	/* Drive write fault */
#define ATA_STAT_DRDY		0x40	/* Drive ready */
#define ATA_STAT_BSY		0x80	/* Controller busy */

/* Controller error conditions bits */
#define ATA_ERR_AMNF		0x01	/* Address mark not found */
#define ATA_ERR_TK0NF		0x02	/* Track 0 not found */
#define ATA_ERR_ABRT		0x04	/* Abort */
#define ATA_ERR_MCR		0x08	/* Media change requested */
#define ATA_ERR_IDNF		0x10	/* Sector id not found */
#define ATA_ERR_MC		0x20	/* Media change */
#define ATA_ERR_UNC		0x40	/* Uncorrectable data error */
#define ATA_ERR_BBK		0x80	/* Bad block */

/* Timeouts (in seconds) */
#define ATA_TIMEOUT_OUTB	2
#define ATA_TIMEOUT_DRDY	2
#define ATA_TIMEOUT_DRQ		2

/* ATA drive types */
#define ATA_DRV_NULL		0
#define ATA_DRV_HD		1
#define ATA_DRV_CDROM		2

/* ATA drive flags */
#define ATA_FLAG_FOUND		0x01

/* Parameters returned by read drive parameters command */
struct ata_param {
	/* Drive information */
	uint16_t config;	/* General configuration bits */
	uint16_t cylinders;	/* Cylinders */
	uint16_t reserved;
	uint16_t heads;		/* Heads */
	uint16_t unfbytespertrk;	/* Unformatted bytes/track */
	uint16_t unfbytes;	/* Unformatted bytes/sector */
	uint16_t sectors;	/* Sectors per track */
	uint16_t vendorunique[3];

	/* Controller information */
	uint16_t serial[10];	/* Serial number */
	uint16_t buffertype;	/* Buffer type */
	uint16_t buffersize;	/* Buffer size, in 512-byte units */
	uint16_t necc;		/* ECC bytes appended */
	uint16_t rev[4];	/* Firmware revision */
	uint16_t model[20];	/* Model name */
	uint16_t nsecperint;	/* Sectors per interrupt */
	uint16_t usedmovsd;	/* Can use double word read/write? */
	uint16_t pad[209];
};

struct ata_controller {
	uint16_t iobase;	/* I/O port registers base address */
	uint16_t ctlbase;	/* Ctl port registers base address */
};

struct ata_drive {
	uint8_t flags;
	struct ata_controller *atac;	/* Controller */
	int drive;		/* Drive number */
	int type;		/* Drive type */
	struct ata_param param;	/* Drive parameter block */

	/* Partition information */
	struct part parttab[PARTS];

	/* Geometry */
	uint32_t blks;		/* Number of blocks on drive */
	uint32_t size;		/* Size in Mbytes */
	uint32_t tracks;	/* Number of tracks */
	uint32_t heads;		/* Number of heads */
	uint32_t sectorspertrack;	/* Sectors per track */

	/* Current transfer location */
	uint32_t blkno;		/* Current block */
	uint32_t track;		/* Current track */
	uint32_t head;		/* Current head */
	uint32_t sector;	/* Current sector */
};

struct ata_partition {
	struct ata_drive *atad;
	uint32_t sectors;
	uint32_t offset;
};

typedef struct ata_controller *atac_t;
typedef struct ata_drive *atad_t;
typedef struct ata_partition *atap_t;

int ata_init();
atap_t ata_get_primary_partition();

int ata_read(void *dev, uint8_t * b, int len);

void ata_reset(atac_t atac);
void ata_eoi(atac_t atac);
void ata_select_delay(atac_t atac);
int ata_wait(atac_t atac, uint8_t cmd, uint8_t mask);
uint8_t ata_inb(atac_t atac, uint16_t port);
void ata_outb(atac_t atac, uint16_t port, uint8_t val);

int ata_identify(atad_t atad, char *drvstr);
int ata_read_parttab(atad_t atad);
int ata_seek(atad_t atad, uint32_t blkno);

void ata_convert_string(uint16_t * s, int words);

int atapi_identify(atad_t atad, char *drvstr);

void load_parttab(uint8_t * mbr, part_t parttab);
void write_parttab(part_t parttab, uint8_t * mbr);
void dump_parttab(part_t parttab);

#endif				/* __ATA_H */
