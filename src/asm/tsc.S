	/*--------------------------------------------------------------------
	 *
	 * Read Pentium timestamp counter
	 *
	 */
	.globl		tscread
tscread:
	/* Opcode for reading Pentium timestamp counter */
	.byte		0x0f
	.byte		0x31
	ret
