/*
 *  Roadrunner/pk
 *    Copyright (C) 1989-2001  Cornfed Systems, Inc.
 *
 *  The Roadrunner/pk operating system is free software; you can
 *  redistribute and/or modify it under the terms of the GNU General
 *  Public License, version 2, as published by the Free Software
 *  Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA 02111-1307 USA
 *
 *  More information about the Roadrunner/pk operating system of
 *  which this file is a part is available on the World-Wide Web
 *  at: http://www.cornfed.com.
 *
 */



	/*--------------------------------------------------------------------
	 *
	 * System halt
	 *
	 */
	.align		4, 0x90
	.globl		halt
halt:
	hlt
	jmp		halt

	/*--------------------------------------------------------------------
	 *
	 * System restart
	 *
	 */
	.align		4, 0x90
	.globl		reboot
reboot:
	inb		$I8255_PORT_A, %al
	inb		$I8255_PORT_A, %al

	movb		$I8255_REBOOT, %al
	outb		%al, $I8255_CTRL

rebootloop:
	jmp		rebootloop

	/*--------------------------------------------------------------------
	 *
	 * Read Pentium timestamp counter
	 *
	 */
	.globl		tscread
tscread:
	pushl		%ebp
	movl		%esp, %ebp

	movl		8(%ebp), %edi

	/* Opcode for reading Pentium timestamp counter */
	.byte		0x0f
	.byte		0x31

	movl		%edx, (%edi)
	addl		$4, %edi
	movl		%eax, (%edi)

	leave
	ret
	.align		2, 0x90
