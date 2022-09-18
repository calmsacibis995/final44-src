h10208
s 00002/00002/00011
d D 8.1 93/05/31 16:04:07 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00010
d D 5.4 90/04/30 21:24:19 bostic 4 3
c Berkeley headers, SCCS id's
e
s 00002/00001/00021
d D 5.3 90/04/30 21:09:48 bostic 3 2
c move score to /var/games, games to /usr/share/games
e
s 00001/00001/00021
d D 5.2 90/04/30 20:52:22 bostic 2 1
c move to /usr/share/games
e
s 00022/00000/00000
d D 5.1 89/05/11 14:40:28 bostic 1 0
c file reorg, pathnames.h, paths.h
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 4
I 4
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
E 4
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

#include <paths.h>

D 2
#define	_PATH_SPECIAL_DIR	"/usr/games/lib/atc/"
E 2
I 2
D 3
#define	_PATH_SPECIAL_DIR	"/usr/share/games/atc/"
E 3
I 3
#define	_PATH_GAMES	"/usr/share/games/atc/"
#define	_PATH_SCORE	"/var/games/atc_score"
E 3
E 2
E 1
