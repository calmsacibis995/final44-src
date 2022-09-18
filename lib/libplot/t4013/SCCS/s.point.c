h18123
s 00002/00002/00013
d D 8.1 93/06/07 20:39:28 bostic 5 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00013
d R 8.1 93/06/04 17:51:49 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00009
d D 5.2 91/04/22 16:03:42 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00001/00007
d D 5.1 85/06/07 08:27:58 dist 2 1
c Add copyright
e
s 00008/00000/00000
d D 1.1 85/01/02 20:10:45 jak 1 0
c date and time created 85/01/02 20:10:45 by jak
e
u
U
t
T
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 5
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
E 3
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
E 2

point(xi,yi){
	move(xi,yi);
	cont(xi,yi);
}
E 1
