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
 * $Log:	lock.h,v $
 * Revision 2.3  91/05/14  17:44:15  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:18:52  dbg
 * 	Created.
 * 	[91/03/21            dbg]
 * 
 */

/*
 * Machine-dependent simple locks for the vax.
 */
#ifndef	_VAX_LOCK_H_
#define	_VAX_LOCK_H_

/*
 *	The code here depends on the GNU C compiler.
 */

/*
 *	Simple-lock routines.
 */
#define	simple_lock_init(l) \
	((l)->lock_data = 0)

#ifdef	__GNUC__

#define	simple_lock(l) \
    ({	asm volatile("	brb	1f\n\
		    0:	blbs	%0, 0b\n\
		    1:	bbssi	$0, %0, 0b" \
		    : \
		    : "m" (*(volatile int *)(l)) ); \
	0; })

#define	simple_unlock(l) \
    ({	asm volatile("	bbcci	$0, %0, 0f\n\
		    0:"\
		    : \
		    : "m" (*(volatile int *)(l)) ); \
	0; })

#define	simple_lock_try(l) \
    ({	int _lv__; \
	asm volatile("	bbssi	$0, %1, 0f\n\
			movl	$1, %0\n\
			brb	1f\n\
		    0:	clrl	%0\n\
		    1:" \
		    : "=g" (_lv__) \
		    : "m" (*(volatile int *)(l)) ); \
	_lv__; })

/*
 *	General bit-lock routines.
 */
#define	bit_lock(bit, l) \
    ({	asm volatile("	brb	1f\n\
		    0:	bbs	%0, %1, 0b\n\
		    1:	bbssi	%0, %1, 0b" \
		    : \
		    : "g" (bit), "m" (*(volatile int *)(l))); \
	0; })

#define	bit_unlock(bit, l) \
    ({	asm volatile("	bbcci	%0, %1, 0f\n\
		    0:"\
		    : \
		    : "g" (bit), "m" (*(volatile int *)(l))); \
	0; })

/*
 *	Set or clear individual bits in a long word.
 *	The locked access is needed only to lock access
 *	to the word, not to individual bits.
 */
#define	i_bit_set(bit, l) \
    ({	asm volatile("	bbssi %0, %1, 0f\n\
		    0:" \
		    : \
		    : "g" (bit), "m" (*(volatile int *)l)); \
	0; })

#define	i_bit_clear(bit, l) \
    ({	asm volatile("	bbcci %0, %1, 0f\n\
		    0:" \
		    : \
		    : "g" (bit), "m" (*(volatile int *)l)); \
	0; })

#endif	/* __GNUC__ */

#endif	/* _VAX_LOCK_H_ */
