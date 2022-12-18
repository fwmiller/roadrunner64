/*
 * Portions of this file contain:
 * Copyrigh;t 2015 Philipp Oppermann
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * A port of https://github.com/phil-opp/blog_os/tree/multiboot_bootstrap/src/arch/x86_64/boot.asm
 * from nasm to gas (gnu assembler).
 */

#include <sys/idt.h>

	.section .rodata
	// Global Descriptor Table
	.align	8
gdt64:
	.quad	0 // zero entry

gdt64_code_entry:
	.set	gdt64_code_seg, gdt64_code_entry - gdt64
	.quad	(1<<44) | (1<<47) | (1<<41) | (1<<43) | (1<<53) // code segment

gdt64_data_entry:
	.set	gdt64_data_seg, gdt64_data_entry - gdt64
	.quad	(1<<44) | (1<<47) | (1<<41) // data segment

gdt64_pointer:
	.set	gdt64_limit, gdt64_pointer - gdt64 - 1
	.word	gdt64_limit
	.quad	gdt64

        // Interrupt Descriptor Table
	.align	8
idt64:
	.space	GATES * DESC_SIZE

idt64_pointer:
	.set	idt64_limit, idt64_pointer - idt64 - 1
	.word	idt64_limit
	.quad	idt64

	// Entry code
	.section .text
	.code32
	.global _start
_start:
	movl	$stack_top, %esp

	// Move Multiboot info pointer to edi to pass it to the kernel.
	// We must not move Multiboot info pointer to edi to pass it to
	// the kernel.  We must not modify the `edi` register until the
	// kernel it called.
	movl	%ebx, %edi

	call	check_multiboot
	call	check_cpuid
	call	check_long_mode

	call	set_up_page_tables
	call	enable_paging
	call	set_up_SSE

	// Load the 64-bit GDT
	lgdt	(gdt64_pointer)

	// Update selectors
	movw	$gdt64_data_seg, %ax
	movw	%ax, %ss
	movw	%ax, %ds
	movw	%ax, %es

	// Interrupt Descriptor Table
	lidt	idt64_pointer

	push	%edi
	// Load the Interrupt Descriptor Table (IDT)
	lea	idt64, %edi

#define LOAD_INTR_DESC(INTR)		\
	lea	INTR, %edx;		\
	movl	$(0x08 << 16), %eax;	\
	movw	%dx, %ax;		\
	movw	$0x8f00, %dx;		\
	movl	%eax, (%edi);		\
	movl	%edx, 4(%edi);		\
	xorl	%edx, %edx;		\
	movl	%edx, 8(%edi);		\
	movl	%edx, 12(%edi);		\
	addl	$DESC_SIZE, %edi

	LOAD_INTR_DESC(intr0)
	LOAD_INTR_DESC(intr1)
	LOAD_INTR_DESC(intr2)
	LOAD_INTR_DESC(intr3)
	LOAD_INTR_DESC(intr4)
	LOAD_INTR_DESC(intr4)
	LOAD_INTR_DESC(intr6)
	LOAD_INTR_DESC(intr7)
	LOAD_INTR_DESC(intr8)
	LOAD_INTR_DESC(intr9)

	LOAD_INTR_DESC(intr10)
	LOAD_INTR_DESC(intr11)
	LOAD_INTR_DESC(intr12)
	LOAD_INTR_DESC(intr13)
	LOAD_INTR_DESC(intr14)
	LOAD_INTR_DESC(intr14)
	LOAD_INTR_DESC(intr16)
	LOAD_INTR_DESC(intr17)
	LOAD_INTR_DESC(intr18)
	LOAD_INTR_DESC(intr19)

	LOAD_INTR_DESC(intr20)
	LOAD_INTR_DESC(intr21)
	LOAD_INTR_DESC(intr22)
	LOAD_INTR_DESC(intr23)
	LOAD_INTR_DESC(intr24)
	LOAD_INTR_DESC(intr24)
	LOAD_INTR_DESC(intr26)
	LOAD_INTR_DESC(intr27)
	LOAD_INTR_DESC(intr28)
	LOAD_INTR_DESC(intr29)

	LOAD_INTR_DESC(intr30)
	LOAD_INTR_DESC(intr31)
	LOAD_INTR_DESC(intr32)
	LOAD_INTR_DESC(intr33)
	LOAD_INTR_DESC(intr34)
	LOAD_INTR_DESC(intr34)
	LOAD_INTR_DESC(intr36)
	LOAD_INTR_DESC(intr37)
	LOAD_INTR_DESC(intr38)
	LOAD_INTR_DESC(intr39)

	LOAD_INTR_DESC(intr40)
	LOAD_INTR_DESC(intr41)
	LOAD_INTR_DESC(intr42)
	LOAD_INTR_DESC(intr43)
	LOAD_INTR_DESC(intr44)
	LOAD_INTR_DESC(intr44)
	LOAD_INTR_DESC(intr46)
	LOAD_INTR_DESC(intr47)

	// edi = multiboot info
	pop	%edi

	.extern kmain
	ljmp	$gdt64_code_seg, $kmain

	// Not reached
	hlt

	.code64
	.extern __handl
#define ISR(INTR)			\
	cli;				\
	pushq	%rdi;			\
	movq	$INTR, %rdi;		\
	call	__handl;		\
	popq	%rdi;			\
	sti;				\
	iretq;

intr0:	ISR(0)
intr1:	ISR(1)
intr2:	ISR(2)
intr3:	ISR(3)
intr4:	ISR(4)
intr5:	ISR(5)
intr6:	ISR(6)
intr7:	ISR(7)
intr8:	ISR(8)
intr9:	ISR(9)

intr10:	ISR(10)
intr11:	ISR(11)
intr12:	ISR(12)
intr13:	ISR(13)
intr14:	ISR(14)
intr15:	ISR(15)
intr16:	ISR(16)
intr17:	ISR(17)
intr18:	ISR(18)
intr19:	ISR(19)

intr20:	ISR(20)
intr21:	ISR(21)
intr22:	ISR(22)
intr23:	ISR(23)
intr24:	ISR(24)
intr25:	ISR(25)
intr26:	ISR(26)
intr27:	ISR(27)
intr28:	ISR(28)
intr29:	ISR(29)

intr30:	ISR(30)
intr31:	ISR(31)
intr32:	ISR(32)
intr33:	ISR(33)
intr34:	ISR(34)
intr35:	ISR(35)
intr36:	ISR(36)
intr37:	ISR(37)
intr38:	ISR(38)
intr39:	ISR(39)

intr40:	ISR(40)
intr41:	ISR(41)
intr42:	ISR(42)
intr43:	ISR(43)
intr44:	ISR(44)
intr45:	ISR(45)
intr46:	ISR(46)
intr47:	ISR(47)

	.code32
set_up_page_tables:
	// Recursive map P4
	mov	$p4_table, %eax
	orl	$0b11, %eax		// present + writable
	movl	%eax, (p4_table + 511 * 8)

	// Map first P4 entry to P3 table
	movl	$p3_table, %eax
	orl	$0b11, %eax		// present + writable
	movl	%eax, (p4_table)

	// Map first P3 entry to P2 table
	movl	$p2_table, %eax
	orl	$0b11, %eax		// present + writable
	mov	%eax, (p3_table)

	// Map each P2 entry to a huge 2MiB page
	movl	$0, %ecx		// counter variable
map_p2_table:
	// Map ecx-th P2 entry to a huge page that starts at address
	// (2MiB * ecx)
	movl	$0x200000, %eax		// 2MiB
	mul	%ecx			// start address of ecx-th page
	orl	$0b10000011, %eax	// present + writable + huge
	movl	%eax, p2_table(,%ecx,8) // map ecx-th entry

	inc	%ecx			// increase counter
	cmp	$512, %ecx		// if counter == 512, the
					//   whole P2 table is mapped
	jne	map_p2_table		// else map the next entry

	ret

enable_paging:
	// Load P4 to cr3 register (cpu uses this to access the P4 table)
	movl	$p4_table, %eax
	movl	%eax, %cr3

	// Enable PAE-flag in cr4 (Physical Address Extension)
	movl	%cr4, %eax
	orl	$1 << 5, %eax
	mov	%eax, %cr4

	// Set the long mode bit in the EFER MSR (model specific register)
	mov	$0xC0000080, %ecx
	rdmsr
	orl	$1 << 8, %eax
	wrmsr

	// Enable paging in the cr0 register
	movl	%cr0, %eax
	orl	$1 << 31, %eax
	mov	%eax, %cr0

	ret

// Prints `ERR: ` and the given error code to screen and hangs.
// parameter: error code (in ascii) in al
error:
	movl	$0x4f524f45, (0xb8000)
	movl	$0x4f3a4f52, (0xb8004)
	movl	$0x4f204f20, (0xb8008)
	movb	%al, (0xb800a)
	hlt

// Throw error 0 if eax doesn't contain the Multiboot 2 magic value
// (0x36d76289)
check_multiboot:
	cmpl	$0x36d76289, %eax
	jne	no_multiboot
	ret

no_multiboot:
	movb	$'0', %al
	jmp	error

// Throw error 1 if the CPU doesn't support the CPUID command
check_cpuid:
	pushf				// Store the FLAGS-register
	pop	%eax			// Restore the A-register
	mov	%eax, %ecx		// Set C-register to the A-register
	xor	$1 << 21, %eax		// Flip the ID-bit, which is bit 21
	push	%eax			// Store the A-register
	popf				// Restore the FLAGS-register
	pushf				// Store the FLAGS-register
	pop	%eax			// Restore the A-register
	push	%ecx			// Store the C-register
	popf				// Restore the FLAGS-register
	xor	%ecx, %eax		// Do a XOR-operation on A-register
					//   and C-register
	jz	no_cpuid		// The zero flag is set, no CPUID
	ret				// CPUID is available for use

no_cpuid:
	mov	$'1', %al
	jmp	error

// Throw error 2 if the CPU doesn't support Long Mode
check_long_mode:
	movl	$0x80000000, %eax	// Set the A-register to 0x80000000
	cpuid				// CPU identification
	cmp	$0x80000001, %eax	// Compare A-register with 0x80000001
	jb	no_long_mode		// It is less, there is no long mode
	movl	$0x80000001, %eax	// Set the A-register to 0x80000001
	cpuid				// CPU identification
	test	$1 << 29, %edx		// Test if the LM-bit, which is bit
					//   29, is set in the D-register
	jz	no_long_mode		// They aren't, there is no long mode
	ret

no_long_mode:
	mov	$'2', %al
	jmp	error

// Check for SSE and enable it. If it's not supported throw error "a"
set_up_SSE:
	// Check for SSE
	movl	$0x1, %eax
	cpuid
	testl	$1<<25, %edx
	jz	no_SSE

	// Enable SSE
	movl	%cr0, %eax
	andw	$0xFFFB, %ax		// Clear coprocessor emulation CR0.EM
	orw	$0x2, %ax		// Set coprocessor monitoring CR0.MP
	movl	%eax, %cr0
	movl	%cr4, %eax
	orw	$3 << 9, %ax		// set CR4.OSFXSR and CR4.OSXMMEXCPT
					//   at the same time
	movl	%eax, %cr4
	ret

no_SSE:
	movb	$'a', %al
	jmp	error

// Uninitialized data section contain the page tables and stack
	.section .bss
	.align 4096
p4_table:
	.skip 4096
p3_table:
	.skip 4096
p2_table:
	.skip 4096

stack_bottom:
	.globl stack_bottom

// This value specifies the size of the run-time stack for the single
// thread of execution
	.skip 4096 * 32

stack_top:
	.globl stack_top
