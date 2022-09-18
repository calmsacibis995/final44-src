h04995
s 00002/00002/00078
d D 8.1 93/06/06 16:02:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00074
d D 5.2 91/04/16 15:56:22 bostic 4 3
c new copyright; att/bsd/shared
e
s 00010/00003/00069
d D 5.1 85/06/05 15:47:37 dist 3 2
c Add copyright
e
s 00000/00000/00072
d D 2.1 84/02/08 20:21:45 aoki 2 1
c synchronizing at version 2
e
s 00072/00000/00000
d D 1.1 81/03/02 21:28:17 peter 1 0
c date and time created 81/03/02 21:28:17 by peter
e
u
U
t
T
I 1
D 3
static	char *sccsid = "%W% (Berkeley) %G%";
/* Copyright (c) 1979 Regents of the University of California */
#
E 3
I 3
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

E 3
/*
 * pxp - Pascal execution profiler
 *
 * Bill Joy UCB
 * Version 1.2 January 1979
 */

#include "0.h"

/*
 * Label declaration part
 */
label(r, l)
	int *r, l;
{
	register *ll;

	if (nodecl)
		printoff();
	puthedr();
	setline(l);
	ppnl();
	indent();
	ppkw("label");
	ppgoin(DECL);
	ppnl();
	indent();
	ppbra(NIL);
	ll = r;
	if (ll != NIL)
		for (;;) {
			pplab(ll[1]);
			ll = ll[2];
			if (ll == NIL)
				break;
			ppsep(", ");
		}
	else
		ppid("{label list}");
	ppket(";");
	putcml();
	ppgoout(DECL);
}

/*
 * Goto statement
 */
gotoop(s)
	char *s;
{

	gocnt++;
	ppkw("goto");
	ppspac();
	pplab(s);
}

/*
 * A label on a statement
 */
labeled(s)
	char *s;
{

	linopr();
	indentlab();
	pplab(s);
	ppsep(":");
}
E 1
