h05796
s 00002/00002/00020
d D 8.1 93/06/06 15:14:38 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00013
d D 1.2 90/04/09 18:25:57 bostic 2 1
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00015/00000/00000
d D 1.1 82/11/12 12:11:33 mckusick 1 0
c date and time created 82/11/12 12:11:33 by mckusick
e
u
U
t
T
I 1
D 2
/* Copyright (c) 1982 Regents of the University of California */
E 2
I 2
/*-
D 3
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */
E 2

D 2
static char sccsid[] = "%Z%%M% %I% %G%";
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

char EASRTS[] = "Assertion failed: %s\n";

ASRTS(cond, stmt)
	short	cond;
	char	*stmt;
{
	if (cond)
		return;
	ERROR(EASRTS, stmt);
	return;
}
E 1
