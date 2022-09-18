h25740
s 00011/00010/00109
d D 5.4 95/04/29 10:09:47 bostic 4 3
c It failed to compile on the sparc because `swapresponse' was
c ifdef'ed on vax, sun, i386 (but not sparc).  I made it pass gcc2 -Wall.
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00004/00114
d D 5.3 94/04/02 15:19:07 bostic 3 2
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00001/00000/00117
d D 5.2 92/10/17 13:36:39 bostic 2 1
c lint to make gcc shut up
e
s 00117/00000/00000
d D 5.1 92/10/17 13:31:40 bostic 1 0
c date and time created 92/10/17 13:31:40 by bostic
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "@(#)io.c	5.1 (Berkeley) 6/6/85";
#endif not lint

/*
 * This file contains the I/O handling and the exchange of 
 * edit characters. This connection itself is established in
 * ctl.c
 */

#include "talk.h"
I 2
#include <sys/ioctl.h>
E 2
D 4
#include <stdio.h>
#include <errno.h>
E 4
#include <sys/time.h>
I 4
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
E 4

#define A_LONG_TIME 10000000
#define STDIN_MASK (1<<fileno(stdin))	/* the bit mask for standard
					   input */
extern int errno;

/*
 * The routine to do the actual talking
 */
I 4
void
E 4
talk()
{
	register int read_template, sockt_mask;
	int read_set, nb;
	char buf[BUFSIZ];
	struct timeval wait;

	message("Connection established\007\007\007");
	current_line = 0;
	sockt_mask = (1<<sockt);

	/*
	 * Wait on both the other process (sockt_mask) and 
	 * standard input ( STDIN_MASK )
	 */
	read_template = sockt_mask | STDIN_MASK;
	forever {
		read_set = read_template;
		wait.tv_sec = A_LONG_TIME;
		wait.tv_usec = 0;
D 4
		nb = select(32, &read_set, 0, 0, &wait);
E 4
I 4
		nb = select(32, (fd_set *)&read_set, 0, 0, &wait);
E 4
		if (nb <= 0) {
			if (errno == EINTR) {
				read_set = read_template;
				continue;
			}
			/* panic, we don't know what happened */
			p_error("Unexpected error from select");
			quit();
		}
		if (read_set & sockt_mask) { 
			/* There is data on sockt */
			nb = read(sockt, buf, sizeof buf);
			if (nb <= 0) {
				message("Connection closed. Exiting");
				quit();
			}
			display(&his_win, buf, nb);
		}
		if (read_set & STDIN_MASK) {
			/*
			 * We can't make the tty non_blocking, because
			 * curses's output routines would screw up
			 */
			ioctl(0, FIONREAD, (struct sgttyb *) &nb);
			nb = read(0, buf, nb);
			display(&my_win, buf, nb);
			/* might lose data here because sockt is non-blocking */
			write(sockt, buf, nb);
		}
	}
}

extern	int errno;
D 4
extern	int sys_nerr;
extern	char *sys_errlist[];
E 4

/*
 * p_error prints the system error message on the standard location
 * on the screen and then exits. (i.e. a curses version of perror)
 */
I 4
__dead void
E 4
p_error(string) 
D 4
	char *string;
E 4
I 4
	const char *string;
E 4
{
	char *sys;

D 4
	sys = "Unknown error";
	if (errno < sys_nerr)
		sys = sys_errlist[errno];
E 4
I 4
	sys = strerror(errno);
E 4
	wmove(my_win.x_win, current_line%my_win.x_nlines, 0);
	wprintw(my_win.x_win, "[%s : %s (%d)]\n", string, sys, errno);
	wrefresh(my_win.x_win);
	move(LINES-1, 0);
	refresh();
	quit();
}

/*
 * Display string in the standard location
 */
I 4
void
E 4
message(string)
D 4
	char *string;
E 4
I 4
	const char *string;
E 4
{

	wmove(my_win.x_win, current_line%my_win.x_nlines, 0);
	wprintw(my_win.x_win, "[%s]\n", string);
	wrefresh(my_win.x_win);
}
E 1
