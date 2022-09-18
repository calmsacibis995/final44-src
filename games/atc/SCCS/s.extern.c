h62061
s 00002/00002/00047
d D 8.1 93/05/31 16:03:39 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00048
d D 5.4 90/10/30 08:13:57 bostic 4 3
c ANSI C snarfed "clock"; change to "clck"
e
s 00014/00000/00035
d D 5.3 90/04/30 21:24:03 bostic 3 2
c Berkeley headers, SCCS id's
e
s 00001/00002/00034
d D 5.2 90/04/30 21:09:41 bostic 2 1
c move score to /var/games, games to /usr/share/games
e
s 00036/00000/00000
d D 5.1 89/03/05 20:27:54 bostic 1 0
c date and time created 89/03/05 20:27:54 by bostic
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
I 3

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "include.h"

D 2
char		GAMES[] =	"Game_List",
		LOG[] =		"ATC_scores";
E 2
I 2
char		GAMES[] =	"Game_List";
E 2

D 4
int		clock, safe_planes, start_time, test_mode;
E 4
I 4
int		clck, safe_planes, start_time, test_mode;
E 4

char		*file;

FILE		*filein, *fileout;

C_SCREEN		screen, *sp = &screen;

LIST		air, ground;

struct sgttyb	tty_start, tty_new;

DISPLACEMENT	displacement[MAXDIR] = {
		{  0, -1 },
		{  1, -1 },
		{  1,  0 },
		{  1,  1 },
		{  0,  1 },
		{ -1,  1 },
		{ -1,  0 },
		{ -1, -1 }
};
E 1
