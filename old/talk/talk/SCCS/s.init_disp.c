h25994
s 00007/00001/00119
d D 1.5 95/04/29 10:09:46 bostic 5 4
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00115
d D 1.4 94/04/02 15:19:06 bostic 4 3
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00001/00000/00118
d D 1.3 92/10/17 13:36:38 bostic 3 2
c lint to make gcc shut up
e
s 00001/00000/00117
d D 1.2 90/05/31 16:40:59 marc 2 1
c check in for Marc: needs USE_OLD_TTY
e
s 00117/00000/00000
d D 1.1 89/09/13 16:14:30 marc 1 0
c date and time created 89/09/13 16:14:30 by marc
e
u
U
t
T
I 1
D 4
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "@(#)init_disp.c	5.1 (Berkeley) 6/6/85";
#endif not lint

/*
 * Initialization code for the display package,
 * as well as the signal handling routines.
 */

I 2
#define USE_OLD_TTY
E 2
#include "talk.h"
I 3
#include <sgtty.h>
I 5
#include <stdlib.h>
E 5
E 3
#include <signal.h>
I 5
#include <unistd.h>
E 5

I 5
void	sig_sent();

E 5
/* 
 * Set up curses, catch the appropriate signals,
 * and build the various windows.
 */
I 5
void
E 5
init_display()
{
D 5
	void sig_sent();
E 5
	struct sigvec sigv;

	initscr();
	(void) sigvec(SIGTSTP, (struct sigvec *)0, &sigv);
	sigv.sv_mask |= sigmask(SIGALRM);
	(void) sigvec(SIGTSTP, &sigv, (struct sigvec *)0);
	curses_initialized = 1;
	clear();
	refresh();
	noecho();
	crmode();
	signal(SIGINT, sig_sent);
	signal(SIGPIPE, sig_sent);
	/* curses takes care of ^Z */
	my_win.x_nlines = LINES / 2;
	my_win.x_ncols = COLS;
	my_win.x_win = newwin(my_win.x_nlines, my_win.x_ncols, 0, 0);
	scrollok(my_win.x_win, FALSE);
	wclear(my_win.x_win);

	his_win.x_nlines = LINES / 2 - 1;
	his_win.x_ncols = COLS;
	his_win.x_win = newwin(his_win.x_nlines, his_win.x_ncols,
	    my_win.x_nlines+1, 0);
	scrollok(his_win.x_win, FALSE);
	wclear(his_win.x_win);

	line_win = newwin(1, COLS, my_win.x_nlines, 0);
	box(line_win, '-', '-');
	wrefresh(line_win);
	/* let them know we are working on it */
	current_state = "No connection yet";
}

/*
 * Trade edit characters with the other talk. By agreement
 * the first three characters each talk transmits after
 * connection are the three edit characters.
 */
I 5
void
E 5
set_edit_chars()
{
	char buf[3];
	int cc;
	struct sgttyb tty;
	struct ltchars ltc;
	
	ioctl(0, TIOCGETP, &tty);
	ioctl(0, TIOCGLTC, (struct sgttyb *)&ltc);
	my_win.cerase = tty.sg_erase;
	my_win.kill = tty.sg_kill;
	if (ltc.t_werasc == (char) -1)
		my_win.werase = '\027';	 /* control W */
	else
		my_win.werase = ltc.t_werasc;
	buf[0] = my_win.cerase;
	buf[1] = my_win.kill;
	buf[2] = my_win.werase;
	cc = write(sockt, buf, sizeof(buf));
	if (cc != sizeof(buf) )
		p_error("Lost the connection");
	cc = read(sockt, buf, sizeof(buf));
	if (cc != sizeof(buf) )
		p_error("Lost the connection");
	his_win.cerase = buf[0];
	his_win.kill = buf[1];
	his_win.werase = buf[2];
}

void
sig_sent()
{

	message("Connection closing. Exiting");
	quit();
}

/*
 * All done talking...hang up the phone and reset terminal thingy's
 */
I 5
__dead void
E 5
quit()
{

	if (curses_initialized) {
		wmove(his_win.x_win, his_win.x_nlines-1, 0);
		wclrtoeol(his_win.x_win);
		wrefresh(his_win.x_win);
		endwin();
	}
	if (invitation_waiting)
		send_delete();
	exit(0);
}
E 1
