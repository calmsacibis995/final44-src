h31488
s 00002/00002/00040
d D 8.1 93/06/04 15:44:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00039
d D 6.2 91/04/15 11:59:34 donn 2 1
c Add 'contributed' notices (for Keith).
e
s 00039/00000/00000
d D 6.1 91/04/05 09:48:23 donn 1 0
c date and time created 91/04/05 09:48:23 by donn
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
 * Unsigned division, GCC flavor.
 */

#include "DEFS.h"

#define	DIVIDEND	4(ap)
#define	DIVISOR		8(ap)

ENTRY(__udivsi3,0)
	movl	DIVISOR,r2
	jlss	Leasy		# big divisor: settle by comparison
	movl	DIVIDEND,r0
	jlss	Lhard		# big dividend: extended division
	divl2	r2,r0		# small divisor and dividend: signed division
	ret
Lhard:
	clrl	r1
	ediv	r2,r0,r0,r1
	ret
Leasy:
	cmpl	DIVIDEND,r2
	jgequ	Lone		# if dividend is as big or bigger, return 1
	clrl	r0		# else return 0
	ret
Lone:
	movl	$1,r0
	ret
E 1
