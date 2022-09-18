h52386
s 00002/00002/00124
d D 8.1 93/05/31 17:45:38 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00124
d D 5.5 91/02/28 14:28:30 bostic 5 4
c ANSI
e
s 00001/00011/00124
d D 5.4 90/06/01 13:15:07 bostic 4 3
c new copyright notice
e
s 00010/00005/00125
d D 5.3 88/06/18 20:04:45 bostic 3 2
c install approved copyright notice
e
s 00009/00003/00121
d D 5.2 88/03/09 11:18:42 bostic 2 1
c Written by Ken Arnold; add Berkeley specific copyright
e
s 00124/00000/00000
d D 5.1 85/05/30 18:35:11 mckusick 1 0
c date and time created 85/05/30 18:35:11 by mckusick
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1980 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

# include	"robots.h"
# include	<signal.h>

/*
 * move_robots:
 *	Move the robots around
 */
I 5
void
E 5
move_robots(was_sig)
bool	was_sig;
{
	register COORD	*rp;
	register int	y, x;
	register int	mindist, d;
	static COORD	newpos;

	if (Real_time)
		signal(SIGALRM, move_robots);
# ifdef DEBUG
	move(Min.y, Min.x);
	addch(inch());
	move(Max.y, Max.x);
	addch(inch());
# endif DEBUG
	for (rp = Robots; rp < &Robots[MAXROBOTS]; rp++) {
		if (rp->y < 0)
			continue;
		mvaddch(rp->y, rp->x, ' ');
		Field[rp->y][rp->x]--;
		rp->y += sign(My_pos.y - rp->y);
		rp->x += sign(My_pos.x - rp->x);
		if (rp->y <= 0)
			rp->y = 0;
		else if (rp->y >= Y_FIELDSIZE)
			rp->y = Y_FIELDSIZE - 1;
		if (rp->x <= 0)
			rp->x = 0;
		else if (rp->x >= X_FIELDSIZE)
			rp->x = X_FIELDSIZE - 1;
		Field[rp->y][rp->x]++;
	}

	Min.y = Y_FIELDSIZE;
	Min.x = X_FIELDSIZE;
	Max.y = 0;
	Max.x = 0;
	for (rp = Robots; rp < &Robots[MAXROBOTS]; rp++)
		if (rp->y < 0)
			continue;
		else if (rp->y == My_pos.y && rp->x == My_pos.x)
			Dead = TRUE;
		else if (Field[rp->y][rp->x] > 1) {
			mvaddch(rp->y, rp->x, HEAP);
			rp->y = -1;
			Num_robots--;
			if (Waiting)
				Wait_bonus++;
			add_score(ROB_SCORE);
		}
		else {
			mvaddch(rp->y, rp->x, ROBOT);
			if (rp->y < Min.y)
				Min.y = rp->y;
			if (rp->x < Min.x)
				Min.x = rp->x;
			if (rp->y > Max.y)
				Max.y = rp->y;
			if (rp->x > Max.x)
				Max.x = rp->x;
		}

	if (was_sig) {
		refresh();
		if (Dead || Num_robots <= 0)
D 5
			longjmp(End_move);
E 5
I 5
			longjmp(End_move, 0);
E 5
	}

# ifdef DEBUG
	standout();
	move(Min.y, Min.x);
	addch(inch());
	move(Max.y, Max.x);
	addch(inch());
	standend();
# endif DEBUG
	if (Real_time)
		alarm(3);
}

/*
 * add_score:
 *	Add a score to the overall point total
 */
add_score(add)
int	add;
{
	Score += add;
	move(Y_SCORE, X_SCORE);
	printw("%d", Score);
}

/*
 * sign:
 *	Return the sign of the number
 */
sign(n)
int	n;
{
	if (n < 0)
		return -1;
	else if (n > 0)
		return 1;
	else
		return 0;
}
E 1
