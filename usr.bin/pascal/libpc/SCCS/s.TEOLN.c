h06490
s 00002/00002/00036
d D 8.1 93/06/06 15:20:06 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00029
d D 1.5 90/04/09 18:28:00 bostic 5 4
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00012/00001/00019
d D 1.4 82/08/16 19:23:00 mckusick 4 3
c check that file has been reset or rewritten
e
s 00001/00002/00019
d D 1.3 81/06/10 00:44:42 mckusic 3 2
c move the text of error messages from ERROR to the functions
c which generate them.
e
s 00001/00000/00020
d D 1.2 81/03/07 16:05:02 mckusic 2 1
c merge in onyx changes
e
s 00020/00000/00000
d D 1.1 80/10/30 00:36:03 mckusick 1 0
c date and time created 80/10/30 00:36:03 by mckusick
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

I 2
bool
E 2
TEOLN(filep)

	register struct iorec	*filep;
{
D 4
	if (filep->fblk >= MAXFILES || _actfile[filep->fblk] != filep) {
E 4
I 4
	if (filep->fblk >= MAXFILES || _actfile[filep->fblk] != filep ||
	    (filep->funit & FDEF)) {
E 4
D 3
		ERROR(ENOFILE, 0);
E 3
I 3
		ERROR("Reference to an inactive file\n", 0);
E 3
		return;
	}
I 4
	if (filep->funit & FWRITE) {
		ERROR("%s: eoln is undefined on files open for writing\n",
		    filep->pfname);
		return;
	}
E 4
	IOSYNC(filep);
I 4
	if (filep->funit & EOFF) {
		ERROR("%s: eoln is undefined when eof is true\n",
		    filep->pfname);
		return;
	}
E 4
	if (filep->funit & EOLN)
		return TRUE;
	return FALSE;
}
E 1
