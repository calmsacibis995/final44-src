h08986
s 00002/00002/00023
d D 8.1 93/06/04 13:02:41 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00000/00000
d D 5.1 92/06/25 06:37:59 torek 1 0
c date and time created 92/06/25 06:37:59 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 *
 * from: $Header: setlogin.s,v 1.1 91/07/06 13:06:00 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
	.asciz "%W% (Berkeley) %G%"
#endif /* LIBC_SCCS and not lint */

#include "SYS.h"

	.globl	__logname_valid		/* in getlogin() */

SYSCALL(setlogin)
	sethi	%hi(__logname_valid), %g1
	retl
	 st	%g0, [%g1 + %lo(__logname_valid)]
E 1
