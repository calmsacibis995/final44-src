h45179
s 00002/00002/00272
d D 8.1 93/05/31 17:45:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00268
d D 5.5 92/08/31 10:18:09 elan 5 4
c Fixed CTRL macro use and updated header file includes.
e
s 00001/00011/00272
d D 5.4 90/06/01 13:14:58 bostic 4 3
c new copyright notice
e
s 00010/00005/00273
d D 5.3 88/06/18 20:04:44 bostic 3 2
c install approved copyright notice
e
s 00009/00003/00269
d D 5.2 88/03/09 11:18:41 bostic 2 1
c Written by Ken Arnold; add Berkeley specific copyright
e
s 00272/00000/00000
d D 5.1 85/05/30 18:34:45 mckusick 1 0
c date and time created 85/05/30 18:34:45 by mckusick
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

D 5
# include	"robots.h"
# include	<ctype.h>
E 5
I 5
#include <sys/ttydefaults.h>
#include <ctype.h>
#include "robots.h"
E 5

# define	ESC	'\033'

/*
 * get_move:
 *	Get and execute a move from the player
 */
get_move()
{
	register int	c;
	register int	y, x, lastmove;
	static COORD	newpos;

	if (Waiting)
		return;

#ifdef	FANCY
	if (Pattern_roll) {
		if (Next_move >= Move_list)
			lastmove = *Next_move;
		else
			lastmove = -1;	/* flag for "first time in" */
	}
#endif
	for (;;) {
		if (Teleport && must_telep())
			goto teleport;
		if (Running)
			c = Run_ch;
		else if (Count != 0)
			c = Cnt_move;
#ifdef	FANCY
		else if (Num_robots > 1 && Stand_still)
			c = '>';
		else if (Num_robots > 1 && Pattern_roll) {
			if (*++Next_move == '\0') {
				if (lastmove < 0)
					goto over;
				Next_move = Move_list;
			}
			c = *Next_move;
			mvaddch(0, 0, c);
			if (c == lastmove)
				goto over;
		}
#endif
		else {
over:
			c = getchar();
			if (isdigit(c)) {
				Count = (c - '0');
				while (isdigit(c = getchar()))
					Count = Count * 10 + (c - '0');
				if (c == ESC)
					goto over;
				Cnt_move = c;
				if (Count)
					leaveok(stdscr, TRUE);
			}
		}

		switch (c) {
		  case ' ':
		  case '.':
			if (do_move(0, 0))
				goto ret;
			break;
		  case 'y':
			if (do_move(-1, -1))
				goto ret;
			break;
		  case 'k':
			if (do_move(-1, 0))
				goto ret;
			break;
		  case 'u':
			if (do_move(-1, 1))
				goto ret;
			break;
		  case 'h':
			if (do_move(0, -1))
				goto ret;
			break;
		  case 'l':
			if (do_move(0, 1))
				goto ret;
			break;
		  case 'b':
			if (do_move(1, -1))
				goto ret;
			break;
		  case 'j':
			if (do_move(1, 0))
				goto ret;
			break;
		  case 'n':
			if (do_move(1, 1))
				goto ret;
			break;
		  case 'Y': case 'U': case 'H': case 'J':
		  case 'K': case 'L': case 'B': case 'N':
		  case '>':
			Running = TRUE;
			if (c == '>')
				Run_ch = ' ';
			else
				Run_ch = tolower(c);
			leaveok(stdscr, TRUE);
			break;
		  case 'q':
		  case 'Q':
			if (query("Really quit?"))
				quit();
			refresh();
			break;
		  case 'w':
		  case 'W':
			Waiting = TRUE;
			leaveok(stdscr, TRUE);
			flushok(stdscr, FALSE);
			goto ret;
		  case 't':
		  case 'T':
teleport:
			Running = FALSE;
			mvaddch(My_pos.y, My_pos.x, ' ');
			My_pos = *rnd_pos();
			mvaddch(My_pos.y, My_pos.x, PLAYER);
			leaveok(stdscr, FALSE);
			refresh();
			flush_in();
			goto ret;
D 5
		  case CTRL(L):
E 5
I 5
		  case CTRL('L'):
E 5
			wrefresh(curscr);
			break;
		  case EOF:
			break;
		  default:
D 5
			putchar(CTRL(G));
E 5
I 5
			putchar(CTRL('G'));
E 5
			reset_count();
			fflush(stdout);
			break;
		}
	}
ret:
	if (Count > 0)
		if (--Count == 0)
			leaveok(stdscr, FALSE);
}

/*
 * must_telep:
 *	Must I teleport; i.e., is there anywhere I can move without
 * being eaten?
 */
must_telep()
{
	register int	x, y;
	static COORD	newpos;

#ifdef	FANCY
	if (Stand_still && Num_robots > 1 && eaten(&My_pos))
		return TRUE;
#endif

	for (y = -1; y <= 1; y++) {
		newpos.y = My_pos.y + y;
		if (newpos.y <= 0 || newpos.y >= Y_FIELDSIZE)
			continue;
		for (x = -1; x <= 1; x++) {
			newpos.x = My_pos.x + x;
			if (newpos.x <= 0 || newpos.x >= X_FIELDSIZE)
				continue;
			if (Field[newpos.y][newpos.x] > 0)
				continue;
			if (!eaten(&newpos))
				return FALSE;
		}
	}
	return TRUE;
}

/*
 * do_move:
 *	Execute a move
 */
do_move(dy, dx)
int	dy, dx;
{
	static COORD	newpos;

	newpos.y = My_pos.y + dy;
	newpos.x = My_pos.x + dx;
	if (newpos.y <= 0 || newpos.y >= Y_FIELDSIZE ||
	    newpos.x <= 0 || newpos.x >= X_FIELDSIZE ||
	    Field[newpos.y][newpos.x] > 0 || eaten(&newpos)) {
		if (Running) {
			Running = FALSE;
			leaveok(stdscr, FALSE);
			move(My_pos.y, My_pos.x);
			refresh();
		}
		else {
D 5
			putchar(CTRL(G));
E 5
I 5
			putchar(CTRL('G'));
E 5
			reset_count();
		}
		return FALSE;
	}
	else if (dy == 0 && dx == 0)
		return TRUE;
	mvaddch(My_pos.y, My_pos.x, ' ');
	My_pos = newpos;
	mvaddch(My_pos.y, My_pos.x, PLAYER);
	if (!jumping())
		refresh();
	return TRUE;
}

/*
 * eaten:
 *	Player would get eaten at this place
 */
eaten(pos)
register COORD	*pos;
{
	register int	x, y;

	for (y = pos->y - 1; y <= pos->y + 1; y++) {
		if (y <= 0 || y >= Y_FIELDSIZE)
			continue;
		for (x = pos->x - 1; x <= pos->x + 1; x++) {
			if (x <= 0 || x >= X_FIELDSIZE)
				continue;
			if (Field[y][x] == 1)
				return TRUE;
		}
	}
	return FALSE;
}

/*
 * reset_count:
 *	Reset the count variables
 */
reset_count()
{
	Count = 0;
	Running = FALSE;
	leaveok(stdscr, FALSE);
	refresh();
}

/*
 * jumping:
 *	See if we are jumping, i.e., we should not refresh.
 */
jumping()
{
	return (Jump && (Count || Running || Waiting));
}
E 1
