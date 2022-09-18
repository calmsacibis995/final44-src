h03317
s 00002/00002/00056
d D 8.1 93/06/06 16:01:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00052
d D 5.2 91/04/16 15:56:17 bostic 4 3
c new copyright; att/bsd/shared
e
s 00010/00002/00047
d D 5.1 85/06/05 15:44:45 dist 3 2
c Add copyright
e
s 00000/00000/00049
d D 2.1 84/02/08 20:21:29 aoki 2 1
c synchronizing at version 2
e
s 00049/00000/00000
d D 1.1 81/03/02 21:27:56 peter 1 0
c date and time created 81/03/02 21:27:56 by peter
e
u
U
t
T
I 1
D 3
static	char *sccsid = "%W% (Berkeley) %G%";
/* Copyright (c) 1979 Regents of the University of California */
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
#
/*
 * pxp - Pascal execution profiler
 *
 * Bill Joy UCB
 * Version 1.2 January 1979
 */

#include "0.h"
#include "tree.h"

/*
 * Procedure or function call
 */
call(p, argv)
	register int *argv;
{
	register *al;

	ppid(p);
	if (argv != NIL) {
		ppbra("(("+1);	/* xaproposstrange */
		for (;;) {
			al = argv[1];
			if (al[0] == T_WEXP) {
				rvalue(al[1], NIL);
				if (al[2] != NIL) {
					ppsep(": ");
					rvalue(al[2], NIL);
				}
				if (al[3] == OCT || al[3] == HEX) {
					ppspac();
					ppkw(al[3] == OCT ? "oct" : "hex");
				} else if (al[3] != NIL) {
					ppsep(": ");
					rvalue(al[3], NIL);
				}
			} else
				rvalue(argv[1], NIL);
			argv = argv[2];
			if (argv == NIL)
				break;
			ppsep(", ");
		}
		ppket(")");
	}
}
E 1
