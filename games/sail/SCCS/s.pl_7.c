h37091
s 00002/00002/00438
d D 8.1 93/05/31 17:51:02 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00006/00440
d D 5.10 93/01/22 18:25:58 bostic 20 19
c get it all...
e
s 00000/00011/00446
d D 5.9 93/01/22 18:24:45 bostic 19 18
c curses should be handling all of the job stop stuff (untested)
e
s 00003/00001/00454
d D 5.8 92/08/28 16:02:36 elan 18 17
c Fixed tstp and added include file for CTRL.
e
s 00003/00001/00452
d D 5.7 91/02/28 14:47:56 bostic 17 16
c ANSI
e
s 00001/00011/00452
d D 5.6 90/06/01 13:21:52 bostic 16 15
c new copyright notice
e
s 00010/00005/00453
d D 5.5 88/06/18 19:56:00 bostic 15 14
c install approved copyright notice
e
s 00009/00003/00449
d D 5.4 88/03/09 12:30:40 bostic 14 13
c written by David Riggle and Edward Wang; add Berkeley specific copyright
e
s 00001/00001/00451
d D 5.3 87/12/22 13:33:38 bostic 13 12
c make ANSI C compatible
e
s 00004/00002/00448
d D 5.2 87/10/07 07:52:27 bostic 12 11
c sprintf doesn't necessarily return its first arg
e
s 00005/00005/00445
d D 5.1 85/05/29 16:10:21 dist 11 10
c Add copyright
e
s 00006/00000/00444
d D 2.9 85/04/23 21:53:03 edward 10 9
c copyright message
e
s 00000/00001/00444
d D 2.8 84/02/23 16:44:12 edward 9 8
c lint
e
s 00024/00002/00421
d D 2.7 84/02/23 15:58:13 edward 8 7
c check error from Sync(), block alarm when suspending,
c initscr() called differently.
e
s 00001/00001/00422
d D 2.6 84/02/03 15:37:01 edward 7 6
c prints stats wrong way round
e
s 00004/00000/00419
d D 2.5 83/12/17 13:19:03 edward 6 5
c some more blockalarm()s
e
s 00001/00000/00418
d D 2.4 83/12/09 13:32:09 edward 5 4
c turn window bigger, and block alarm when refreshing
e
s 00002/00003/00416
d D 2.3 83/11/08 15:58:29 edward 4 3
c fixed clear lastline when quitting
e
s 00001/00001/00418
d D 2.2 83/11/08 15:40:52 edward 3 2
c show state of 'S' command
e
s 00000/00000/00419
d D 2.1 83/10/31 13:46:37 edward 2 1
c new version
e
s 00419/00000/00000
d D 1.1 83/10/28 19:24:37 edward 1 0
c date and time created 83/10/28 19:24:37 by edward
e
u
U
t
T
I 10
/*
D 11
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 11
I 11
D 21
 * Copyright (c) 1983 Regents of the University of California.
D 14
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 16
 * Redistribution and use in source and binary forms are permitted
D 15
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 15
I 15
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
E 16
I 16
 * %sccs.include.redist.c%
E 16
E 15
E 14
E 11
 */

E 10
I 1
#ifndef lint
D 11
static	char *sccsid = "%W% %E%";
#endif
E 11
I 11
static char sccsid[] = "%W% (Berkeley) %G%";
D 14
#endif not lint
E 14
I 14
#endif /* not lint */
E 14
E 11

I 18
#include <sys/ttydefaults.h>
E 18
#include "player.h"

I 18

E 18
/*
 * Display interface
 */

static char sc_hasprompt;
static char *sc_prompt;
static char *sc_buf;
static int sc_line;

initscreen()
{
D 8
	(void) initscr();
E 8
I 8
	/* initscr() already done in SCREENTEST() */
E 8
	view_w = newwin(VIEW_Y, VIEW_X, VIEW_T, VIEW_L);
	slot_w = newwin(SLOT_Y, SLOT_X, SLOT_T, SLOT_L);
	scroll_w = newwin(SCROLL_Y, SCROLL_X, SCROLL_T, SCROLL_L);
	stat_w = newwin(STAT_Y, STAT_X, STAT_T, STAT_L);
	turn_w = newwin(TURN_Y, TURN_X, TURN_T, TURN_L);
	done_curses++;
	(void) leaveok(view_w, 1);
	(void) leaveok(slot_w, 1);
	(void) leaveok(stat_w, 1);
	(void) leaveok(turn_w, 1);
I 8
D 20
#ifdef SIGTSTP
	{
D 17
		int susp();
E 17
I 17
		void susp();
E 17
		(void) signal(SIGTSTP, susp);
	}
#endif
E 20
E 8
	noecho();
	crmode();
I 8
D 9
	return 0;
E 9
E 8
}

cleanupscreen()
{
I 5
	/* alarm already turned off */
E 5
	if (done_curses) {
I 4
		(void) wmove(scroll_w, SCROLL_Y - 1, 0);
		(void) wclrtoeol(scroll_w);
E 4
		draw_screen();
D 4
		(void) move(LINES - 1, 0);
		(void) clrtoeol();
		(void) refresh();
E 4
		endwin();
	}
}

I 17
void
E 17
newturn()
{
	repaired = loaded = fired = changed = 0;
	movebuf[0] = '\0';

	(void) alarm(0);
	if (mf->readyL & R_LOADING)
		if (mf->readyL & R_DOUBLE)
			mf->readyL = R_LOADING;
		else
			mf->readyL = R_LOADED;
	if (mf->readyR & R_LOADING)
		if (mf->readyR & R_DOUBLE)
			mf->readyR = R_LOADING;
		else
			mf->readyR = R_LOADED;
I 8
	if (!hasdriver)
		Write(W_DDEAD, SHIP(0), 0, 0, 0, 0, 0);
E 8

	if (sc_hasprompt) {
		(void) wmove(scroll_w, sc_line, 0);
		(void) wclrtoeol(scroll_w);
	}
D 8
	Sync();
E 8
I 8
	if (Sync() < 0)
		leave(LEAVE_SYNC);
	if (!hasdriver)
		leave(LEAVE_DRIVER);
E 8
	if (sc_hasprompt)
		(void) wprintw(scroll_w, "%s%s", sc_prompt, sc_buf);

	if (turn % 50 == 0)
		Write(W_ALIVE, SHIP(0), 0, 0, 0, 0, 0);
	if (mf->FS && (!mc->rig1 || windspeed == 6))
		Write(W_FS, ms, 0, 0, 0, 0, 0);
	if (mf->FS == 1)
		Write(W_FS, ms, 0, 2, 0, 0, 0);

	if (mf->struck)
		leave(LEAVE_QUIT);
	if (mf->captured != 0)
		leave(LEAVE_CAPTURED);
	if (windspeed == 7)
		leave(LEAVE_HURRICAN);

	adjustview();
	draw_screen();

	(void) signal(SIGALRM, newturn);
	(void) alarm(7);
}

/*VARARGS2*/
Signal(fmt, ship, a, b, c, d)
char *fmt;
register struct ship *ship;
int a, b, c, d;
{
	if (!done_curses)
		return;
	if (*fmt == '\7')
		putchar(*fmt++);
	if (ship == 0)
		(void) wprintw(scroll_w, fmt, a, b, c, d);
	else
		(void) wprintw(scroll_w, fmt, ship->shipname,
			colours(ship), sterncolour(ship), a, b, c, d);
	Scroll();
}

Scroll()
{
	if (++sc_line >= SCROLL_Y)
		sc_line = 0;
	(void) wmove(scroll_w, sc_line, 0);
	(void) wclrtoeol(scroll_w);
}

prompt(p, ship)
register char *p;
struct ship *ship;
{
	static char buf[60];

D 12
	if (ship != 0)
		p = sprintf(buf, p, ship->shipname, colours(ship),
E 12
I 12
	if (ship != 0) {
		(void)sprintf(buf, p, ship->shipname, colours(ship),
E 12
			sterncolour(ship));
I 12
		p = buf;
	}
E 12
	sc_prompt = p;
	sc_buf = "";
	sc_hasprompt = 1;
	(void) waddstr(scroll_w, p);
}

endprompt(flag)
char flag;
{
	sc_hasprompt = 0;
	if (flag)
		Scroll();
}

sgetch(p, ship, flag)
char *p;
struct ship *ship;
char flag;
{
	register c;

	prompt(p, ship);
I 6
	blockalarm();
E 6
	(void) wrefresh(scroll_w);
I 6
	unblockalarm();
E 6
	while ((c = wgetch(scroll_w)) == EOF)
		;
	if (flag && c >= ' ' && c < 0x7f)
		(void) waddch(scroll_w, c);
	endprompt(flag);
	return c;
}

sgetstr(pr, buf, n)
char *pr;
register char *buf;
register n;
{
	register c;
	register char *p = buf;

	prompt(pr, (struct ship *)0);
	sc_buf = buf;
	for (;;) {
		*p = 0;
I 6
		blockalarm();
E 6
		(void) wrefresh(scroll_w);
I 6
		unblockalarm();
E 6
		while ((c = wgetch(scroll_w)) == EOF)
			;
		switch (c) {
		case '\n':
		case '\r':
			endprompt(1);
			return;
		case '\b':
			if (p > buf) {
				(void) waddstr(scroll_w, "\b \b");
				p--;
			}
			break;
		default:
			if (c >= ' ' && c < 0x7f && p < buf + n - 1) {
				*p++ = c;
				(void) waddch(scroll_w, c);
			} else
D 13
				(void) putchar(CTRL(g));
E 13
I 13
				(void) putchar(CTRL('g'));
E 13
		}
	}
}

draw_screen()
{
	draw_view();
	draw_turn();
	draw_stat();
	draw_slot();
	(void) wrefresh(scroll_w);		/* move the cursor */
}

draw_view()
{
	register struct ship *sp;

	(void) werase(view_w);
	foreachship(sp) {
		if (sp->file->dir
		    && sp->file->row > viewrow
		    && sp->file->row < viewrow + VIEW_Y
		    && sp->file->col > viewcol
		    && sp->file->col < viewcol + VIEW_X) {
			(void) wmove(view_w, sp->file->row - viewrow,
				sp->file->col - viewcol);
			(void) waddch(view_w, colours(sp));
			(void) wmove(view_w,
				sternrow(sp) - viewrow,
				sterncol(sp) - viewcol);
			(void) waddch(view_w, sterncolour(sp));
		}
	}
	(void) wrefresh(view_w);
}

draw_turn()
{
	(void) wmove(turn_w, 0, 0);
D 3
	(void) wprintw(turn_w, "Turn %d", turn);
E 3
I 3
	(void) wprintw(turn_w, "%cTurn %d", dont_adjust?'*':'-', turn);
E 3
	(void) wrefresh(turn_w);
}

draw_stat()
{
	(void) wmove(stat_w, STAT_1, 0);
	(void) wprintw(stat_w, "Points  %3d\n", mf->points);
	(void) wprintw(stat_w, "Fouls    %2d\n", fouled(ms));
	(void) wprintw(stat_w, "Grapples %2d\n", grappled(ms));

	(void) wmove(stat_w, STAT_2, 0);
	(void) wprintw(stat_w, "    0 %c(%c)\n",
		maxmove(ms, winddir + 3, -1) + '0',
		maxmove(ms, winddir + 3, 1) + '0');
	(void) waddstr(stat_w, "   \\|/\n");
	(void) wprintw(stat_w, "   -^-%c(%c)\n",
		maxmove(ms, winddir + 2, -1) + '0',
		maxmove(ms, winddir + 2, 1) + '0');
	(void) waddstr(stat_w, "   /|\\\n");
	(void) wprintw(stat_w, "    | %c(%c)\n",
		maxmove(ms, winddir + 1, -1) + '0',
		maxmove(ms, winddir + 1, 1) + '0');
	(void) wprintw(stat_w, "   %c(%c)\n",
		maxmove(ms, winddir, -1) + '0',
		maxmove(ms, winddir, 1) + '0');

	(void) wmove(stat_w, STAT_3, 0);
	(void) wprintw(stat_w, "Load  %c%c %c%c\n",
		loadname[mf->loadL], readyname(mf->readyL),
		loadname[mf->loadR], readyname(mf->readyR));
	(void) wprintw(stat_w, "Hull %2d\n", mc->hull);
	(void) wprintw(stat_w, "Crew %2d %2d %2d\n",
		mc->crew1, mc->crew2, mc->crew3);
	(void) wprintw(stat_w, "Guns %2d %2d\n", mc->gunL, mc->gunR);
D 7
	(void) wprintw(stat_w, "Carr %2d %2d\n", mc->carR, mc->carL);
E 7
I 7
	(void) wprintw(stat_w, "Carr %2d %2d\n", mc->carL, mc->carR);
E 7
	(void) wprintw(stat_w, "Rigg %d %d %d ", mc->rig1, mc->rig2, mc->rig3);
	if (mc->rig4 < 0)
		(void) waddch(stat_w, '-');
	else
		(void) wprintw(stat_w, "%d", mc->rig4);
	(void) wrefresh(stat_w);
}

draw_slot()
{
	if (!boarding(ms, 0)) {
		(void) mvwaddstr(slot_w, 0, 0, "   ");
		(void) mvwaddstr(slot_w, 1, 0, "   ");
	} else
		(void) mvwaddstr(slot_w, 1, 0, "OBP");
	if (!boarding(ms, 1)) {
		(void) mvwaddstr(slot_w, 2, 0, "   ");
		(void) mvwaddstr(slot_w, 3, 0, "   ");
	} else
		(void) mvwaddstr(slot_w, 3, 0, "DBP");

	(void) wmove(slot_w, SLOT_Y-4, 0);
	if (mf->RH)
		(void) wprintw(slot_w, "%dRH", mf->RH);
	else
		(void) waddstr(slot_w, "   ");
	(void) wmove(slot_w, SLOT_Y-3, 0);
	if (mf->RG)
		(void) wprintw(slot_w, "%dRG", mf->RG);
	else
		(void) waddstr(slot_w, "   ");
	(void) wmove(slot_w, SLOT_Y-2, 0);
	if (mf->RR)
		(void) wprintw(slot_w, "%dRR", mf->RR);
	else
		(void) waddstr(slot_w, "   ");

#define Y	(SLOT_Y/2)
	(void) wmove(slot_w, 7, 1);
	(void) wprintw(slot_w,"%d", windspeed);
	(void) mvwaddch(slot_w, Y, 0, ' ');
	(void) mvwaddch(slot_w, Y, 2, ' ');
	(void) mvwaddch(slot_w, Y-1, 0, ' ');
	(void) mvwaddch(slot_w, Y-1, 1, ' ');
	(void) mvwaddch(slot_w, Y-1, 2, ' ');
	(void) mvwaddch(slot_w, Y+1, 0, ' ');
	(void) mvwaddch(slot_w, Y+1, 1, ' ');
	(void) mvwaddch(slot_w, Y+1, 2, ' ');
	(void) wmove(slot_w, Y - dr[winddir], 1 - dc[winddir]);
	switch (winddir) {
	case 1:
	case 5:
		(void) waddch(slot_w, '|');
		break;
	case 2:
	case 6:
		(void) waddch(slot_w, '/');
		break;
	case 3:
	case 7:
		(void) waddch(slot_w, '-');
		break;
	case 4:
	case 8:
		(void) waddch(slot_w, '\\');
		break;
	}
	(void) mvwaddch(slot_w, Y + dr[winddir], 1 + dc[winddir], '+');
	(void) wrefresh(slot_w);
}

draw_board()
{
	register int n;

	(void) clear();
	(void) werase(view_w);
	(void) werase(slot_w);
	(void) werase(scroll_w);
	(void) werase(stat_w);
	(void) werase(turn_w);

	sc_line = 0;

	(void) move(BOX_T, BOX_L);
	for (n = 0; n < BOX_X; n++)
		(void) addch('-');
	(void) move(BOX_B, BOX_L);
	for (n = 0; n < BOX_X; n++)
		(void) addch('-');
	for (n = BOX_T+1; n < BOX_B; n++) {
		(void) mvaddch(n, BOX_L, '|');
		(void) mvaddch(n, BOX_R, '|');
	}
	(void) mvaddch(BOX_T, BOX_L, '+');
	(void) mvaddch(BOX_T, BOX_R, '+');
	(void) mvaddch(BOX_B, BOX_L, '+');
	(void) mvaddch(BOX_B, BOX_R, '+');
	(void) refresh();

#define WSaIM "Wooden Ships & Iron Men"
	(void) wmove(view_w, 2, (VIEW_X - sizeof WSaIM - 1) / 2);
	(void) waddstr(view_w, WSaIM);
	(void) wmove(view_w, 4, (VIEW_X - strlen(cc->name)) / 2);
	(void) waddstr(view_w, cc->name);
	(void) wrefresh(view_w);

	(void) move(LINE_T, LINE_L);
	(void) printw("Class %d %s (%d guns) '%s' (%c%c)",
		mc->class,
		classname[mc->class],
		mc->guns,
		ms->shipname,
		colours(ms),
		sterncolour(ms));
	(void) refresh();
}

centerview()
{
	viewrow = mf->row - VIEW_Y / 2;
	viewcol = mf->col - VIEW_X / 2;
}

upview()
{
	viewrow -= VIEW_Y / 3;
}

downview()
{
	viewrow += VIEW_Y / 3;
}

leftview()
{
	viewcol -= VIEW_X / 5;
}

rightview()
{
	viewcol += VIEW_X / 5;
}

adjustview()
{
	if (dont_adjust)
		return;
	if (mf->row < viewrow + VIEW_Y/4)
		viewrow = mf->row - (VIEW_Y - VIEW_Y/4);
	else if (mf->row > viewrow + (VIEW_Y - VIEW_Y/4))
		viewrow = mf->row - VIEW_Y/4;
	if (mf->col < viewcol + VIEW_X/8)
		viewcol = mf->col - (VIEW_X - VIEW_X/8);
	else if (mf->col > viewcol + (VIEW_X - VIEW_X/8))
		viewcol = mf->col - VIEW_X/8;
}
I 8
D 19

#ifdef SIGTSTP
I 17
void
E 17
susp()
{
	blockalarm();
D 18
	tstp();
E 18
I 18
	tstp(SIGTSTP);
E 18
	(void) signal(SIGTSTP, susp);
	unblockalarm();
}
#endif
E 19
E 8
E 1
