h19837
s 00001/00001/00256
d D 8.2 95/04/28 15:41:59 bostic 14 13
c externs.h -> extern.h
e
s 00002/00002/00255
d D 8.1 93/05/31 16:13:05 bostic 13 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00256
d R 5.8 92/12/30 14:45:48 elan 12 11
c changed ERR to CURSES_ERR.
e
s 00000/00001/00257
d D 5.7 92/06/16 20:11:43 bostic 11 10
c initscr() does a savetty() call; new curses doesn't have savetty().
e
s 00001/00001/00257
d D 5.6 91/03/04 10:31:07 bostic 10 9
c ANSI
e
s 00003/00001/00255
d D 5.5 91/02/27 17:32:23 bostic 9 8
c ANSI
e
s 00001/00011/00255
d D 5.4 90/06/01 13:02:04 bostic 8 7
c new copyright notice
e
s 00001/00001/00265
d D 5.3 89/09/15 16:17:34 bostic 7 6
c POSIX signals
e
s 00010/00005/00256
d D 5.2 88/06/19 14:11:14 bostic 6 5
c install approved copyright notice
e
s 00011/00005/00250
d D 5.1 88/05/08 15:49:38 bostic 5 4
c add Berkeley header; yank to 5.1
e
s 00003/00005/00252
d D 1.4 87/06/03 11:17:40 bostic 4 3
c switch was silly
e
s 00006/00000/00251
d D 1.3 85/04/24 15:28:51 edward 3 2
c copyright messages
e
s 00010/00002/00241
d D 1.2 84/11/28 18:29:38 edward 2 1
c Dave's changes
e
s 00243/00000/00000
d D 1.1 84/11/18 18:59:01 edward 1 0
c date and time created 84/11/18 18:59:01 by edward
e
u
U
t
T
I 3
/*
D 5
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 5
I 5
D 13
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 6
E 5
 */

E 3
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% %G%";
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

D 14
#include "externs.h"
E 14
I 14
#include "extern.h"
E 14
#undef UP
#include <curses.h>

#define abs(a)	((a) < 0 ? -(a) : (a))
#define MIDR  (LINES/2 - 1)
#define MIDC  (COLS/2 - 1)

int row, column;
int dr = 0, dc = 0;
char destroyed;
int clock = 120;		/* time for all the flights in the game */
char cross = 0;
D 7
int (*oldsig)();
E 7
I 7
sig_t oldsig;
E 7

I 9
void
E 9
succumb()
{
D 2
	endfly();
	die();
E 2
I 2
D 4
	switch (oldsig) {
	case SIG_DFL:
E 4
I 4
	if (oldsig == SIG_DFL) {
E 4
		endfly();
		exit(1);
D 4
	case SIG_IGN:
		break;
	default:
E 4
I 4
	}
	if (oldsig != SIG_IGN) {
E 4
		endfly();
D 9
		(*oldsig)();
E 9
I 9
		(*oldsig)(SIGINT);
E 9
	}
E 2
}

visual()
{
D 10
	int moveenemy();
E 10
I 10
	void moveenemy();
E 10

	destroyed = 0;
D 11
	savetty();
E 11
	if(initscr() == ERR){
		puts("Whoops!  No more memory...");
		return(0);
	}
	oldsig = signal(SIGINT, succumb);
	crmode();
	noecho();
	screen();
	row = rnd(LINES-3) + 1;
	column = rnd(COLS-2) + 1;
	moveenemy();
	for (;;) {
		switch(getchar()){

			case 'h':
			case 'r':
				dc = -1;
				fuel--;
				break;

			case 'H':
			case 'R':
				dc = -5;
				fuel -= 10;
				break;

			case 'l':
				dc = 1;
				fuel--;
				break;

			case 'L':
				dc = 5;
				fuel -= 10;
				break;

			case 'j':
			case 'u':
				dr = 1;
				fuel--;
				break;

			case 'J':
			case 'U':
				dr = 5;
				fuel -= 10;
				break;

			case 'k':
			case 'd':
				dr = -1;
				fuel--;
				break;

			case 'K':
			case 'D':
				dr = -5;
				fuel -= 10;
				break;

			case '+':
				if (cross){
					cross = 0;
					notarget();
				}
				else
					cross = 1;
				break;

			case ' ':
			case 'f':
				if (torps){
					torps -= 2;
					blast();
					if (row == MIDR && column - MIDC < 2 && MIDC - column < 2){
						destroyed = 1;
						alarm(0);
					}
				}
				else
					mvaddstr(0,0,"*** Out of torpedoes. ***");
				break;

			case 'q':
				endfly();
				return(0);

			default:
				mvaddstr(0,26,"Commands = r,R,l,L,u,U,d,D,f,+,q");
				continue;

			case EOF:
				break;
		}
		if (destroyed){
			endfly();
			return(1);
		}
		if (clock <= 0){
			endfly();
			die();
		}
	}
}

screen()
{
	register int r,c,n;
	int i;

	clear();
	i = rnd(100);
	for (n=0; n < i; n++){
		r = rnd(LINES-3) + 1;
		c = rnd(COLS);
		mvaddch(r, c, '.');
	}
	mvaddstr(LINES-1-1,21,"TORPEDOES           FUEL           TIME");
	refresh();
}

target()
{
	register int n;

	move(MIDR,MIDC-10);
	addstr("-------   +   -------");
	for (n = MIDR-4; n < MIDR-1; n++){
		mvaddch(n,MIDC,'|');
		mvaddch(n+6,MIDC,'|');
	}
}

notarget()
{
	register int n;

	move(MIDR,MIDC-10);
	addstr("                     ");
	for (n = MIDR-4; n < MIDR-1; n++){
		mvaddch(n,MIDC,' ');
		mvaddch(n+6,MIDC,' ');
	}
}

blast()
{
	register int n;

	alarm(0);
	move(LINES-1, 24);
	printw("%3d", torps);
	for(n = LINES-1-2; n >= MIDR + 1; n--){
		mvaddch(n, MIDC+MIDR-n, '/');
		mvaddch(n, MIDC-MIDR+n, '\\');
		refresh();
	}
	mvaddch(MIDR,MIDC,'*');
	for(n = LINES-1-2; n >= MIDR + 1; n--){
		mvaddch(n, MIDC+MIDR-n, ' ');
		mvaddch(n, MIDC-MIDR+n, ' ');
		refresh();
	}
	alarm(1);
}

I 9
void
E 9
moveenemy()
{
	double d;
	int oldr, oldc;

	oldr = row;
	oldc = column;
	if (fuel > 0){
		if (row + dr <= LINES-3 && row + dr > 0)
			row += dr;
		if (column + dc < COLS-1 && column + dc > 0)
			column += dc;
	} else if (fuel < 0){
		fuel = 0;
		mvaddstr(0,60,"*** Out of fuel ***");
	}
	d = (double) ((row - MIDR)*(row - MIDR) + (column - MIDC)*(column - MIDC));
	if (d < 16){
		row += (rnd(9) - 4) % (4 - abs(row - MIDR));
		column += (rnd(9) - 4) % (4 - abs(column - MIDC));
	}
	clock--;
	mvaddstr(oldr, oldc - 1, "   ");
	if (cross)
		target();
	mvaddstr(row, column - 1, "/-\\");
	move(LINES-1, 24);
	printw("%3d", torps);
	move(LINES-1, 42);
	printw("%3d", fuel);
	move(LINES-1, 57);
	printw("%3d", clock);
	refresh();
	signal(SIGALRM, moveenemy);
	alarm(1);
}

endfly()
{
	alarm(0);
	signal(SIGALRM, SIG_DFL);
	mvcur(0,COLS-1,LINES-1,0);
	endwin();
	signal(SIGTSTP, SIG_DFL);
	signal(SIGINT, oldsig);
}
E 1
