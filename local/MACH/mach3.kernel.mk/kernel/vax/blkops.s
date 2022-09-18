/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie Mellon University
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
 * HISTORY
 * $Log:	blkops.s,v $
 * Revision 2.3  93/01/14  18:00:19  danner
 * 	Ansi cpp fixes.
 * 	[93/01/14            danner]
 * 
 * Revision 2.2  91/07/31  18:17:44  dbg
 * 	Created.
 * 	[91/07/26            dbg]
 * 
 */

/*
 * Block move and copy routines.
 *
 * These are called by the inline assembler code if
 * the size is > 65535.
 */

#include <vax/asm.h>

	.globl	__bcopy
	.globl	_blkcpy
	.align	1
__bcopy:
_blkcpy:
	.word	0x40			# save R6
	movl	4(ap),r1		# source
	movl	8(ap),r3		# dest
	movl	12(ap),r6		# length
0:
	cmpl	r6,$65535		# too long for 1 movc3?
	blequ	1f			# if so:
	movc3	$65535,(r1),(r3)	#    move maximum
					/*    (advances r1 and r3) */
	subl2	$65535,r6		#    adjust length
	brb	0b			#    try again
1:
	movc3	r6,(r1),(r3)		# last move
	ret

	.globl	__bzero
	.globl	_blkclr
	.align	1
__bzero:
_blkclr:
	.word	0x40			# save R6
	movl	4(ap),r3		# dest
	movl	8(ap),r6		# length
0:
	cmpl	r6,$65535		# too long for 1 movc5?
	blequ	1f			# if so:
	movc5	$0,(r3),$0,$65535,(r3)	#    clear maximum (advances r3)
	subl2	$65535,r6		#    adjust length
	brb	0b			#    try again
1:
	movc5	$0,(r3),$0,r6,(r3)	# last clear
	ret
