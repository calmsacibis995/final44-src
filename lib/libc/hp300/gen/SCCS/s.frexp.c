h08277
s 00002/00002/00037
d D 8.1 93/06/04 12:24:38 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00000/00000
d D 5.1 91/03/06 18:09:30 bostic 1 0
c date and time created 91/03/06 18:09:30 by bostic
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
#include <math.h>

double
frexp(value, eptr)
	double value;
	int *eptr;
{
	union {
                double v;
                struct {
                        u_int  u_sign :  1;
			u_int   u_exp : 11;
			u_int u_mant1 : 20;
			u_int u_mant2 : 32;
                } s;
        } u;

	if (value) {
		u.v = value;
		*eptr = u.s.u_exp - 1022;
		u.s.u_exp = 1022;
		return(u.v);
	} else {
		*eptr = 0;
		return((double)0);
	}
}
E 1
