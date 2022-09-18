h36481
s 00002/00002/00026
d D 8.1 93/06/06 15:14:22 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00019
d D 1.3 90/04/09 18:25:53 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00002/00020
d D 1.2 81/06/10 00:45:29 mckusic 2 1
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00022/00000/00000
d D 1.1 80/10/31 14:45:07 mckusick 1 0
c date and time created 80/10/31 14:45:07 by mckusick
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

APPEND(filep)

	register struct iorec	*filep;
{
	filep = GETNAME (filep, 0, 0, 0);
	filep->fbuf = fopen(filep->fname, "a");
	if (filep->fbuf == NULL) {
D 2
		ERROR(EOPEN, filep->pfname);
E 2
I 2
		PERROR("Could not open ", filep->pfname);
E 2
		return;
	}
	filep->funit |= (EOFF | FWRITE);
	if (filep->fblk > PREDEF) {
		setbuf(filep->fbuf, &filep->buf[0]);
	}
}
E 1
