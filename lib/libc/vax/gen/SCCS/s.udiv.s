h07305
s 00002/00002/00067
d D 8.1 93/06/04 15:44:41 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00066
d D 5.6 91/04/15 11:52:08 donn 10 9
c Add 'contributed' notices (for Keith).
e
s 00001/00001/00065
d D 5.5 91/04/08 20:53:40 bostic 9 8
c audiv fix, from Donn
e
s 00014/00010/00052
d D 5.4 91/04/08 14:25:28 bostic 8 7
c update from Donn -- fixes for pcc
e
s 00049/00064/00013
d D 5.3 91/04/08 11:59:48 bostic 7 6
c Donn Seeley, from scratch; Berkeley copyright
e
s 00002/00002/00075
d D 5.2 86/03/09 21:15:37 donn 6 5
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00074
d D 5.1 85/06/05 18:54:04 mckusick 5 4
c Add copyright
e
s 00034/00000/00041
d D 4.4 85/01/16 11:27:33 ralph 4 3
c added audiv() to handle /= properly.
e
s 00001/00001/00040
d D 4.3 84/11/01 23:52:33 sam 3 2
c change ENTRY & ASENTRY to allow setting the register save mask
e
s 00001/00001/00040
d D 4.2 83/06/27 19:52:30 root 2 1
c need assembler entry point
e
s 00041/00000/00000
d D 4.1 83/06/27 15:42:09 root 1 0
c date and time created 83/06/27 15:42:09 by root
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
 *
I 10
 * This code is derived from software contributed to Berkeley by
 * Donn Seeley at UUNET Technologies, Inc.
 *
E 10
 * %sccs.include.redist.c%
 */
E 7
E 6
E 5

I 7
#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

E 7
/*
D 7
 * udiv - unsigned division for vax-11
 *
 * arguments: dividend, divisor.
 * result: quotient.
 * uses r0-r2
 *
 * If 1 < divisor <= 2147483647, zero-extend the dividend
 * to 64 bits and let ediv do the work.  If the divisor is 1,
 * ediv will overflow if bit 31 of the dividend is on, so
 * just return the dividend unchanged.  If the divisor is 0,
 * do the ediv also, so it will generate the proper exception.
 * All other values of the divisor have bit 31 on: in this case
 * the quotient must be 0 if divisor > dividend, and 1 otherwise,
 * provided that the comparison is made as unsigned.
E 7
I 7
 * Unsigned division, PCC flavor.
 * udiv() takes an ordinary dividend/divisor pair;
 * audiv() takes a pointer to a dividend and an ordinary divisor.
E 7
 */

#include "DEFS.h"

D 2
ENTRY(udiv)
E 2
I 2
D 3
ASENTRY(udiv)
E 3
I 3
D 7
ASENTRY(udiv, 0)
E 3
E 2
	movl	4(ap),r0	/* dividend */
	movl	8(ap),r2	/* divisor */
	jeql	1f		/* if divisor=0, force exception */
	cmpl	r2,$1		/* if divisor <= 1 (signed), */
	jleq	2f		/*  no division is necessary */
1:
	clrl	r1		/* zero-extend the dividend */
	ediv	r2,r0,r0,r2	/* divide.  q->r0, r->r2 (discarded) */
E 7
I 7
#define	DIVIDEND	4(ap)
#define	DIVISOR		8(ap)

ASENTRY(udiv,0)
	movl	DIVISOR,r2
	jlss	Leasy		# big divisor: settle by comparison
	movl	DIVIDEND,r0
	jlss	Lhard		# big dividend: extended division
	divl2	r2,r0		# small divisor and dividend: signed division
E 7
	ret
D 7
2:	
	jeql	1f		/* if divisor=1, return dividend */
	cmpl	r0,r2		/* unsigned comparison between */
	jgequ	2f		/*  dividend and divisor */
	clrl	r0		/* dividend < divisor, return 0 */
E 7
I 7
Lhard:
	clrl	r1
	ediv	r2,r0,r0,r1
E 7
	ret
D 7
2:	
	movl	$1,r0		/* dividend >= divisor, return 1 */
1:	
E 7
I 7
Leasy:
	cmpl	DIVIDEND,r2
	jgequ	Lone		# if dividend is as big or bigger, return 1
	clrl	r0		# else return 0
E 7
	ret
I 7
Lone:
	movl	$1,r0
	ret
E 7
I 4

D 7
/*
 * audiv - unsigned division for vax-11
 *
 * arguments: *dividend, divisor.
 * result: quotient in r0 and *dividend.
 * uses r0-r2
 */

#include "DEFS.h"

ASENTRY(audiv, 0)
	movl	*4(ap),r0	/* dividend */
	movl	8(ap),r2	/* divisor */
	jeql	1f		/* if divisor=0, force exception */
	cmpl	r2,$1		/* if divisor <= 1 (signed), */
	jleq	2f		/*  no division is necessary */
1:
	clrl	r1		/* zero-extend the dividend */
	ediv	r2,r0,r0,r2	/* divide.  q->r0, r->r2 (discarded) */
	movl	r0,*4(ap)	/* save result */
E 7
I 7
ASENTRY(audiv,0)
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
	jlss	Lahard		# big dividend: extended division
	divl3	r2,r0,(r3)	# small divisor and dividend: signed division
E 8
I 8
	jlss	La_hard		# big dividend: extended division
	divl2	r2,r0		# small divisor and dividend: signed division
	movl	r0,(r3)		# leave the value of the assignment in r0
E 8
E 7
	ret
D 7
2:
	jeql	1f		/* if divisor=1, return dividend */
	cmpl	r0,r2		/* unsigned comparison between */
	jgequ	2f		/*  dividend and divisor */
	clrl	r0		/* dividend < divisor, return 0 */
	clrl	*4(ap)		/* save result */
E 7
I 7
D 8
Lahard:
E 8
I 8
La_hard:
E 8
	clrl	r1
D 8
	ediv	r2,r0,(r3),r1
E 8
I 8
	ediv	r2,r0,r0,r1
	movl	r0,(r3)
E 8
E 7
	ret
D 7
2:
	movl	$1,r0		/* dividend >= divisor, return 1 */
1:
	movl	r0,*4(ap)	/* save result */
E 7
I 7
D 8
Laeasy:
E 8
I 8
La_easy:
E 8
	cmpl	(r3),r2
D 8
	jgequ	Laone		# if dividend is as big or bigger, store 1
	clrl	(r3)		# else store 0
E 8
I 8
	jgequ	La_one		# if dividend is as big or bigger, return 1
	clrl	r0		# else return 0
	clrl	(r3)
E 8
	ret
D 8
Laone:
	movl	$1,(r3)
E 8
I 8
La_one:
	movl	$1,r0
	movl	r0,(r3)
E 8
E 7
	ret
E 4
E 1
