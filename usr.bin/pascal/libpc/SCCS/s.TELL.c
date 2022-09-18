h41937
s 00002/00002/00028
d D 8.1 93/06/06 15:20:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00021
d D 1.4 90/04/09 18:27:58 bostic 4 3
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00007/00005/00016
d D 1.3 81/06/17 00:39:46 mckusic 3 2
c change to allow any type of files
e
s 00001/00000/00020
d D 1.2 81/03/07 16:04:37 mckusic 2 1
c merge in onyx changes
e
s 00020/00000/00000
d D 1.1 81/01/16 19:34:08 mckusick 1 0
c date and time created 81/01/16 19:34:08 by mckusick
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

/*
 * Find current location
 */
I 2
D 3
long
E 3
I 3
struct seekptr
E 3
E 2
TELL(curfile)

	register struct iorec	*curfile;
{
D 3
	long loc;
E 3
I 3
	struct seekptr loc;
E 3

D 3
	loc = ftell(curfile);
	if ((curfile->funit | SYNC) == 0)
		loc += 1;
E 3
I 3
	if ((curfile->funit & FREAD) && (curfile->funit & SYNC) == 0) {
		fseek(curfile->fbuf, -curfile->fsize, 1);
		curfile->funit |= SYNC;
	}
	loc.cnt = ftell(curfile->fbuf);
E 3
	return loc;
}
E 1
