h00367
s 00002/00002/00027
d D 8.1 93/06/06 15:16:10 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00020
d D 1.5 90/04/09 18:26:24 bostic 5 4
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00002/00022
d D 1.4 89/01/09 15:38:39 mckusick 4 3
c update from John Gilmore for gcc
e
s 00002/00003/00022
d D 1.3 81/06/10 00:37:52 mckusic 3 2
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00000/00004/00025
d D 1.2 81/01/24 15:13:27 mckusic 2 1
c set file^ to blank on eof (for text files)
e
s 00029/00000/00000
d D 1.1 80/10/30 00:33:16 mckusick 1 0
c date and time created 80/10/30 00:33:16 by mckusick
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

char *
FNIL(curfile)

	register struct iorec	*curfile;
{
	if (curfile->fblk >= MAXFILES || _actfile[curfile->fblk] != curfile) {
D 3
		ERROR(ENOFILE, 0);
E 3
I 3
		ERROR("Reference to an inactive file\n", 0);
E 3
D 4
		return;
E 4
	}
	if (curfile->funit & FDEF) {
D 3
		ERROR(EREFINAF, curfile->pfname);
E 3
I 3
		ERROR("%s: Reference to an inactive file\n", curfile->pfname);
E 3
D 4
		return;
E 4
	}
	if (curfile->funit & FREAD) {
		IOSYNC(curfile);
D 2
		if (curfile->funit & EOFF) {
			ERROR(EPASTEOF, curfile->pfname);
			return;
		}
E 2
	}
	return curfile->fileptr;
}
E 1
