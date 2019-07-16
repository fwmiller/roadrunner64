#ifndef __ATA_H
#define __ATA_H

#include <stdint.h>
#include <part.h>

#define ATAPI_SECTOR_SIZE	2048

/* Partitions per drive */
#define PARTS			4

#define ATA_CONTROLLERS		2
#define ATA_DRIVES		4

#define ATA0_IOBASE		0x01f0
#define ATA1_IOBASE		0x0170

/* Controller registers */
#define ATA_DATA		0	/* 16-bit port */
#define ATA_ERR			0x001
#define ATA_FEATURE		0x001
#define ATA_SECTORCNT		0x002
#define ATA_SECTOR		0x003
#define ATA_TRACKLSB		0x004
#define ATA_TRACKMSB		0x005
#define ATA_DRVHD		0x006
#define ATA_STATUS		0x007
#define ATA_COMMAND		0x007
#define ATA_ALT_STATUS		0x206
#define ATA_CONTROL		0x206

/* Controller commands */
#define ATA_CTL_RESET		0x04

/* Drive commands */
#define ATA_CMD_READ		0x20
#define ATA_CMD_WRITE		0x30
#define ATA_CMD_ATAPI_IDENTIFY	0xa1
#define ATA_CMD_IDENTIFY	0xec

/* Controller status */
#define ATA_STAT_ERR		0x01	/* Error */
#define ATA_STAT_IDX		0x02	/* Index */
#define ATA_STAT_CORR		0x04	/* Corrected data */
#define ATA_STAT_DRQ		0x08	/* Data request */
#define ATA_STAT_DSC		0x10	/* Drive seek complete */
#define ATA_STAT_DWF		0x20	/* Drive write fault */
#define ATA_STAT_DRDY		0x40	/* Drive ready */
#define ATA_STAT_BSY		0x80	/* Controller busy */

/* Controller error conditions */
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
	ushort_t config;	/* General configuration bits */
	ushort_t cylinders;	/* Cylinders */
	ushort_t reserved;
	ushort_t heads;		/* Heads */
	ushort_t unfbytespertrk;	/* Unformatted bytes/track */
	ushort_t unfbytes;	/* Unformatted bytes/sector */
	ushort_t sectors;	/* Sectors per track */
	ushort_t vendorunique[3];

	/* Controller information */
	ushort_t serial[10];	/* Serial number */
	ushort_t buffertype;	/* Buffer type */
	ushort_t buffersize;	/* Buffer size, in 512-byte units */
	ushort_t necc;		/* ECC bytes appended */
	ushort_t rev[4];	/* Firmware revision */
	ushort_t model[20];	/* Model name */
	ushort_t nsecperint;	/* Sectors per interrupt */
	ushort_t usedmovsd;	/* Can use double word read/write? */
	ushort_t pad[209];
};

struct ata_controller {
#if 0
	struct mutex mutex;	/* Controller mutex */
#endif
	ushort_t iobase;	/* I/O port registers base address */
};

struct ata_drive {
	uchar_t flags;
	struct ata_controller *atac;	/* Controller */
	int drive;		/* Drive number */
	int type;		/* Drive type */
	struct ata_param param;	/* Drive parameter block */

	/* Partition information */
	struct part parttab[PARTS];

	/* Geometry */
	uint_t blks;		/* Number of blocks on drive */
	uint_t size;		/* Size in Mbytes */
	uint_t tracks;		/* Number of tracks */
	uint_t heads;		/* Number of heads */
	uint_t sectorspertrack;	/* Sectors per track */

	/* Current transfer location */
	uint_t blkno;		/* Current block */
	uint_t track;		/* Current track */
	uint_t head;		/* Current head */
	uint_t sector;		/* Current sector */
};

struct ata_partition {
	struct ata_drive *atad;
	ulong_t sectors;
	ulong_t offset;
};

typedef struct ata_controller *atac_t;
typedef struct ata_drive *atad_t;
typedef struct ata_partition *atap_t;

int ata_init();
int ata_get_boot_device(uchar_t drv, char *device);
int ata_ioctl(void *dev, int cmd, void *args);
int ata_read(void *dev, uchar_t * b, int *len);
#if 0
int ata_write(void *dev, buf_t * b);
#endif

#endif
