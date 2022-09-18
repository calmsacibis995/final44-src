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
 * $Log:	libcpats.c,v $
 * Revision 2.3  89/03/09  22:15:50  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  20:19:53  gm0w
 * 	Changes for cleanup.
 * 
 */
/*
 * Copyright (c) 1984, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef	lint
static char sccsid[] = "@(#)libcpats.c	7.1 (Berkeley) 6/5/86";
#endif	not lint

#include <inline/inline.h>

/*
 * Pattern table for the C library.
 */
struct pats libc_ptab[] = {

	{ 1, "_fgetc\n",
"	sobgeq	*(sp),1f\n\
	calls	$1,__filbuf\n\
	jbr     2f\n\
1:\n\
	addl3	$4,(sp)+,r1\n\
	movzbl	*(r1),r0\n\
	incl	(r1)\n\
2:\n" },

	{ 2, "_fputc\n",
"	sobgeq	*4(sp),1f\n\
	calls	$2,__flsbuf\n\
	jbr	2f\n\
1:\n\
	movq	(sp)+,r0\n\
	movb	r0,*4(r1)\n\
	incl	4(r1)\n\
2:\n" },

	{ 0, "", "" }
};

struct pats vaxsubset_libc_ptab[] = {

	{ 1, "_strlen\n",
"	movl	(sp)+,r5\n\
	movl	r5,r1\n\
1:\n\
	tstb	(r1)+\n\
	jneq	1b\n\
	decl	r1\n\
	subl3	r5,r1,r0\n" },

	{ 0, "", "" }
};

struct pats vax_libc_ptab[] = {

	{ 1, "_strlen\n",
"	movl	(sp)+,r5\n\
	movl	r5,r1\n\
1:\n\
	locc	$0,$65535,(r1)\n\
	jeql	1b\n\
	subl3	r5,r1,r0\n" },

	{ 0, "", "" }
};
