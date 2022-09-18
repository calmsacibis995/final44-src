/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	rpb.s,v $
 * Revision 2.3  89/02/25  20:28:12  gm0w
 * 	Changes for cleanup.
 * 
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 *  6-Nov-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	We need to know an address to start slaves at, so this in in the
 *	rpb, always at offset 0x10 from the boot load address.
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)rpb.s	7.1 (Berkeley) 6/5/86
 */

/*
 * This has to get loaded first (physical 0) as 780 memory restart rom
 * only looks for rpb on a 64K page boundary (doc isn't wrong,
 * it never says what size "page boundary" rpb has to be on).
 */
ZERO_PHYS:
	.globl	jmp_start
	.globl	_rpb
_rpb:
	.space	16
entry:	jmp	jmp_start
	.space	486
erpb:
	.space	4
