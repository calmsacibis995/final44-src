h37571
s 00002/00002/00020
d D 8.1 93/06/06 15:16:52 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00013
d D 1.4 90/04/09 18:26:38 bostic 4 3
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00003/00001/00012
d D 1.3 82/11/12 18:58:29 mckusick 3 2
c make error message global var, so routine can be inline expanded
e
s 00001/00002/00012
d D 1.2 81/06/10 00:38:19 mckusic 2 1
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00014/00000/00000
d D 1.1 80/10/30 00:33:38 mckusick 1 0
c date and time created 80/10/30 00:33:38 by mckusick
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
D 2
#include "h01errs.h"
E 2

I 3
char ELINO[] = "Statement count limit of %D exceeded\n";

E 3
LINO()
{
	if (++_stcnt >= _stlim) {
D 2
		ERROR(ESTLIM, _stcnt);
E 2
I 2
D 3
		ERROR("Statement count limit of %D exceeded\n", _stcnt);
E 3
I 3
		ERROR(ELINO, _stcnt);
E 3
E 2
		return;
	}
}
E 1
