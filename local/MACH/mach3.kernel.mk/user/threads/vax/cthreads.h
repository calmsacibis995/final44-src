/* 
 * Mach Operating System
 * Copyright (c) 1993,1991,1990 Carnegie Mellon University
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
 * $Log:	cthreads.h,v $
 * Revision 2.7  93/01/14  18:06:31  danner
 * 	asm -> __asm__
 * 	[93/01/10            danner]
 * 
 * Revision 2.6  92/01/03  20:37:31  dbg
 * 	Add volatile to spin_lock_t.  Remove operand-match
 * 	constraint from ASM statement in spin_lock_try - rely on
 * 	volatile attribute.
 * 	[91/09/04            dbg]
 * 
 * Revision 2.5  91/07/31  18:40:18  dbg
 * 	Add inline substitution for cthread_sp, spin_unlock,
 * 	spin_try_lock.
 * 	[91/07/25            dbg]
 * 
 * Revision 2.4  91/05/14  18:00:32  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/02/14  14:21:53  mrt
 * 	Added new Mach copyright
 * 	[91/02/13  12:40:08  mrt]
 * 
 * Revision 2.2  90/11/05  14:38:17  rpd
 * 	Created.
 * 	[90/11/01            rwd]
 * 
 */

#ifndef _MACHINE_CTHREADS_H_
#define _MACHINE_CTHREADS_H_

typedef volatile int spin_lock_t;
#define SPIN_LOCK_INITIALIZER	0
#define spin_lock_init(s)	(*(s) = 0)
#define spin_lock_locked(s)	(*(s) != 0)

#ifdef	__GNUC__

#define	spin_unlock(p) \
    ({	__asm__ volatile("	bbcci	$0, %0, 0f\n\
		    0:" \
		    : "=m" (*(p)) ); \
	0; })

#define	spin_try_lock(p)\
    ({	boolean_t _r__; \
	__asm__ volatile("	bbssi	$0, %1, 0f\n\
			movl	$1, %0\n\
			brb	1f\n\
		    0:	clrl	%0\n\
		    1:" \
		    : "=&g" (_r__), "=m" (*(p)) ); \
	_r__; })

#define	cthread_sp() \
    ({	int _sp__; \
	__asm__("	movl	sp, %0" \
	    :	"=g" (_sp__) ); \
	_sp__; })

#endif	/* __GNUC__ */

#endif	/* _MACHINE_CTHREADS_H_ */
