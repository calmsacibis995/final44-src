h30900
s 00002/00002/00020
d D 8.1 93/06/04 17:43:40 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00016
d D 5.3 91/04/22 15:52:54 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00000/00020
d D 5.2 91/02/24 15:45:45 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00007/00001/00013
d D 5.1 85/05/07 12:14:36 dist 2 1
c Add copyright notice
e
s 00014/00000/00000
d D 4.1 83/11/10 14:42:37 ralph 1 0
c date and time created 83/11/10 14:42:37 by ralph
e
u
U
t
T
I 2
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
E 4
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 2

#include <signal.h>
#include "hp7221.h"

I 3
void
E 3
closepl()
{
	/* receive interupts */
	signal(SIGINT, SIG_IGN);
	printf( "v@}" );			/* Put pen away. */
	fflush( stdout );
}
E 1
