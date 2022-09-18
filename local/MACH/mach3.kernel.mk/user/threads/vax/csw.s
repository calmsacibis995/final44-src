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
 * $Log:	csw.s,v $
 * Revision 2.6  91/10/09  16:21:09  af
 * 	 Revision 2.5.1.1  91/09/16  10:26:18  rpd
 * 	 	Removed inappropriate RCS keywords.
 * 
 * Revision 2.5.1.1  91/09/16  10:26:18  rpd
 * 	Removed inappropriate RCS keywords.
 * 
 * Revision 2.5  91/05/14  18:00:09  mrt
 * 	Correcting copyright
 * 
 * Revision 2.4  91/02/14  14:21:44  mrt
 * 	Added new Mach copyright
 * 	[91/02/13  12:39:50  mrt]
 * 
 * Revision 2.3  90/01/19  14:38:40  rwd
 * 	Change u macro
 * 
 * Revision 2.2  89/12/08  19:55:09  rwd
 * 	Fix cproc_prepare.
 * 	[89/12/05            rwd]
 * 	Routing called was supposed to be cproc_waiting, not
 * 	cthread_waiting.
 * 	[89/12/05            rwd]
 * 	Cproc_prepare compliments of dbg
 * 	[89/11/22            rwd]
 * 	Changed cproc_start to cproc_start_wait.  Added unlock param.
 * 	[89/10/23            rwd]
 * 
 */
/*
 * vax/csw.s
 *
 * Context switch and cproc startup for VAX COROUTINE implementation.
 */

	.text

/*
 * Suspend the current thread and resume the next one.
 *
 *	void
 *	cproc_switch(cur, next, lock)
 *		int *cur;
 *		int *next;
 */
	.align	1
	.globl	_cproc_switch
_cproc_switch:
	.word	0xfc0		/* save current registers */
	movl	fp,*4(ap)	/* save current fp */
	movl	*8(ap),fp	/* restore next fp */
	movl	fp,sp		/* sp = fp */
	bbcci	$0,*12(ap),1f	/* clear lock */
1:	ret			/* return to next thread */

/*
 *	void
 *	cproc_start_wait(parent_context, child, stackp, lock)
 *		int *parent_context;
 *		cproc_t child;
 *		int stackp;
 */
	.align	1
	.globl	_cproc_start_wait
_cproc_start_wait:
	.word	0xfc0			/* save parent registers */
	movl	fp,*4(ap)		/* save parent fp */
	movl	12(ap),sp		/* sp = stackp */
	movl	sp,fp			/* fp = sp */
	pushl	8(ap)
	bbcci	$0,*16(ap),1f		/* clear lock */
1:	calls	$1,_cproc_waiting	/* cproc_waiting(child) */

/*
 *	void
 *	cproc_prepare(child, child_context, stack)
 *		int	*child_context;
 *		int	*stack;
 */
	.globl	_cproc_prepare
_cproc_prepare:
	.word 0
	movl	12(ap),r0	/* get stack */
	movl	4(ap),-(r0)	/* child is argument to cthread_body */
	movl	$1,-(r0)	/* number of arguments */
	movl	r0,r1		/* save AP that child will start with */
	clrl	-(r0)		/* zero return PC from cthread_body */
	clrq	-(r0)		/* zero return AP/FP from cthread_body */
	movl	$0x20000000,-(r0)
				/* set callS frame, no registers saved */
	clrl	-(r0)		/* clear handler */
	movl	r0,r2		/* save FP that child will start with */
	
	movab	_cthread_body+2,-(r0)
				/* PC to return to is cthread_body + 2 */
	movl	r2,-(r0)	/* return FP */
	movl	r1,-(r0)	/* return AP */
	clrq	-(r0)		/* set callG frame, no registers saved ... */
				/* ... and clear handler */
	
	movl	r0,*8(ap)	/* store child context */
	ret
