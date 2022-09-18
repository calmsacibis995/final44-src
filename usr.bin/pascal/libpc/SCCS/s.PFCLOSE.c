h16590
s 00002/00002/00046
d D 8.1 93/06/06 15:17:54 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00039
d D 1.4 90/04/09 18:27:03 bostic 4 3
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00004/00002/00037
d D 1.3 83/01/21 18:58:32 mckusick 3 2
c fix for prematurely removing temp files
e
s 00000/00002/00039
d D 1.2 82/08/29 21:34:18 mckusick 2 1
c remove diagnostic output
e
s 00041/00000/00000
d D 1.1 82/08/29 21:31:44 mckusick 1 0
c date and time created 82/08/29 21:31:44 by mckusick
e
u
U
t
T
I 1
D 4
/* Copyright (c) 1982 Regents of the University of California */
E 4
I 4
/*-
D 5
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */
E 4

D 4
static	char sccsid[] = "%W%	(Berkeley)	%G%";
E 4
I 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

/*
 * Close a Pascal file deallocating resources as appropriate.
 */

D 2
#include <stdio.h>
E 2
#include "h00vars.h"
#include "libpc.h"

struct iorec *
D 3
PFCLOSE(filep)
E 3
I 3
PFCLOSE(filep, lastuse)
E 3
	register struct iorec *filep;
I 3
	bool lastuse;
E 3
{
D 2
	fprintf(stderr, "Closing file %s\n", filep->pfname);
E 2
	if ((filep->funit & FDEF) == 0 && filep->fbuf != NULL) {
		/*
		 * Have a previous buffer, close associated file.
		 */
		if (filep->fblk > PREDEF) {
			fflush(filep->fbuf);
			setbuf(filep->fbuf, NULL);
		}
		fclose(filep->fbuf);
		if (ferror(filep->fbuf)) {
			ERROR("%s: Close failed\n", filep->pfname);
			return;
		}
		/*
		 * Temporary files are discarded.
		 */
D 3
		if ((filep->funit & TEMP) != 0 && unlink(filep->pfname)) {
E 3
I 3
		if ((filep->funit & TEMP) != 0 && lastuse &&
		    unlink(filep->pfname)) {
E 3
			PERROR("Could not remove ", filep->pfname);
			return;
		}
	}
	_actfile[filep->fblk] = FILNIL;
	return (filep->fchain);
}
E 1
