h60078
s 00002/00002/00052
d D 8.1 93/06/04 17:41:46 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00048
d D 6.2 91/04/22 15:22:41 bostic 2 1
c new copyright; att/bsd/shared
e
s 00054/00000/00000
d D 6.1 86/08/29 15:06:28 sklower 1 0
c date and time created 86/08/29 15:06:28 by sklower
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
 *	This local routine outputs an x-y coordinate pair in the standard
 *	format required by the grn file.
 *
 *	Results:	None.
 *	
 *	Side Effects:
 *
 *	Errors:		None.
 *---------------------------------------------------------
 */
outxy(x, y)
int x, y;			/* The coordinates to be output.  Note:
				 * these are world coordinates, not screen
				 * ones.  We scale in this routine.
				 */
{
    printf("%.2f %.2f\n", (x - xbot)*scale,(y - ybot)*scale);
}

outcurxy()
{
	outxy(curx,cury);
}

startvector()
{
	if (!ingrnfile) erase();
	if (invector) return;
	invector = 1;
	printf("VECTOR\n");
	outcurxy();
}

endvector()
{
	if (!invector) return;
	invector = 0;
	printf("*\n%d 0\n0\n",linestyle);
}
E 1
