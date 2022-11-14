#include <sys/idt.h>

	.section .rodata
	// Interrupt Descriptor Table
	.align	4
	.globl	idt64
idt64:
	.space	GATES * DESC_SIZE

	.globl	idt64_pointer
idt64_pointer:
	.short	(GATES * DESC_SIZE) - 1
	.quad	idt64

	.globl __gp_excp
__gp_excp:
	push	%rdi

	mov	'%', %rdi
	call	uart_putchar

	pop	%rdi
	iretq

	.globl __tmr_isr
__tmr_isr:
	push	%rdi

	mov	'!', %rdi
	call	uart_putchar

	pop	%rdi
	iretq
