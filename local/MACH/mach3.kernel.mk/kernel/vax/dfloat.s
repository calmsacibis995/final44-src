/* 
 * Mach Operating System
 * Copyright (c) 1991,1989,1987,1985 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 *	File:	vax/dfloat.s
 *	Author:	Avadis Tevanian, Jr., Michael Wayne Young, 1985
 *
 *	Assembly hacks to see if the cpu has D-Floating Point
 *	support.
 *
 * HISTORY
 * $Log:	dfloat.s,v $
 * Revision 2.4  93/02/01  09:53:20  danner
 * 	Cpp fixup.
 * 
 * Revision 2.3  91/05/14  17:43:06  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:16:54  dbg
 * 	Fix for ANSI C preprocessor.
 * 	[91/04/23            dbg]
 * 
 * Revision 2.1  89/08/03  16:27:27  rwd
 * Created.
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
	mfpr	$ SCBB,r1			# get old SCB
	movl	0x10(r1),r2			# get old vector
	movab	f_bad,0x10(r1)			# new vector
	movl	$1,_D_float			# assume we`ve got it
	tstd	r0				# try an instruction
	movl	r2,0x10(r1)			# restore vector
	ret					# done
	.align	2
f_bad:	clrl	_D_float			# no D-Float.
	rei					# go back
