#ifndef __INTR_H
#define __INTR_H

#define disable __asm__ __volatile__("cli")
#define enable __asm__ __volatile__("sti");

void intr_init();

#endif
