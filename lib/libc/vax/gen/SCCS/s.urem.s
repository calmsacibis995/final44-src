h24577
s 00002/00002/00067
d D 8.1 93/06/04 15:44:56 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00066
d D 5.6 91/04/15 11:52:09 donn 10 9
c Add 'contributed' notices (for Keith).
e
s 00001/00001/00065
d D 5.5 91/04/08 21:49:25 donn 9 8
c Fix goof in urem() too...
e
s 00012/00008/00054
d D 5.4 91/04/08 14:25:30 bostic 8 7
c update from Donn -- fixes for pcc
e
s 00053/00066/00009
d D 5.3 91/04/08 12:05:46 bostic 7 6
c Donn Seeley, from scratch; Berkeley copyright
e
s 00002/00002/00073
d D 5.2 86/03/09 21:15:48 donn 6 5
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00072
d D 5.1 85/06/05 18:54:28 mckusick 5 4
c Add copyright
e
s 00033/00000/00040
d D 4.4 85/01/16 11:27:03 ralph 4 3
c added aurem() to handle %= properly.
e
s 00001/00001/00039
d D 4.3 84/11/01 23:52:36 sam 3 2
c change ENTRY & ASENTRY to allow setting the register save mask
e
s 00001/00001/00039
d D 4.2 83/06/27 19:52:34 root 2 1
c need assembler entry point
e
s 00040/00000/00000
d D 4.1 83/06/27 15:42:11 root 1 0
c date and time created 83/06/27 15:42:11 by root
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
D 6
#ifndef lint
E 6
I 6
D 7
#ifdef LIBC_SCCS
E 6
	.asciz	"%W% (Berkeley) %G%"
D 6
#endif not lint
E 6
I 6
#endif LIBC_SCCS
E 6
E 5

/*
 * urem - unsigned remainder for vax-11
E 7
I 7
/*-
D 11
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
E 7
 *
I 10
 * This code is derived from software contributed to Berkeley by
 * Donn Seeley at UUNET Technologies, Inc.
 *
E 10
D 7
 * arguments: dividend, divisor
 * result: remainder
 * uses r0-r2
 *
 * if 1 < divisor <= 2147483647, zero-extend the dividend
 * to 64 bits and let ediv do the work.  If the divisor is 1,
 * ediv will overflow if bit 31 of the dividend is on, so
 * just return 0.  If the divisor is 0, do the ediv also,
 * so it will generate the proper exception.  All other values
 * of the divisor have bit 31 on: in this case the remainder
 * must be the dividend if divisor > dividend, and the dividend
 * minus the divisor otherwise.  The comparison must be unsigned.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */
D 7
#include "DEFS.h"
E 7

D 2
ENTRY(urem)
E 2
I 2
D 3
ASENTRY(urem)
E 3
I 3
D 7
ASENTRY(urem, 0)
E 3
E 2
	movl	4(ap),r0	/* dividend */
	movl	8(ap),r2	/* divisor */
	jeql	1f		/* if divisor=0, force exception */
	cmpl	r2,$1		/* if divisor <= 1 (signed), */
	jleq	2f		/*  no division is necessary */
1:
	clrl	r1		/* zero-extend the dividend */
	ediv	r2,r0,r2,r0	/* divide.  q->r2 (discarded), r->r0 */
	ret
2:
	jneq	1f		/* if divisor=1, return 0 */
	clrl	r0		/*  (because doing the divide will overflow */
	ret			/*  if the dividend has its high bit on) */
1:
	cmpl	r0,r2		/* if dividend < divisor (unsigned) */
	jlssu	1f		/*  remainder is dividend */
	subl2	r2,r0		/*  else remainder is dividend - divisor */
1:
	ret
E 7
I 7
#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */
E 7
I 4

I 7
#include "DEFS.h"

E 7
/*
D 7
 * aurem - unsigned remainder for vax-11
 *
 * arguments: *dividend, divisor
 * result: remainder in r0 and *dividend
 * uses r0-r2
E 7
I 7
 * Unsigned modulus, PCC flavor.
 * urem() takes an ordinary dividend/divisor pair;
 * aurem() takes a pointer to a dividend and an ordinary divisor.
E 7
 */
D 7
#include "DEFS.h"
E 7

D 7
ASENTRY(aurem, 0)
	movl	*4(ap),r0	/* dividend */
	movl	8(ap),r2	/* divisor */
	jeql	1f		/* if divisor=0, force exception */
	cmpl	r2,$1		/* if divisor <= 1 (signed), */
	jleq	2f		/*  no division is necessary */
1:
	clrl	r1		/* zero-extend the dividend */
	ediv	r2,r0,r2,r0	/* divide.  q->r2 (discarded), r->r0 */
	movl	r0,*4(ap)	/* save result */
E 7
I 7
#define	DIVIDEND	4(ap)
#define	DIVISOR		8(ap)

ASENTRY(urem,0)
	movl	DIVISOR,r2
	jlss	Leasy		# big divisor: settle by comparison
	movl	DIVIDEND,r0
	jlss	Lhard		# big dividend: need extended division
	divl3	r2,r0,r1	# small divisor and dividend: signed modulus
	mull2	r2,r1
	subl2	r1,r0
E 7
	ret
D 7
2:
	jneq	1f		/* if divisor=1, return 0 */
	clrl	r0		/*  (because doing the divide will overflow */
	clrl	*4(ap)		/*  if the dividend has its high bit on) */
	ret	
1:
	cmpl	r0,r2		/* if dividend < divisor (unsigned) */
	jlssu	1f		/*  remainder is dividend */
	subl2	r2,r0		/*  else remainder is dividend - divisor */
1:
	movl	r0,*4(ap)	/* save result */
E 7
I 7
Lhard:
	clrl	r1
	ediv	r2,r0,r1,r0
	ret
Leasy:
	subl3	r2,DIVIDEND,r0
	jcc	Ldifference	# if divisor goes in once, return difference
	movl	DIVIDEND,r0	# if divisor is bigger, return dividend
Ldifference:
	ret

ASENTRY(aurem,0)
I 9
	movl	DIVIDEND,r3
E 9
	movl	DIVISOR,r2
D 8
	jlss	Laeasy		# big divisor: settle by comparison
E 8
I 8
	jlss	La_easy		# big divisor: settle by comparison
E 8
D 9
	movl	DIVIDEND,r3
E 9
	movl	(r3),r0
D 8
	jlss	Lahard		# big dividend: need extended division
E 8
I 8
	jlss	La_hard		# big dividend: need extended division
E 8
	divl3	r2,r0,r1	# small divisor and dividend: signed modulus
	mull2	r2,r1
D 8
	subl3	r1,r0,(r3)
E 8
I 8
	subl2	r1,r0
	movl	r0,(r3)		# leave the value of the assignment in r0
E 8
	ret
D 8
Lahard:
E 8
I 8
La_hard:
E 8
	clrl	r1
D 8
	ediv	r2,r0,r1,(r3)
E 8
I 8
	ediv	r2,r0,r1,r0
	movl	r0,(r3)
E 8
	ret
D 8
Laeasy:
E 8
I 8
La_easy:
E 8
	subl3	r2,(r3),r0
D 8
	jcs	Ldividend	# if divisor is bigger, leave dividend alone
E 8
I 8
	jcs	La_dividend	# if divisor is bigger, leave dividend alone
E 8
	movl	r0,(r3)		# if divisor goes in once, store difference
D 8
Ldividend:
E 8
I 8
	ret
La_dividend:
	movl	(r3),r0
E 8
E 7
	ret
E 4
E 1
