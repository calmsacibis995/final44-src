h46087
s 00002/00002/00024
d D 8.1 93/06/06 15:14:46 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00017
d D 1.5 90/04/09 18:26:00 bostic 5 4
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00002/00003/00017
d D 1.4 88/06/02 19:22:58 mckusick 4 3
c get rid of _sobuf
e
s 00002/00002/00018
d D 1.3 81/12/09 14:04:42 mckusic 3 2
c correct order of args to setbuf as per bug report
e
s 00001/00001/00019
d D 1.2 81/03/07 15:52:17 mckusic 2 1
c merge in onyx changes
e
s 00020/00000/00000
d D 1.1 80/10/30 00:32:51 mckusick 1 0
c date and time created 80/10/30 00:32:51 by mckusick
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1979 Regents of the University of California */
E 5
I 5
/*-
D 6
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */
E 5

D 5
static char sccsid[] = "%Z%%M% %I% %G%";
E 5
I 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

#include "h00vars.h"

D 4
extern char	_sobuf[];

E 4
BUFF(amount)

D 2
	int		amount;
E 2
I 2
	long		amount;
E 2
{
	struct iorec	*curfile;
I 4
	static char	sobuf[BUFSIZ];
E 4

	curfile = OUTPUT;
	if (amount == 0)
D 3
		setbuf(0, ACTFILE(curfile));
E 3
I 3
		setbuf(ACTFILE(curfile), 0);
E 3
	else if (amount == 2)
D 3
		setbuf(_sobuf, ACTFILE(curfile));
E 3
I 3
D 4
		setbuf(ACTFILE(curfile), _sobuf);
E 4
I 4
		setbuf(ACTFILE(curfile), sobuf);
E 4
E 3
}
E 1
