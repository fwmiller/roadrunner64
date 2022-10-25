#include <sys/idt.h>

	.section .rodata
	// Interrupt Descriptor Table
	.align	4
	.globl	idt64
idt64:
	.space	GATES * DESC_SIZE

idt64_pointer:
	.short	(GATES * DESC_SIZE) - 1
	.quad	idt64

	.globl __isr
__isr:
	iret
