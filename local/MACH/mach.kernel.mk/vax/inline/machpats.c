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
 * $Log:	machpats.c,v $
 * Revision 2.4  89/03/09  22:15:57  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:19:59  gm0w
 * 	Changes for cleanup.
 * 
 * 18-Apr-88  Steven Schwab (schwab) at Carnegie-Mellon University
 *	Added insqti_ul and remqhi_ul for ultrix compatability.
 *
 *  4-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Removed insqti, remqhi (nowhere used).
 *
 * 27-Feb-87  David Golub (dbg) at Carnegie-Mellon University
 *	Added bit_lock_try, i_bit_set, i_bit_clear.  Removed comments
 *	on arguments for bit_lock operations since they defeat inline's
 *	optimization (inline can't handle comments!).
 *
 * 29-Dec-86  David Golub (dbg) at Carnegie-Mellon University
 *	Changed bbssiloop to bit_lock, bbcciloop to bit_unlock.
 *	Modified to work on 8200 (not hit the bus every cycle).
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 */
/*
 * Copyright (c) 1984, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef	lint
static char sccsid[] = "@(#)machpats.c	7.1 (Berkeley) 6/5/86";
#endif	not lint

#include <inline/inline.h>

/*
 * Pattern table for special VAX instructions.
 */
struct pats machine_ptab[] = {

	{ 3, "_blkcpy\n",
"	movl	(sp)+,r1\n\
	movl	(sp)+,r3\n\
	jbr	2f\n\
1:\n\
	subl2	r0,(sp)\n\
	movc3	r0,(r1),(r3)\n\
2:\n\
	movzwl	$65535,r0\n\
	cmpl	(sp),r0\n\
	jgtr	1b\n\
	movl	(sp)+,r0\n\
	movc3	r0,(r1),(r3)\n" },

	{ 3, "_bcopy\n",
"	movl	(sp)+,r1\n\
	movl	(sp)+,r3\n\
	movl	(sp)+,r5\n\
	movc3	r5,(r1),(r3)\n" },

	{ 3, "_ovbcopy\n",
"	movl	(sp)+,r3\n\
	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	movc3	r5,(r3),(r4)\n" },

	{ 2, "_blkclr\n",
"	movl	(sp)+,r3\n\
	jbr	2f\n\
1:\n\
	subl2	r0,(sp)\n\
	movc5	$0,(r3),$0,r0,(r3)\n\
2:\n\
	movzwl	$65535,r0\n\
	cmpl	(sp),r0\n\
	jgtr	1b\n\
	movl	(sp)+,r0\n\
	movc5	$0,(r3),$0,r0,(r3)\n" },

	{ 2, "_bzero\n",
"	movl	(sp)+,r3\n\
	movl	(sp)+,r5\n\
	movc5	$0,(r3),$0,r5,(r3)\n" },

	{ 2, "_insque\n",
"	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	insque	(r4),(r5)\n" },

	{ 1, "_remque\n",
"	movl	(sp)+,r5\n\
	remque	(r5),r0\n" },

	{ 2, "_remqhi_ul\n",
"	movl	(sp)+,r1\n\
	addl2	$4, sp\n\
1:	remqhi	(r1),r0\n\
	bcs	1b\n\
	bvc	1f\n\
	clrl	r0\n\
1:"},

	{ 3, "_insqti_ul\n",
"	movl	(sp)+,r1\n\
	movl	(sp)+,r2\n\
	addl2	$4, sp\n\
	mnegl	$1, r0\n\
1:	insqti	(r1),(r2)\n\
	bcs	1b\n\
	bneq	1f\n\
	clrl	r0\n\
1:" },

	{ 0, "", "" }
};

struct pats vax_ptab[] = {

	{ 3, "_blkcmp\n",
"	movl	(sp)+,r1\n\
	movl	(sp)+,r3\n\
	jbr	2f\n\
1:\n\
	subl2	r0,(sp)\n\
	cmpc3	r0,(r1),(r3)\n\
	bneq	3f\n\
2:\n\
	movzwl	$65535,r0\n\
	cmpl	(sp),r0\n\
	jgtr	1b\n\
	movl	(sp)+,r0\n\
	cmpc3	r0,(r1),(r3)\n\
3:\n" },

	{ 3, "_bcmp\n",
"	movl	(sp)+,r1\n\
	movl	(sp)+,r3\n\
	movl	(sp)+,r5\n\
	cmpc3	r5,(r1),(r3)\n" },

	{ 3, "_llocc\n",
"	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	movl	(sp)+,r1\n\
1:\n\
	movzwl	$65535,r0\n\
	cmpl	r5,r0\n\
	jleq	1f\n\
	subl2	r0,r5\n\
	locc	r4,r0,(r1)\n\
	jeql	1b\n\
	addl2	r5,r0\n\
	jbr	2f\n\
1:\n\
	locc	r4,r5,(r1)\n\
2:\n" },

	{ 3, "_locc\n",
"	movl	(sp)+,r3\n\
	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	locc	r3,r4,(r5)\n" },

	{ 4, "_scanc\n",
"	movl	(sp)+,r2\n\
	movl	(sp)+,r3\n\
	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	scanc	r2,(r3),(r4),r5\n" },

	{ 3, "_skpc\n",
"	movl	(sp)+,r3\n\
	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	skpc	r3,r4,(r5)\n" },

	{ 2, "_bit_lock\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r1\n\
0:	bbssi	r0,(r1),1f\n\
	brb	2f\n\
1:	bbs	r0,(r1),1b\n\
	brb	0b\n\
2:\n" },

	{ 2, "_bit_unlock\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r1\n\
	bbcci	r0,(r1),0f\n\
0:\n" },

	{ 2, "_bit_lock_try\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r1\n\
	bbssi	r0,(r1),1f\n\
	movl	$1,r0			# success\n\
	brb	2f\n\
1:	clrl	r0			# failure\n\
2:\n" },

	{ 2, "_bbssi\n",
"	movl	$1,r0\n\
	bbssi	(sp),*4(sp),1f\n\
	clrl	r0\n\
1:	addl2	$8,sp\n" },

	{ 2, "_bbcci\n",
"	movl	$1,r0\n\
	bbcci	(sp),*4(sp),1f\n\
	clrl	r0\n\
1:	addl2	$8,sp\n" },

	{ 2, "_i_bit_set\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r1\n\
	bbssi	r0,(r1),1f\n\
1:\n"},

	{ 2, "_i_bit_clear\n",
"	movl	(sp)+,r0\n\
	movl	(sp)+,r1\n\
	bbcci	r0,(r1),1f\n\
1:\n"},

	{ 0, "", "" }
};

struct pats vaxsubset_ptab[] = {

	{ 3, "_blkcmp\n",
"	movl	(sp)+,r1\n\
	movl	(sp)+,r3\n\
	movl	(sp)+,r0\n\
2:\n\
	cmpb	(r1)+,(r3)+\n\
	jneq	3f\n\
	sobgtr	r0,2b\n\
3:\n" },

	{ 3, "_bcmp\n",
"	movl	(sp)+,r1\n\
	movl	(sp)+,r3\n\
	movl	(sp)+,r5\n\
	movl	r5,r0\n\
2:\n\
	cmpb	(r1)+,(r3)+\n\
	jneq	1f\n\
	sobgtr	r0,2b\n\
1:\n" },

	{ 3, "_llocc\n",
"	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	movl	(sp)+,r1\n\
	movl	r5,r0\n\
2:\n\
	cmpb	r4,(r1)+\n\
	jeql	1f\n\
	sobgtr	r0,2b\n\
1:\n" },

	{ 3, "_locc\n",
"	movl	(sp)+,r3\n\
	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	movl	r4,r0\n\
2:\n\
	cmpb	r3,(r5)+\n\
	jeql	1f\n\
	sobgtr	r0,2b\n\
1:\n" },

	{ 3, "_skpc\n",
"	movl	(sp)+,r3\n\
	movl	(sp)+,r4\n\
	movl	(sp)+,r5\n\
	movl	r4,r0\n\
2:\n\
	cmpb	r3,(r5)+\n\
	jneq	1f\n\
	sobgtr	r0,2b\n\
1:\n" },

	{ 0, "", "" }
};
