/*-
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "@(#)reset.s	8.1 (Berkeley) 6/4/93"
#endif /* LIBC_SCCS and not lint */

/*
 * C library -- reset, setexit
 *
 *	reset(x)
 * will generate a "return" from
 * the last call to
 *	setexit()
 * by restoring r6 - r12, ap, fp
 * and doing a return.
 * The returned value is x; on the original
 * call the returned value is 0.
 *
 * useful for going back to the main loop
 * after a horrible error in a lowlevel
 * routine.
 */
#include "DEFS.h"

ENTRY(setexit)
	movab	setsav,r0
	movq	r6,(r0)+
	movq	r8,(r0)+
	movq	r10,(r0)+
	movq	8(fp),(r0)+		# ap, fp
	movab	4(ap),(r0)+		# sp
	movl	16(fp),(r0)		# pc
	clrl	r0
	ret

ENTRY(reset)
	movl	4(ap),r0	# returned value
	movab	setsav,r1
	movq	(r1)+,r6
	movq	(r1)+,r8
	movq	(r1)+,r10
	movq	(r1)+,r12
	movl	(r1)+,sp
	jmp 	*(r1)

	.data
setsav:	.space	10*4
