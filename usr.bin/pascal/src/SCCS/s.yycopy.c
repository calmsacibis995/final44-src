h08705
s 00002/00002/00026
d D 8.1 93/06/06 16:13:07 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00022
d D 5.2 91/04/16 16:05:08 bostic 7 6
c new copyright; att/bsd/shared
e
s 00007/00003/00020
d D 5.1 85/06/05 15:05:13 dist 6 5
c Add copyright
e
s 00000/00000/00023
d D 2.1 84/02/08 20:43:48 aoki 5 4
c synchronize to version 2
e
s 00000/00000/00023
d D 1.4 83/09/19 07:01:47 thien 4 3
c Restoring to unlinted version
e
s 00005/00002/00018
d D 1.3 83/08/19 05:03:57 thien 3 2
c The changes were made to allow successful linting
e
s 00001/00000/00019
d D 1.2 83/05/11 21:52:43 peter 2 1
c since input buffer is variable sized, includers of yy.h also include whoami.h.
e
s 00019/00000/00000
d D 1.1 80/08/27 19:56:56 peter 1 0
c date and time created 80/08/27 19:56:56 by peter
e
u
U
t
T
I 1
D 6
/* Copyright (c) 1979 Regents of the University of California */
E 6
I 6
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 8
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
E 7
 */
E 6

I 3
#ifndef lint
E 3
D 6
static	char sccsid[] = "%Z%%M% %I% %G%";
I 3
#endif
E 6
I 6
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 6
E 3

I 2
#include	"whoami.h"
E 2
#include	"0.h"
I 3
#include 	"tree_ty.h"		/* must be included for yy.h */
E 3
#include	"yy.h"

OYcopy ()
    {
D 3
	register int	*r0 = & OY;
	register int	*r1 = & Y;
E 3
I 3
	register int	*r0 = ((int *) & OY);
	register int	*r1 = ((int *) & Y);
E 3
	register int	r2 = ( sizeof ( struct yytok ) ) / ( sizeof ( int ) );

	do
	    {
		* r0 ++ = * r1 ++ ;
	    }
	    while ( -- r2 > 0 );
    }
E 1
