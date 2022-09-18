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
 * $Log:	dfloat.s,v $
 * Revision 2.2  89/02/25  20:17:29  gm0w
 * 	Changes for cleanup.
 * 
 * 16-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Removed dependency on loadpt.
 *
 * 11-Aug-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed flag name to "D_float" to match 4.3.
 *
 * 17-Dec-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Created.
 */
/*
 *	File:	vax/dfloat.s
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young
 *
 *	Copyright (C) 1985, Avadis Tevanian, Jr., Michael Wayne Young
 */
#include <vax/mtpr.h>

/*
 *	Check to see if we have Dfloat.
 */
	.data
	.globl	_D_float
_D_float:
	.long	0

	.text
	.globl	_dfloat_test
_dfloat_test:
	.word	0
	mfpr	$SCBB,r1			# get old SCB
	movl	0x10(r1),r2			# get old vector
	movab	f_bad,0x10(r1)			# new vector
	movl	$1,_D_float			# assume we've got it
	tstd	r0				# try an instruction
	movl	r2,0x10(r1)			# restore vector
	ret					# done
	.align	2
f_bad:	clrl	_D_float			# no D-Float.
	rei					# go back
