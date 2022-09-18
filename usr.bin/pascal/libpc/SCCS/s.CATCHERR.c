h28009
s 00002/00002/00020
d D 8.1 93/06/06 15:15:01 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00013
d D 1.3 90/04/09 18:26:04 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00002/00002/00013
d D 1.2 81/04/01 22:57:22 mckusic 2 1
c fix dynamic display save
e
s 00015/00000/00000
d D 1.1 81/01/13 13:31:50 mckusick 1 0
c date and time created 81/01/13 13:31:50 by mckusick
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

CATCHERR(err, todo)
	long err;		/* error to be caught */
	struct formalrtn todo;	/* procedure to call to catch error */
{
D 2
	if (todo.cbn == 1)
		_entry[err].entryaddr = todo.entryaddr;
E 2
I 2
	if (todo.fbn == 1)
		_entry[err].fentryaddr = todo.fentryaddr;
E 2
	else
		fputs("procedure not at level 1", stderr);
}
E 1
