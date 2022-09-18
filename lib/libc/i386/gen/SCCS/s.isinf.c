h10067
s 00002/00002/00036
d D 8.1 93/06/04 15:39:31 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00038/00000/00000
d D 5.1 91/03/18 16:52:52 bostic 1 0
c date and time created 91/03/18 16:52:52 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>

isnan(d)
	double d;
{
	register struct IEEEdp {
		u_int manl : 32;
		u_int manh : 20;
		u_int  exp : 11;
		u_int sign :  1;
	} *p = (struct IEEEdp *)&d;

	return(p->exp == 2047 && (p->manh || p->manl));
}

isinf(d)
	double d;
{
	register struct IEEEdp {
		u_int manl : 32;
		u_int manh : 20;
		u_int  exp : 11;
		u_int sign :  1;
	} *p = (struct IEEEdp *)&d;

	return(p->exp == 2047 && !p->manh && !p->manl);
}
E 1
