h55280
s 00002/00002/00034
d D 8.1 93/05/31 16:03:42 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00035
d D 5.4 90/10/30 08:13:59 bostic 4 3
c ANSI C snarfed "clock"; change to "clck"
e
s 00012/00000/00024
d D 5.3 90/04/30 21:24:04 bostic 3 2
c Berkeley headers, SCCS id's
e
s 00001/00001/00023
d D 5.2 90/04/30 21:09:43 bostic 2 1
c move score to /var/games, games to /usr/share/games
e
s 00024/00000/00000
d D 5.1 90/04/30 20:59:06 bostic 1 0
c date and time created 90/04/30 20:59:06 by bostic
e
u
U
t
T
I 3
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Ed James.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
I 1
/*
 * Copyright (c) 1987 by Ed James, UC Berkeley.  All rights reserved.
 *
 * Copy permission is hereby granted provided that this notice is
 * retained on all partial or complete copies.
 *
 * For more info on this and all of my stuff, mail edjames@berkeley.edu.
 */

D 2
extern char		GAMES[], LOG[], *file;
E 2
I 2
extern char		GAMES[], *file;
E 2

D 4
extern int		clock, safe_planes, start_time, test_mode;
E 4
I 4
extern int		clck, safe_planes, start_time, test_mode;
E 4

extern FILE		*filein, *fileout;

extern C_SCREEN		screen, *sp;

extern LIST		air, ground;

extern struct sgttyb	tty_start, tty_new;

extern DISPLACEMENT	displacement[MAXDIR];

extern PLANE		*findplane(), *newplane();
E 1
