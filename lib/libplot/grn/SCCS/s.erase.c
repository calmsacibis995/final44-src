h41098
s 00002/00002/00032
d D 8.1 93/06/04 17:41:14 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00028
d D 6.2 91/04/22 15:22:35 bostic 2 1
c new copyright; att/bsd/shared
e
s 00034/00000/00000
d D 6.1 86/08/29 15:06:21 sklower 1 0
c date and time created 86/08/29 15:06:21 by sklower
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
 *	This routine erases the screen.
 *
 *	Results:	None.
 *	Side Effects:	A new grn file is begun
 *	but: it is concatentated to the old one.
 *---------------------------------------------------------
 */
erase()
{
	if (ingrnfile)
	{
		closepl();
		fputs("multiple grn files in output must be separated by hand!\n",stderr);
	}
    printf("sungremlinfile\n0.00 0.00\n");
    ingrnfile = 1;
    invector = 0;
    scale = 1;
    curx = cury = xbot = ybot = 0;
}
E 1
