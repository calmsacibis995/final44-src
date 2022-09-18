h32901
s 00002/00002/00121
d D 8.1 93/06/06 16:03:21 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00117
d D 5.2 91/04/16 15:56:37 bostic 5 4
c new copyright; att/bsd/shared
e
s 00010/00002/00112
d D 5.1 85/06/05 15:56:11 dist 4 3
c Add copyright
e
s 00000/00000/00114
d D 2.1 84/02/08 20:22:44 aoki 3 2
c synchronizing at version 2
e
s 00001/00000/00113
d D 1.2 83/05/11 21:49:02 peter 2 1
c since input buffer is variable sized, people who include yy.h need whoami.h.
e
s 00113/00000/00000
d D 1.1 81/03/02 21:29:31 peter 1 0
c date and time created 81/03/02 21:29:31 by peter
e
u
U
t
T
I 1
D 4
static	char *sccsid = "%W% (Berkeley) %G%";
/* Copyright (c) 1979 Regents of the University of California */
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
 * pi - Pascal interpreter code translator
 *
 * Charles Haley, Bill Joy UCB
 * Version 1.2 January 1979
 *
 *
 * pxp - Pascal execution profiler
 *
 * Bill Joy UCB
 * Version 1.2 January 1979
 */

I 2
#include "whoami.h"
E 2
#include "0.h"
#include "yy.h"

/*
 * Yerror prints an error
 * message and then returns
 * NIL for the tree if needed.
 * The error is flagged on the
 * current line which is printed
 * if the listing is turned off.
#ifdef PXP
 *
 * As is obvious from the fooling around
 * with fout below, the Pascal system should
 * be changed to use the new library "lS".
#endif
 */
yerror(s, a1, a2, a3, a4, a5)
	char *s;
{
#ifdef PI
	char buf[256];
#endif
	register int i, j;
	static yySerrs;
#ifdef PXP
/*
	int ofout;
*/
#endif

	if (errpfx == 'w' && opt('w') != 0)
		return;
#ifdef PXP
/*
	flush();
	ofout = fout[0];
	fout[0] = errout;
*/
#endif
	yyResume = 0;
#ifdef PI
	geterr(s, buf);
	s = buf;
#endif
	yysync();
	putc(errpfx, stderr);
	putc(' ', stderr);
	for (i = 3; i < yyecol; i++)
		putc('-', stderr);
	fprintf(stderr, "^--- ");
/*
	if (yyecol > 60)
		printf("\n\t");
*/
	fprintf(stderr, s, a1, a2, a3, a4, a5);
	putc('\n', stderr);
	if (errpfx == 'E')
#ifdef PI
		eflg++, cgenflg++;
#endif
#ifdef PXP
		eflg++;
#endif
	errpfx = 'E';
	yySerrs++;
	if (yySerrs >= MAXSYNERR) {
		yySerrs = 0;
		yerror("Too many syntax errors - QUIT");
		pexit(ERRS);
	}
#ifdef PXP
/*
	flush();
	fout[0] = ofout;
*/
	return (0);
#endif
}

/*
 * A bracketing error message
 */
brerror(where, what)
	int where;
	char *what;
{

	if (where == 0) {
		line = yyeline;
		setpfx(' ');
		error("End matched %s on line %d", what, where);
		return;
	}
	if (where < 0)
		where = -where;
	yerror("Inserted keyword end matching %s on line %d", what, where);
}
E 1
