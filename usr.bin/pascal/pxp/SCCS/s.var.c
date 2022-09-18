h24188
s 00002/00002/00078
d D 8.1 93/06/06 16:03:03 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00074
d D 5.2 91/04/16 15:56:33 bostic 5 4
c new copyright; att/bsd/shared
e
s 00010/00003/00069
d D 5.1 85/06/05 15:54:14 dist 4 3
c Add copyright
e
s 00000/00000/00072
d D 2.1 84/02/08 20:22:23 aoki 3 2
c synchronizing at version 2
e
s 00001/00001/00071
d D 1.2 81/03/07 17:36:17 mckusic 2 1
c merge in onyx changes
e
s 00072/00000/00000
d D 1.1 81/03/02 21:29:14 peter 1 0
c date and time created 81/03/02 21:29:14 by peter
e
u
U
t
T
I 1
D 4
static	char *sccsid = "%W% (Berkeley) %G%";
/* Copyright (c) 1979 Regents of the University of California */
#
E 4
I 4
D 5
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
/*-
D 6
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

E 4
/*
 * pxp - Pascal execution profiler
 *
 * Bill Joy UCB
 * Version 1.2 January 1979
 */

#include "0.h"
#include "tree.h"

D 2
STATIC	int varcnt -1;
E 2
I 2
STATIC	int varcnt = -1;
E 2
/*
 * Var declaration part
 */
varbeg(l, vline)
	int l, vline;
{

	line = l;
	if (nodecl)
		printoff();
	puthedr();
	putcm();
	ppnl();
	indent();
	ppkw("var");
	ppgoin(DECL);
	varcnt = 0;
	setline(vline);
}

var(vline, vidl, vtype)
	int vline;
	register int *vidl;
	int *vtype;
{

	if (varcnt)
		putcm();
	setline(vline);
	ppitem();
	if (vidl != NIL)
		for (;;) {
			ppid(vidl[1]);
			vidl = vidl[2];
			if (vidl == NIL)
				break;
			ppsep(", ");
		}
	else
		ppid("{identifier list}");
	ppsep(":");
	gtype(vtype);
	ppsep(";");
	setinfo(vline);
	putcml();
	varcnt++;
}

varend()
{

	if (varcnt == -1)
		return;
	if (varcnt == 0)
		ppid("{variable decls}");
	ppgoout(DECL);
	varcnt = -1;
}
E 1
