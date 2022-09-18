h53162
s 00002/00002/00029
d D 8.1 93/06/06 15:18:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00022
d D 1.4 90/04/09 18:27:19 bostic 4 3
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00002/00024
d D 1.3 89/01/09 15:39:08 mckusick 3 2
c update from John Gilmore for gcc
e
s 00003/00003/00023
d D 1.2 81/06/10 00:43:54 mckusic 2 1
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00026/00000/00000
d D 1.1 80/10/30 00:34:42 mckusick 1 0
c date and time created 80/10/30 00:34:42 by mckusick
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

char
READC(curfile)

	register struct iorec	*curfile;
{
	char			data;

	if (curfile->funit & FWRITE) {
D 2
		ERROR(EREADIT, curfile->pfname);
E 2
I 2
		ERROR("%s: Attempt to read, but open for writing\n",
			curfile->pfname);
E 2
D 3
		return;
E 3
	}
	IOSYNC(curfile);
	if (curfile->funit & EOFF) {
D 2
		ERROR(EPASTEOF, curfile->pfname);
E 2
I 2
		ERROR("%s: Tried to read past end of file\n", curfile->pfname);
E 2
D 3
		return;
E 3
	}
	curfile->funit |= SYNC;
	return *curfile->fileptr;
}
E 1
