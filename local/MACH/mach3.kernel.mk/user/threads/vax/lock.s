/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
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
 * $Log:	lock.s,v $
 * Revision 2.5  91/10/09  16:21:32  af
 * 	 Revision 2.4.1.1  91/09/16  10:26:24  rpd
 * 	 	Removed inappropriate RCS keywords.
 * 
 * Revision 2.4.1.1  91/09/16  10:26:24  rpd
 * 	Removed inappropriate RCS keywords.
 * 
 * Revision 2.4  91/05/14  18:00:43  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/02/14  14:22:00  mrt
 * 	Added new Mach copyright
 * 	[91/02/13  12:40:12  mrt]
 * 
 * Revision 2.2  89/12/08  19:55:27  rwd
 * 	Fix two typos
 * 	[89/12/05            rwd]
 * 	Only spins are simple locks.
 * 	[89/10/23            rwd]
 * 
 */
/*
 * vax/lock.s
 *
 * Mutex implementation for VAX.
 */

	.text
/*
 *	int
 *	spin_try_lock(m)
 *		int *m;
 */
	.align	1
	.globl	_spin_try_lock
_spin_try_lock:
	.word	0
	bbssi	$0,*4(ap),1f
	movl	$1,r0		/* yes */
	ret
1:
	clrl	r0		/* no */
	ret

/*
 *	void
 *	spin_unlock(m)
 *		int *m;
 */
	.align	1
	.globl	_spin_unlock
_spin_unlock:
	.word	0
	bbcci	$0,*4(ap),1f
1:	ret
