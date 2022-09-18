h01307
s 00002/00002/00020
d D 8.1 93/06/06 15:18:36 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00013
d D 1.5 90/04/09 18:27:22 bostic 6 5
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00000/00001/00015
d D 1.4 81/06/10 00:44:01 mckusic 5 4
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00004/00009/00012
d D 1.3 81/01/26 12:36:46 mckusic 4 2
c append a newline to unterminated last lines when reading text files
e
s 00006/00001/00020
d R 1.3 81/01/24 17:50:07 mckusic 3 2
c check for EOF
e
s 00000/00004/00021
d D 1.2 81/01/24 16:38:53 mckusic 2 1
c prevent error when ``readln'' used on partial last line in file
e
s 00025/00000/00000
d D 1.1 80/10/30 00:34:46 mckusick 1 0
c date and time created 80/10/30 00:34:46 by mckusick
e
u
U
t
T
I 1
D 6
/* Copyright (c) 1979 Regents of the University of California */
E 6
I 6
/*-
D 7
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */
E 6

D 6
static char sccsid[] = "%Z%%M% %I% %G%";
E 6
I 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

#include "h00vars.h"
D 5
#include "h01errs.h"
E 5

READLN(curfile)

	register struct iorec	*curfile;
{
D 4
	if (curfile->funit & FWRITE) {
		ERROR(EREADIT, curfile->pfname);
		return;
	}
	IOSYNC(curfile);
D 2
	if (curfile->funit & EOFF) {
		ERROR(EPASTEOF, curfile->pfname);
		return;
	}
E 2
	if ((curfile->funit & EOLN) == 0) {
		fscanf(curfile->fbuf, "%*[^\n]%*c");
	}
	curfile->funit |= SYNC;
E 4
I 4
	do	{
		IOSYNC(curfile);
		curfile->funit |= SYNC;
	} while ((curfile->funit & EOLN) == 0);
E 4
}
E 1
