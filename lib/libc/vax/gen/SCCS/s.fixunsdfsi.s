h02170
s 00002/00002/00030
d D 8.1 93/06/04 15:44:19 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00032/00000/00000
d D 5.1 92/06/25 09:11:44 bostic 1 0
c date and time created 92/06/25 09:11:44 by bostic
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
Lbig:	.double	0d2.14748364800000000000e+09
	.text

/*
 * VAX conversions overflow politely,
 * but we'll be conservative just in case someone is trapping overflow.
 */
ENTRY(__fixunsdfsi, 0)
	cmpd	4(ap),Lbig
	jgeq	1f
	cvtdl	4(ap),r0
	ret

1:	subd3	Lbig,4(ap),r0
	cvtdl	r0,r0
	addl2	$2147483648,r0
	ret
E 1
