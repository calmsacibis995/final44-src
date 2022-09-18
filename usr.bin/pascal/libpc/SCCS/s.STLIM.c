h23406
s 00002/00002/00021
d D 8.1 93/06/06 15:19:43 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00014
d D 1.3 90/04/09 18:27:52 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00002/00015
d D 1.2 81/06/10 00:44:25 mckusic 2 1
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00017/00000/00000
d D 1.1 80/10/30 00:35:48 mckusick 1 0
c date and time created 80/10/30 00:35:48 by mckusick
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
D 2
#include "h01errs.h"
E 2

STLIM(limit)

	long	limit;
{
	if (_stcnt >= limit) {
D 2
		ERROR(ESTLIM, _stcnt);
E 2
I 2
		ERROR("Statement count limit of %D exceeded\n", _stcnt);
E 2
		return;
	}
	_stlim = limit;
}
E 1
