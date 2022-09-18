h57395
s 00002/00002/00033
d D 8.1 93/06/04 17:22:52 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00029
d D 5.4 91/04/22 14:57:14 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00034
d D 5.3 91/02/24 15:42:51 bostic 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00009/00002/00026
d D 5.2 85/04/30 16:15:31 dist 3 2
c add copyright
e
s 00001/00001/00027
d D 5.1 85/04/30 15:44:01 dist 2 1
c add copyright
e
s 00028/00000/00000
d D 4.1 83/11/10 11:02:44 ralph 1 0
c date and time created 83/11/10 11:02:44 by ralph
e
u
U
t
T
I 3
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
 * %sccs.include.proprietary.c%
E 5
 */

E 3
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %G%";
E 2
I 2
D 3
static char sccsid[] = "@(#)open.c	4.1 (Berkeley) 11/10/83";
E 2
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint

E 5
I 5
#endif /* not lint */
E 5
E 3

/*
 * Displays plot files on a BBN bitgraph terminal.
 */

#include <signal.h>
#include "bg.h"

int currentx = 0;
int currenty = 0;
double lowx = 0.0;
double lowy = 0.0;
double scale = 1.0;

openpl()
{
D 4
	int closepl();
E 4
I 4
	void closepl();
E 4

	/* catch interupts */
	signal(SIGINT, closepl);
	currentx = 0;
	currenty = 0;

	space(0, 0, XMAX, YMAX);
}
E 1
