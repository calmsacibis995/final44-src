h39099
s 00002/00002/00031
d D 8.1 93/06/04 17:41:22 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00027
d D 6.2 91/04/22 15:22:37 bostic 2 1
c new copyright; att/bsd/shared
e
s 00033/00000/00000
d D 6.1 86/08/29 15:06:22 sklower 1 0
c date and time created 86/08/29 15:06:22 by sklower
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
 *	This routine places a label starting at the current
 *	position.
 *
 *	Results:	None.
 *
 *	Side Effects:
 *	The string indicated by s starting at (curx, cury).
 *	The current position is NOT updated.
 *---------------------------------------------------------
 */
label(s)
char *s;
{
	if (!ingrnfile) erase();
	endvector();
	printf("BOTLEFT\n");
	outcurxy();
	printf("*\n%d %d\n%d %s\n",FONTSTYLE,FONTSIZE,strlen(s)-1,s);
}
E 1
