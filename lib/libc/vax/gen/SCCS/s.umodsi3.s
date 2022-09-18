h37359
s 00002/00002/00040
d D 8.1 93/06/04 15:44:48 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00039
d D 6.2 91/04/15 11:59:35 donn 2 1
c Add 'contributed' notices (for Keith).
e
s 00039/00000/00000
d D 6.1 91/04/05 09:48:47 donn 1 0
c date and time created 91/04/05 09:48:47 by donn
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Donn Seeley at UUNET Technologies, Inc.
 *
E 2
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

/*
 * Unsigned modulus, GCC flavor.
 */

#include "DEFS.h"

#define	DIVIDEND	4(ap)
#define	DIVISOR		8(ap)

ENTRY(__umodsi3,0)
	movl	DIVISOR,r2
	jlss	Leasy		# big divisor: settle by comparison
	movl	DIVIDEND,r0
	jlss	Lhard		# big dividend: need extended division
	divl3	r2,r0,r1	# small divisor and dividend: signed modulus
	mull2	r2,r1
	subl2	r1,r0
	ret
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
E 1
