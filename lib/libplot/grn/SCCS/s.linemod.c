h54600
s 00002/00002/00036
d D 8.1 93/06/04 17:41:28 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00032
d D 6.2 91/04/22 15:22:38 bostic 2 1
c new copyright; att/bsd/shared
e
s 00038/00000/00000
d D 6.1 86/08/29 15:06:24 sklower 1 0
c date and time created 86/08/29 15:06:24 by sklower
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 3
 * Copyright (c) 1980, 1986 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint

E 2
I 2
#endif /* not lint */
E 2

#include "grnplot.h"

/*---------------------------------------------------------
 *	Linemod sets the current line drawing style.
 *
 *	Results:	None.
 *
 *	Side Effects:
 *	The line style is set based on string s which
 *	must be one of "dotted", "solid", "longdashed", "shortdashed",
 *	or "dotdashed".  If s isn't recognized, then "solid" is used.
 *---------------------------------------------------------
 */
linemod(s)
char *s;
{
    endvector();
    if (strcmp(s, "dotted") == 0)
	linestyle = 1;
    else if (strcmp(s, "longdashed") == 0)
	linestyle = 4;
    else if (strcmp(s, "shortdashed") == 0)
	linestyle = 4;
    else if (strcmp(s, "dotdashed") == 0)
	linestyle = 2;
    else linestyle = DEFAULTLINE;
}
E 1
