h41818
s 00001/00000/00037
d D 8.2 94/01/12 09:39:08 bostic 5 4
c lint
e
s 00002/00002/00035
d D 8.1 93/06/10 21:40:40 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00034
d D 7.3 92/10/11 09:42:33 bostic 3 2
c make kernel includes standard
e
s 00003/00003/00034
d D 7.2 90/12/16 16:36:04 bostic 2 1
c kernel reorg
e
s 00037/00000/00000
d D 7.1 90/05/08 18:09:07 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef NOBADSECT
D 2
#include "param.h"
#include "buf.h"
#include "dkbad.h"
E 2
I 2
D 3
#include "sys/param.h"
#include "sys/buf.h"
#include "sys/dkbad.h"
E 3
I 3
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/dkbad.h>
E 3
E 2

/*
 * Search the bad sector table looking for
 * the specified sector.  Return index if found.
 * Return -1 if not found.
 */

isbad(bt, cyl, trk, sec)
	register struct dkbad *bt;
I 5
	int cyl, trk, sec;
E 5
{
	register int i;
	register long blk, bblk;

	blk = ((long)cyl << 16) + (trk << 8) + sec;
	for (i = 0; i < 126; i++) {
		bblk = ((long)bt->bt_bad[i].bt_cyl << 16) + bt->bt_bad[i].bt_trksec;
		if (blk == bblk)
			return (i);
		if (blk < bblk || bblk < 0)
			break;
	}
	return (-1);
}
#endif
E 1
