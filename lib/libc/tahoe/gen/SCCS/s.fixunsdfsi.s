h58173
s 00002/00002/00028
d D 8.1 93/06/04 13:17:14 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00030/00000/00000
d D 5.1 92/07/19 14:35:00 bostic 1 0
c date and time created 92/07/19 14:35:00 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "DEFS.h"

	.data
	.align	2
Lbig:	.long	0x50000000, 0x00000000 # .double 2147483648
	.text

ENTRY(__fixunsdfsi, 0)
	cmpd2	4(fp),Lbig
	jgeq	1f
	ldd	4(fp)
	cvdl	r0
	ret

1:	ldd	4(fp)
	subd	Lbig
	cvdl	r0
	addl2	$2147483648,r0
	ret
E 1
