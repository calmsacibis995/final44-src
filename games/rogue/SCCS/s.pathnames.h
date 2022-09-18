h51060
s 00002/00002/00008
d D 8.1 93/05/31 17:47:24 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00010
d D 5.2 92/07/29 12:44:56 bostic 2 1
c use flock, not file creation to lock
e
s 00012/00000/00000
d D 5.1 90/06/01 13:15:30 bostic 1 0
c date and time created 90/06/01 13:15:30 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	_PATH_SCOREFILE	"/var/games/rogue.scores"
D 2
#define	_PATH_LOCKFILE	"/var/games/rogue.lock"

E 2
E 1
