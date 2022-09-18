h15504
s 00002/00002/00026
d D 8.1 93/06/04 13:01:29 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00000/00000
d D 5.1 92/06/25 06:17:00 torek 1 0
c date and time created 92/06/25 06:17:00 by torek
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
 * from: $Header: isnan.c,v 1.1 91/07/08 19:03:34 torek Exp $
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <machine/ieee.h>

isnan(d)
	double d;
{
	register struct ieee_double *p = (struct ieee_double *)&d;

	return (p->dbl_exp == DBL_EXP_INFNAN &&
	    (p->dbl_frach != 0 || p->dbl_fracl != 0));
}
E 1
