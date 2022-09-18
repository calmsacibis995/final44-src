h56160
s 00002/00002/00036
d D 8.1 93/06/04 17:20:07 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00029
d D 5.2 91/04/22 14:54:46 bostic 4 2
c new copyright; att/bsd/shared
e
s 00009/00002/00029
d R 5.2 85/04/30 16:06:06 dist 3 2
c add copyright
e
s 00001/00001/00030
d D 5.1 85/04/30 15:48:03 dist 2 1
c add copyright
e
s 00031/00000/00000
d D 4.1 83/11/11 15:12:33 ralph 1 0
c date and time created 83/11/11 15:12:33 by ralph
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 4
static char sccsid[] = "@(#)linemod.c	4.1 (Berkeley) 11/11/83";
E 2
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

#include "aed.h"

/*---------------------------------------------------------
 *	Linemod sets the current line drawing style.
 *
 *	Results:	None.
 *
 *	Side Effects:
 *	The AED line style is set based on string s which
 *	must be one of "dotted", "solid", "longdashed", "shortdashed",
 *	or "dotdashed".  If s isn't recognized, then "solid" is used.
 *---------------------------------------------------------
 */
linemod(s)
char *s;
{
    if (strcmp(s, "dotted") == 0)
	fputs("1AAFF", stdout);
    else if (strcmp(s, "longdashed") == 0)
	fputs("1F055", stdout);
    else if (strcmp(s, "shortdashed") == 0)
	fputs("1F0FF", stdout);
    else if (strcmp(s, "dotdashed") == 0)
	fputs("1E4FF", stdout);
    else fputs("1FFFF", stdout);
    (void) fflush(stdout);
}
E 1
