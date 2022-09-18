h08639
s 00002/00002/00072
d D 8.1 93/06/06 16:02:17 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00068
d D 5.2 91/04/16 15:56:23 bostic 4 3
c new copyright; att/bsd/shared
e
s 00010/00003/00063
d D 5.1 85/06/05 15:47:59 dist 3 2
c Add copyright
e
s 00000/00000/00066
d D 2.1 84/02/08 20:21:56 aoki 2 1
c synchronizing at version 2
e
s 00066/00000/00000
d D 1.1 81/03/02 21:28:20 peter 1 0
c date and time created 81/03/02 21:28:20 by peter
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
#include "tree.h"

/*
 * A "variable"
 */
lvalue(r)
	register int *r;
{
	register *c, *co;

	ppid(r[2]);
	for (c = r[3]; c != NIL; c = c[2]) {
		co = c[1];
		if (co == NIL)
			continue;
		switch (co[0]) {
			case T_PTR:
				ppop("^");
				continue;
			case T_ARY:
				arycod(co[1]);
				continue;
			case T_FIELD:
				ppop(".");
				ppid(co[1]);
				continue;
			case T_ARGL:
				ppid("{unexpected argument list}");
				break;
			default:
				panic("lval2");
		}
	}
}

/*
 * Subscripting
 */
arycod(el)
	register int *el;
{

	ppbra("[");
	if (el != NIL)
		for (;;) {
			rvalue(el[1], NIL);
			el = el[2];
			if (el == NIL)
				break;
			ppsep(", ");
		}
	else
		rvalue(NIL, NIL);
	ppket("]");
}
E 1
