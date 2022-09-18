h43933
s 00002/00002/00023
d D 8.1 93/06/04 17:22:23 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00019
d D 5.4 91/04/22 14:57:09 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00000/00024
d D 5.3 91/02/24 15:42:47 bostic 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00009/00002/00015
d D 5.2 85/04/30 16:15:01 dist 3 2
c add copyright
e
s 00001/00001/00016
d D 5.1 85/04/30 15:43:34 dist 2 1
c add copyright
e
s 00017/00000/00000
d D 4.1 83/11/10 11:00:54 ralph 1 0
c date and time created 83/11/10 11:00:54 by ralph
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
static char sccsid[] = "@(#)close.c	4.1 (Berkeley) 11/10/83";
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

#include <signal.h>
#include "bg.h"

I 4
void
E 4
closepl()
{
	/* recieve interupts */
	signal(SIGINT, SIG_IGN);

	/* exit graphics mode */
	putchar( ESC );
	printf("[H");
	exit(0);
}
E 1
