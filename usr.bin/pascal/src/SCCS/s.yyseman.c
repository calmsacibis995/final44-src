h25615
s 00002/00002/00042
d D 8.1 93/06/06 16:14:00 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00038
d D 5.2 91/04/16 16:05:20 bostic 6 5
c new copyright; att/bsd/shared
e
s 00007/00003/00036
d D 5.1 85/06/05 15:27:25 dist 5 4
c Add copyright
e
s 00000/00000/00039
d D 2.1 84/02/08 20:43:40 aoki 4 3
c synchronize to version 2
e
s 00000/00000/00039
d D 1.3 83/09/19 07:02:34 thien 3 2
c Restoring to unlinted version
e
s 00003/00000/00036
d D 1.2 83/08/19 05:05:27 thien 2 1
c The changes were made to allow successful linting
e
s 00036/00000/00000
d D 1.1 80/08/27 19:57:34 peter 1 0
c date and time created 80/08/27 19:57:34 by peter
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
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
E 6
 */
E 5

I 2
#ifndef lint
E 2
D 5
static	char sccsid[] = "%Z%%M% %I% %G%";
I 2
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 5
E 2

#include "whoami.h"
#include "0.h"
I 2
#include "tree_ty.h"	/* must be included for yy.h */
E 2
#include "yy.h"

/*
 * Assign semantics to a generated token
 *
 * Most terminals have a semantic value the current
 * input line.  If they are generated they are flagged
 * by having this number negated.
 *
 * The terminals which have true semantics such
 * as identifiers and strings are instead given
 * semantic value NIL here - we do not attempt
 * to do repair, e.g. by giving generated integers
 * the value 1, etc.
 */
nullsem(ch)
	int ch;
{

	switch (ch) {
		case YID:
		case YINT:
		case YNUMB:
		case YBINT:
		case YSTRING:
			return (NIL);
		default:
			return (-yyeline);
	}
}
E 1
