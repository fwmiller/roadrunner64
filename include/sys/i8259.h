#ifndef __INTEL_8259_H
#define __INTEL_8259_H

/* I/O port addresses */
#define I8259_MSTR_CTRL 0x20
#define I8259_MSTR_MASK 0x21

#define I8259_SLV_CTRL 0xa0
#define I8259_SLV_MASK 0xa1

/* Master commands */
#define I8259_MSTR_ICW1 0x11
#define I8259_MSTR_ICW2 0x20
#define I8259_MSTR_ICW3 0x04
#define I8259_MSTR_ICW4 0x01
#define I8259_MSTR_DISABLE 0xfb /* All but cascade */

/* Slave commands */
#define I8259_SLV_ICW1 0x11
#define I8259_SLV_ICW2 0x28
#define I8259_SLV_ICW3 0x02
#define I8259_SLV_ICW4 0x01
#define I8259_SLV_DISABLE 0xff

#define I8259_EOI_TMR 0x60
#define I8259_EOI_KBD 0x61
#define I8259_EOI_CAS 0x62
#define I8259_EOI_SERALT 0x63
#define I8259_EOI_SERPRI 0x64
#define I8259_EOI_FD 0x66
#define I8259_EOI_HD 0x66

#endif
