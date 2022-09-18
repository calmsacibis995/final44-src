h57966
s 00005/00005/00269
d D 8.1 93/05/31 18:02:46 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00015/00261
d D 5.10 93/02/03 18:04:53 torek 13 12
c rm offensive Pascalization to make gcc2 happy
e
s 00001/00000/00275
d D 5.9 92/08/31 10:25:38 elan 12 11
c Added termios.h to incldues.
e
s 00007/00002/00268
d D 5.8 91/02/28 15:44:56 bostic 11 10
c ANSI
e
s 00001/00011/00269
d D 5.7 90/06/01 13:56:31 bostic 10 9
c new copyright notice
e
s 00001/00010/00279
d D 5.6 89/08/02 16:08:32 bostic 9 8
c don't allow sub-shells; English kindness
e
s 00010/00005/00279
d D 5.5 88/06/27 16:35:20 bostic 8 7
c install approved copyright notice
e
s 00010/00004/00274
d D 5.4 88/03/09 11:24:15 bostic 7 6
c written by Michael Toy; add Berkeley specific copyright
e
s 00004/00004/00274
d D 5.3 88/01/02 19:26:36 bostic 6 5
c fix CNTRL macro for ANSI C
e
s 00001/00001/00277
d D 5.2 85/06/25 13:44:42 karels 5 4
c baudrate multiply defined
e
s 00015/00001/00263
d D 5.1 85/05/29 11:25:14 dist 4 3
c Add copyright
e
s 00001/00002/00263
d D 4.3 83/05/19 12:54:54 arnold 3 2
c 
e
s 00010/00004/00255
d D 4.2 83/05/19 12:53:58 arnold 2 1
c jump on slow terminals when using capitols
e
s 00259/00000/00000
d D 4.1 82/10/24 18:26:59 mckusick 1 0
c date and time created 82/10/24 18:26:59 by mckusick
e
u
U
t
T
I 1
D 3

D 2
static char sccsid[] = "	%M%	%I%	%E%	";
E 2
I 2
static char sccsid[] = "	worm.c	4.1	82/10/24	";
E 3
I 3
D 4
static char	*sccsid = "%W% (Berkeley) %G%";
E 4
I 4
/*
D 14
 * Copyright (c) 1980 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
E 7
 */

#ifndef lint
D 14
char copyright[] =
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 14
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 4
E 3
E 2

/*
 * Worm.  Written by Michael Toy
 * UCSC
 */

#include <ctype.h>
#include <curses.h>
#include <signal.h>
I 12
#include <termios.h>
E 12

#define newlink() (struct body *) malloc(sizeof (struct body));
#define HEAD '@'
#define BODY 'o'
#define LENGTH 7
#define RUNLEN 8
D 13
#define when break;case
#define otherwise break;default
E 13
D 6
#define CNTRL(p) ('p'-'A'+1)
E 6
I 6
#define CNTRL(p) (p-'A'+1)
E 6
I 2
D 5
#ifndef attron
E 5
I 5
#ifndef baudrate
E 5
# define	baudrate()	_tty.sg_ospeed
#endif
E 2

WINDOW *tv;
WINDOW *stw;
struct body {
	int x;
	int y;
	struct body *prev;
	struct body *next;
} *head, *tail, goody;
int growing = 0;
int running = 0;
I 2
int slow = 0;
E 2
int score = 0;
int start_len = LENGTH;
char lastch;
char outbuf[BUFSIZ];

I 11
void leave(), wake(), suspend();

E 11
main(argc, argv)
D 11
char **argv;
E 11
I 11
	int argc;
	char **argv;
E 11
{
D 11
	int leave(), wake(), suspend();
E 11
	char ch;

	if (argc == 2)
		start_len = atoi(argv[1]);
	if ((start_len <= 0) || (start_len > 500))
		start_len = LENGTH;
	setbuf(stdout, outbuf);
	srand(getpid());
	signal(SIGALRM, wake);
	signal(SIGINT, leave);
	signal(SIGQUIT, leave);
D 9
#ifdef SIGTSTP
E 9
	signal(SIGTSTP, suspend);	/* process control signal */
D 9
#endif
E 9
	initscr();
	crmode();
	noecho();
I 2
	slow = (baudrate() <= B1200);
E 2
	clear();
	stw = newwin(1, COLS-1, 0, 0);
	tv = newwin(LINES-1, COLS-1, 1, 0);
	box(tv, '*', '*');
	scrollok(tv, FALSE);
	scrollok(stw, FALSE);
	wmove(stw, 0, 0);
	wprintw(stw, " Worm");
	refresh();
	wrefresh(stw);
	wrefresh(tv);
	life();			/* Create the worm */
	prize();		/* Put up a goal */
	while(1)
	{
		if (running)
		{
			running--;
			process(lastch);
		}
		else
		{
		    fflush(stdout);
		    if (read(0, &ch, 1) >= 0)
			process(ch);
		}
	}
}

life()
{
	register struct body *bp, *np;
	register int i;

	head = newlink();
	head->x = start_len+2;
	head->y = 12;
	head->next = NULL;
	display(head, HEAD);
	for (i = 0, bp = head; i < start_len; i++, bp = np) {
		np = newlink();
		np->next = bp;
		bp->prev = np;
		np->x = bp->x - 1;
		np->y = bp->y;
		display(np, BODY);
	}
	tail = np;
	tail->prev = NULL;
D 2
	wrefresh(tv);
E 2
}

display(pos, chr)
struct body *pos;
char chr;
{
	wmove(tv, pos->y, pos->x);
	waddch(tv, chr);
}

I 11
void
E 11
leave()
{
	endwin();
	exit(0);
}

I 11
void
E 11
wake()
{
	signal(SIGALRM, wake);
	fflush(stdout);
	process(lastch);
}

rnd(range)
{
	return abs((rand()>>5)+(rand()>>5)) % range;
}

newpos(bp)
struct body * bp;
{
	do {
		bp->y = rnd(LINES-3)+ 2;
		bp->x = rnd(COLS-3) + 1;
		wmove(tv, bp->y, bp->x);
	} while(winch(tv) != ' ');
}

prize()
{
	int value;

	value = rnd(9) + 1;
	newpos(&goody);
	waddch(tv, value+'0');
	wrefresh(tv);
}

process(ch)
char ch;
{
	register int x,y;
	struct body *nh;

	alarm(0);
	x = head->x;
	y = head->y;
	switch(ch)
	{
D 13
		when 'h': x--;
		when 'j': y++;
		when 'k': y--;
		when 'l': x++;
		when 'H': x--; running = RUNLEN; ch = tolower(ch);
		when 'J': y++; running = RUNLEN/2; ch = tolower(ch);
		when 'K': y--; running = RUNLEN/2; ch = tolower(ch);
		when 'L': x++; running = RUNLEN; ch = tolower(ch);
		when '\f': setup(); return;
D 6
		when CNTRL(Z): suspend(); return;
		when CNTRL(C): crash(); return;
		when CNTRL(D): crash(); return;
E 6
I 6
		when CNTRL('Z'): suspend(); return;
		when CNTRL('C'): crash(); return;
		when CNTRL('D'): crash(); return;
E 6
		otherwise: if (! running) alarm(1);
E 13
I 13
		case 'h': x--; break;
		case 'j': y++; break;
		case 'k': y--; break;
		case 'l': x++; break;
		case 'H': x--; running = RUNLEN; ch = tolower(ch); break;
		case 'J': y++; running = RUNLEN/2; ch = tolower(ch); break;
		case 'K': y--; running = RUNLEN/2; ch = tolower(ch); break;
		case 'L': x++; running = RUNLEN; ch = tolower(ch); break;
		case '\f': setup(); return;
		case CNTRL('Z'): suspend(); return;
		case CNTRL('C'): crash(); return;
		case CNTRL('D'): crash(); return;
		default: if (! running) alarm(1);
E 13
			   return;
	}
	lastch = ch;
	if (growing == 0)
	{
		display(tail, ' ');
		tail->next->prev = NULL;
		nh = tail->next;
		free(tail);
		tail = nh;
	}
	else growing--;
	display(head, BODY);
	wmove(tv, y, x);
	if (isdigit(ch = winch(tv)))
	{
		growing += ch-'0';
		prize();
		score += growing;
		running = 0;
		wmove(stw, 0, 68);
		wprintw(stw, "Score: %3d", score);
		wrefresh(stw);
	}
	else if(ch != ' ') crash();
	nh = newlink();
	nh->next = NULL;
	nh->prev = head;
	head->next = nh;
	nh->y = y;
	nh->x = x;
	display(nh, HEAD);
	head = nh;
D 2
	wrefresh(tv);
	if (! running) alarm(1);
E 2
I 2
	if (!(slow && running))
		wrefresh(tv);
	if (!running)
		alarm(1);
E 2
}

crash()
{
	sleep(2);
	clear();
	move(23, 0);
	refresh();
D 9
	printf("Well you ran into something and the game is over.\n");
E 9
I 9
	printf("Well, you ran into something and the game is over.\n");
E 9
	printf("Your final score was %d\n", score);
	leave();
}

I 11
void
E 11
suspend()
{
	char *sh;

	move(LINES-1, 0);
	refresh();
	endwin();
	fflush(stdout);
D 9
#ifdef SIGTSTP
E 9
	kill(getpid(), SIGTSTP);
	signal(SIGTSTP, suspend);
D 9
#else
	sh = getenv("SHELL");
	if (sh == NULL)
		sh = "/bin/sh";
	system(sh);
#endif
E 9
	crmode();
	noecho();
	setup();
}

setup()
{
	clear();
	refresh();
	touchwin(stw);
	wrefresh(stw);
	touchwin(tv);
	wrefresh(tv);
	alarm(1);
}
E 1
