h16468
s 00002/00002/00026
d D 8.1 93/05/31 17:54:04 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00025
d D 5.2 92/12/23 10:16:45 bostic 2 1
c update copyright notice with contrib notice
e
s 00025/00000/00000
d D 5.1 92/12/22 11:50:39 bostic 1 0
c date and time created 92/12/22 11:50:39 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Chris Torek and Darren F. Provine.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Tetris scores.
 */
struct highscore {
	char	hs_name[20];	/* login name */
	int	hs_score;	/* raw score */
	int	hs_level;	/* play level */
	time_t	hs_time;	/* time at game end */
};

#define MAXHISCORES	80
#define MAXSCORES	9	/* maximum high score entries per person */
#define	EXPIRATION	(5L * 365 * 24 * 60 * 60)

void	savescore __P((int));
void	showscores __P((int));
E 1
