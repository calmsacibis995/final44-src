h14825
s 00002/00002/00023
d D 8.1 93/06/06 15:16:19 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00016
d D 1.5 90/04/09 18:26:26 bostic 5 4
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00002/00002/00016
d D 1.4 82/11/12 14:48:37 mckusick 4 3
c make size last arg to blkcpy and blkclr to be compatable with bcopy and bcmp
e
s 00004/00004/00014
d D 1.3 81/04/01 22:16:15 mckusic 3 2
c mods for dynamically allocating display save area before formal calls
e
s 00002/00007/00016
d D 1.2 81/03/07 15:56:25 mckusic 2 1
c merge in onyx changes
e
s 00023/00000/00000
d D 1.1 80/10/30 00:33:20 mckusick 1 0
c date and time created 80/10/30 00:33:20 by mckusick
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

struct formalrtn *
FSAV(entryaddr, cbn, frtn) 
	long (*entryaddr)();
	long cbn;
	register struct formalrtn *frtn;
{
D 2
	register struct display *dp;
	register struct display *ds;
	struct display *limit;

E 2
D 3
	frtn->entryaddr = entryaddr;
	frtn->cbn = cbn;
D 2
	limit = &frtn->disp[frtn->cbn];
	for (dp = &_disply[1], ds = &frtn->disp[0]; ds < limit; )
		*ds++ = *dp++;
E 2
I 2
	blkcpy(frtn->cbn * sizeof(struct display),
	       &_disply[1], &frtn->disp[0]);
E 3
I 3
	frtn->fentryaddr = entryaddr;
	frtn->fbn = cbn;
D 4
	blkcpy(frtn->fbn * sizeof(struct display),
	       &_disply[1], &frtn->fdisp[0]);
E 4
I 4
	blkcpy(&_disply[1], &frtn->fdisp[0],
		frtn->fbn * sizeof(struct display));
E 4
E 3
E 2
	return frtn;
}
E 1
