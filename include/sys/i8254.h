#ifndef __INTEL_8254_H
#define __INTEL_8254_H

#define I8254_CLK 1193182

/* I/O port addresses */
#define I8254_CNTR_0 0x40
#define I8254_CNTR_1 0x41
#define I8254_CNTR_2 0x42
#define I8254_CTRL 0x43

/* Commands */
#define I8254_CNTR_0_START 0x34
#define I8254_CNTR_0_LATCH 0x00

#endif
