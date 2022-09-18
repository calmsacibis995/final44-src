h04773
s 00002/00002/00033
d D 8.1 93/06/06 15:20:22 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00026
d D 1.5 90/04/09 18:28:06 bostic 5 4
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00002/00000/00026
d D 1.4 83/10/28 17:22:25 mckusick 4 3
c semantic cleanup of UNSYNC()
e
s 00003/00003/00023
d D 1.3 81/06/10 00:44:53 mckusic 3 2
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00004/00000/00022
d D 1.2 81/01/24 17:46:41 mckusic 2 1
c check for EOF in READ4, READ8, and READE before attempting read
e
s 00022/00000/00000
d D 1.1 80/10/30 00:36:16 mckusick 1 0
c date and time created 80/10/30 00:36:16 by mckusick
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
D 3
#include "h01errs.h"
E 3

/*
 * push back last char read to prepare for formatted read
 */
UNSYNC(curfile)

	register struct iorec	*curfile;
{
	if (curfile->funit & FWRITE) {
D 3
		ERROR(EREADIT, curfile->pfname);
E 3
I 3
		ERROR("%s: Attempt to read, but open for writing\n",
			curfile->pfname);
E 3
		return;
	}
I 2
	if (curfile->funit & EOFF) {
D 3
		ERROR(EPASTEOF, curfile->pfname);
E 3
I 3
		ERROR("%s: Tried to read past end of file\n", curfile->pfname);
E 3
		return;
	}
E 2
	if ((curfile->funit & SYNC) == 0) {
		ungetc(*curfile->fileptr, curfile->fbuf);
	}
I 4
	curfile->funit &= ~EOLN;
	curfile->funit |= SYNC;
E 4
}
E 1
