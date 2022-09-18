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
 * $Log:	mdb_hole.s,v $
 * Revision 2.2  89/02/25  20:25:25  gm0w
 * 	Changes for cleanup.
 * 
 */

	.globl	_mdb_hole_begin
	.globl	_mdb_hole_end

	.text
	.align 2

_mdb_hole_begin:
	.asciz "Place Header Here"
	.space 73000

_mdb_hole_end:
	.long 0

