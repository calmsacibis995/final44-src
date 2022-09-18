h32465
s 00002/00002/00035
d D 8.1 93/06/06 15:19:08 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00028
d D 1.3 90/04/09 18:27:38 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00002/00001/00028
d D 1.2 81/03/07 16:02:12 mckusic 2 1
c merge in onyx changes
e
s 00029/00000/00000
d D 1.1 80/10/30 00:35:16 mckusick 1 0
c date and time created 80/10/30 00:35:16 by mckusick
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1979 Regents of the University of California */
E 3
I 3
/*-
D 4
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */
E 3

D 3
static char sccsid[] = "%Z%%M% %I% %G%";
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "h00vars.h"

I 2
bool
E 2
RELTLT(bytecnt, left, right)

D 2
	int		bytecnt;
E 2
I 2
	long		bytecnt;
E 2
	register long	*left;
	register long	*right;
{
	register int	longcnt;

	longcnt = bytecnt >> 2;
	do	{
		if ((*left & ~*right) != 0)
			return FALSE;
		if ((*right++ & ~*left++) != 0)
			goto leq;
	} while (--longcnt);
	return FALSE;
leq:
	while (--longcnt) {
		if ((*left++ & ~*right++) != 0) 
			return FALSE;
	}
	return TRUE;
}
E 1
