h40405
s 00002/00002/00024
d D 8.1 93/06/06 15:16:59 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00017
d D 1.4 90/04/09 18:26:40 bostic 4 3
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00002/00018
d D 1.3 81/06/10 00:38:24 mckusic 3 2
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00001/00001/00019
d D 1.2 81/03/07 15:57:34 mckusic 2 1
c merge in onyx changes
e
s 00020/00000/00000
d D 1.1 80/10/30 00:33:42 mckusick 1 0
c date and time created 80/10/30 00:33:42 by mckusick
e
u
U
t
T
I 1
D 4
/* Copyright (c) 1979 Regents of the University of California */
E 4
I 4
/*-
D 5
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */
E 4

D 4
static char sccsid[] = "%Z%%M% %I% %G%";
E 4
I 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

#include "h00vars.h"
D 3
#include "h01errs.h"
E 3

LLIMIT(curfile, limit)

	register struct iorec	*curfile;
D 2
	int			limit;
E 2
I 2
	long			limit;
E 2
{
	if (limit <= 0)
		limit = 0x7fffffff;
	curfile->llimit = limit;
	if (curfile->lcount >= curfile->llimit) {
D 3
		ERROR(ELLIMIT, curfile->pfname);
E 3
I 3
		ERROR("%s: Line limit exceeded\n", curfile->pfname);
E 3
		return;
	}
}
E 1
