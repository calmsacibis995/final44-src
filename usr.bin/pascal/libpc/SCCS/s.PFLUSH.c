h34995
s 00002/00002/00025
d D 8.1 93/06/06 15:18:01 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00018
d D 1.3 90/04/09 18:27:05 bostic 3 2
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00004/00005/00016
d D 1.2 83/01/21 18:58:15 mckusick 2 1
c fix for prematurely removing temp files
e
s 00021/00000/00000
d D 1.1 80/10/30 00:34:24 mckusick 1 0
c date and time created 80/10/30 00:34:24 by mckusick
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

/*
 * insure that a usable image is in the buffer window
 */
PFLUSH()
{
	register struct iorec	*next;

D 2
	next = _fchain.fchain;
	while(next != FILNIL) {
		if ((next->funit & (FDEF | FREAD)) == 0) {
E 2
I 2
	for (next = _fchain.fchain; next != FILNIL; next = next->fchain) {
		if ((next->funit & (FDEF | FREAD)) != 0)
			continue;
		if (next->fbuf != 0)
E 2
			fflush(next->fbuf);
D 2
		}
		next = next->fchain;
E 2
	}
}
E 1
