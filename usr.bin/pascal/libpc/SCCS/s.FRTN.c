h23210
s 00002/00002/00017
d D 8.1 93/06/06 15:16:15 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00010
d D 1.6 90/04/09 18:26:25 bostic 7 6
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00001/00011
d D 1.5 82/11/12 14:48:32 mckusick 6 4
c make size last arg to blkcpy and blkclr to be compatable with bcopy and bcmp
e
s 00003/00003/00009
d R 1.5 81/06/08 00:38:07 mckusic 5 4
c put display save area back into formal routine structure
e
s 00003/00003/00009
d D 1.4 81/04/01 22:15:56 mckusic 4 3
c mods for dynamically allocating display save area before formal calls
e
s 00002/00007/00010
d D 1.3 81/03/07 15:56:09 mckusic 3 2
c merge in onyx changes
e
s 00001/00003/00016
d D 1.2 81/03/02 14:12:50 peter 2 1
c FRTN is a procedure, not a function.
e
s 00019/00000/00000
d D 1.1 80/10/30 00:33:18 mckusick 1 0
c date and time created 80/10/30 00:33:18 by mckusick
e
u
U
t
T
I 1
D 7
/* Copyright (c) 1979 Regents of the University of California */
E 7
I 7
/*-
D 8
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 */
E 7

D 7
static char sccsid[] = "%Z%%M% %I% %G%";
E 7
I 7
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 7

#include "h00vars.h"

D 2
FRTN(frtn, result)
E 2
I 2
D 4
FRTN(frtn)
E 4
I 4
FRTN(frtn, save)
E 4
E 2
	register struct formalrtn *frtn;
I 4
	char *save;
E 4
D 2
	int result;
E 2
{
D 3
	register struct display *dp;
	register struct display *ds;
	struct display *limit;

	limit = &frtn->disp[2 * frtn->cbn];
	for (ds = &frtn->disp[frtn->cbn], dp = &_disply[1]; ds < limit; )
		*dp++ = *ds++;
E 3
I 3
D 4
	blkcpy(frtn->cbn * sizeof(struct display),
	       &frtn->disp[frtn->cbn], &_disply[1]);
E 4
I 4
D 6
	blkcpy(frtn->fbn * sizeof(struct display), save, &_disply[1]);
E 6
I 6
	blkcpy(save, &_disply[1], frtn->fbn * sizeof(struct display));
E 6
E 4
E 3
D 2
	return result;
E 2
}
E 1
