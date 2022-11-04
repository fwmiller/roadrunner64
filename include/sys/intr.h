#ifndef __INTR_H
#define __INTR_H

#include <sys/idt.h>

#define disable __asm__ __volatile__("cli")
#define enable __asm__ __volatile__("sti");

void idt_init();
void intr_init();

#endif
