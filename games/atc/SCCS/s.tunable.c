h04127
s 00002/00002/00028
d D 8.1 93/05/31 16:04:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00000/00016
d D 5.4 90/04/30 21:24:21 bostic 4 3
c Berkeley headers, SCCS id's
e
s 00000/00010/00016
d D 5.3 90/04/30 21:09:49 bostic 3 2
c move score to /var/games, games to /usr/share/games
e
s 00003/00001/00023
d D 5.2 89/05/11 13:48:19 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00024/00000/00000
d D 5.1 89/05/04 19:14:31 bostic 1 0
c date and time created 89/05/04 19:14:31 by bostic
e
u
U
t
T
I 4
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

E 4
I 1
/*
 * Copyright (c) 1987 by Ed James, UC Berkeley.  All rights reserved.
 *
 * Copy permission is hereby granted provided that this notice is
 * retained on all partial or complete copies.
 *
 * For more info on this and all of my stuff, mail edjames@berkeley.edu.
 */
I 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

I 2
D 3
#include "pathnames.h"

E 2
/*
 * SPECIAL_DIR - Where the special files are kept.
 * Change this to whatever you want.  Be sure to have to path end 
 * with a '/', like "/usr/games/lib/atc/".
 */

D 2
char	SPECIAL_DIR[] =		DEST;
E 2
I 2
char	SPECIAL_DIR[] = _PATH_SPECIAL_DIR;
E 2

E 3
/*
 * NUM_SCORES - Number of scores that are kept track of.
 * Keep this greater than 0, but less than 100.
 * 4 lines are printed above the score, one below + your prompt, so
 * to prevent scrolling: 6 + NUM_SCORES <= 24 (lines on an average terminal).
 */
int	NUM_SCORES =		18;
E 1
