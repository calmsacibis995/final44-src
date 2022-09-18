h48083
s 00028/00000/00000
d D 8.1 94/02/16 12:23:22 bostic 1 0
c date and time created 94/02/16 12:23:22 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

#include <machine/machAsmDefs.h>

#if defined(LIBC_SCCS) && !defined(lint)
	ASMSTR("%W% (Berkeley) %G%")
#endif /* LIBC_SCCS and not lint */

	.set	noreorder

/*
 * fabs(x)
 *	double x;
 *
 * Return absolute value of x.
 */
LEAF(fabs)
	j	ra
	abs.d	$f0, $f12		# compute absolute value of x
END(fabs)
E 1
