#ifndef __MOTOROLA_146818_H
#define __MOTOROLA_146818_H

/* I/O port addresses */
#define MC146818_ADDR		0x70
#define MC146818_DATA		0x71

/* Commands */
#define MC146818_SEC		0x00
#define MC146818_MIN		0x02
#define MC146818_HOUR		0x04
#define MC146818_WDAY		0x06
#define MC146818_MDAY		0x07
#define MC146818_MON		0x08
#define MC146818_YEAR		0x09
#define MC146818_EXT_MEM_LO	0x30
#define MC146818_EXT_MEM_HI	0x31

#endif
