h64498
s 00002/00002/00039
d D 8.1 93/06/11 15:34:37 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00038
d D 5.5 92/10/11 10:10:54 bostic 6 5
c make kernel includes standard
e
s 00001/00001/00040
d D 5.4 91/01/19 12:39:02 william 5 4
c change copyright notice
e
s 00003/00003/00038
d D 5.3 91/01/19 12:38:10 william 4 3
c kernel reorg.
e
s 00000/00000/00041
d D 5.2 91/01/15 12:21:59 bill 3 2
c reno changes
e
s 00012/00001/00029
d D 5.1 90/04/24 18:52:03 william 2 1
c 1st Berkeley Release
e
s 00030/00000/00000
d D 1.1 90/03/12 15:47:49 bill 1 0
c date and time created 90/03/12 15:47:49 by bill
e
u
U
t
T
I 1
D 2
/*	dkbad.c	1.1	86/01/05	*/
E 2
I 2
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 5
 * %sccs.include.noredist.c%
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

E 2

#ifndef NOBADSECT
D 4
#include "../h/param.h"
#include "../h/buf.h"
#include "../h/dkbad.h"
E 4
I 4
D 6
#include "sys/param.h"
#include "sys/buf.h"
#include "sys/dkbad.h"
E 6
I 6
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/dkbad.h>
E 6
E 4

/*
 * Search the bad sector table looking for
 * the specified sector.  Return index if found.
 * Return -1 if not found.
 */

isbad(bt, cyl, trk, sec)
	register struct dkbad *bt;
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
