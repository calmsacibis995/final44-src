/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	SYS.h,v $
 * Revision 2.5  93/01/14  18:13:35  danner
 * 	Ansi cpp fixes.
 * 
 * Revision 2.4  92/01/24  18:16:20  rpd
 * 	Fixed for STDC.
 * 	[92/01/24            rpd]
 * 
 * Revision 2.3  92/01/23  15:22:43  rpd
 * 	Removed dependency on syscall.h by adding
 * 	an explicit definition of SYS_fork.
 * 	[92/01/16            rpd]
 * 
 * Revision 2.2  92/01/16  00:02:09  rpd
 * 	Moved from user collection to mk collection.
 * 
 * Revision 2.2  91/04/11  11:45:22  mrt
 * 	Copied from libc.a
 * 
 * 
 */
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)SYS.h	5.1 (Berkeley) 6/5/85
 */

#ifdef	__STDC__
#define concat(a, b)	a ## b
#else	__STDC__
#define concat(a, b)	a/**/b
#endif	__STDC__

#ifdef PROF
#define	ENTRY(x)	.globl concat(_,x); .align 2; concat(_,x): .word 0; \
			.data; 1:; .long 0; .text; moval 1b,r0; jsb mcount
#else
#define	ENTRY(x)	.globl concat(_,x); .align 2; concat(_,x): .word 0
#endif PROF
#define	SYSCALL(x)	err: jmp cerror; ENTRY(x); chmk $ concat(SYS_,x); jcs err
#define	PSEUDO(x,y)	ENTRY(x); chmk $ concat(SYS_,y)
#define	CALL(x,y)	calls $x, concat(_,y)

	.globl	cerror
