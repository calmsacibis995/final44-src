h27277
s 00002/00002/00114
d D 8.1 93/06/06 16:31:38 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00111
d D 5.8 93/02/04 15:38:52 elan 10 9
c Fixed message() so that it works correctly. (no '\n''s).
e
s 00002/00001/00112
d D 5.7 92/08/31 10:58:37 elan 9 8
c 
e
s 00001/00001/00112
d D 5.6 91/03/01 19:06:10 bostic 8 7
c ANSI, local include files shouldn't include include files
e
s 00001/00011/00112
d D 5.5 90/06/01 17:44:13 bostic 7 6
c new copyright notice
e
s 00004/00009/00119
d D 5.4 90/05/28 12:50:47 bostic 6 5
c sys_errlist -> strerror(3)
e
s 00010/00005/00118
d D 5.3 88/06/29 20:22:24 bostic 5 4
c install approved copyright notice
e
s 00009/00003/00114
d D 5.2 88/05/20 12:37:08 bostic 4 3
c add Berkeley specific header
e
s 00007/00001/00110
d D 5.1 85/06/06 09:18:42 dist 3 2
c Add copyright
e
s 00075/00093/00036
d D 1.2 84/04/11 15:14:13 karels 2 1
c reformatting; convert daemon for inetd; add keywords
e
s 00129/00000/00000
d D 1.1 84/04/11 15:02:57 karels 1 0
c date and time created 84/04/11 15:02:57 by karels
e
u
U
t
T
I 3
/*
D 11
 * Copyright (c) 1983 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
E 4
 */

E 3
I 1
D 2
/* $Header: /a/guest/moore/talk/RCS/io.c,v 1.3 83/07/06 00:17:15 moore Exp $ */
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 3
E 2

D 2
/* this file contains the I/O handling and the exchange of 
   edit characters. This connection itself is established in
   ctl.c
E 2
I 2
/*
 * This file contains the I/O handling and the exchange of 
 * edit characters. This connection itself is established in
 * ctl.c
E 2
 */

I 9
#include <sys/ioctl.h>
E 9
I 6
#include <sys/time.h>
E 6
D 9
#include "talk.h"
E 9
#include <stdio.h>
#include <errno.h>
D 6
#include <sys/time.h>
E 6
I 6
#include <string.h>
I 9
#include "talk.h"
E 9
E 6

#define A_LONG_TIME 10000000
#define STDIN_MASK (1<<fileno(stdin))	/* the bit mask for standard
					   input */
D 6
extern int errno;
E 6

/*
 * The routine to do the actual talking
 */
D 2

E 2
talk()
{
D 2
    register int read_template, sockt_mask;
    int read_set, nb;
    char buf[BUFSIZ];
    struct timeval wait;
E 2
I 2
	register int read_template, sockt_mask;
	int read_set, nb;
	char buf[BUFSIZ];
	struct timeval wait;
E 2

D 2
    message("Connection established\007\007\007");
    current_line = 0;
E 2
I 2
	message("Connection established\007\007\007");
	current_line = 0;
	sockt_mask = (1<<sockt);
E 2

D 2
    sockt_mask = (1<<sockt);

E 2
	/*
D 2
	 * wait on both the other process (sockt_mask) and 
E 2
I 2
	 * Wait on both the other process (sockt_mask) and 
E 2
	 * standard input ( STDIN_MASK )
	 */
D 2

    read_template = sockt_mask | STDIN_MASK;

    forever {

	read_set = read_template;

	wait.tv_sec = A_LONG_TIME;
	wait.tv_usec = 0;

	nb = select(32, &read_set, 0, 0, &wait);

	if (nb <= 0) {

		/* We may be returning from an interupt handler */

	    if (errno == EINTR) {
E 2
I 2
	read_template = sockt_mask | STDIN_MASK;
D 8
	forever {
E 8
I 8
	for (;;) {
E 8
E 2
		read_set = read_template;
D 2
		continue;
	    } else {
		    /* panic, we don't know what happened */
		p_error("Unexpected error from select");
		quit();
	    }
E 2
I 2
		wait.tv_sec = A_LONG_TIME;
		wait.tv_usec = 0;
		nb = select(32, &read_set, 0, 0, &wait);
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
E 2
	}
D 2

	if ( read_set & sockt_mask ) { 

		/* There is data on sockt */
	    nb = read(sockt, buf, sizeof buf);

	    if (nb <= 0) {
		message("Connection closed. Exiting");
		quit();
	    } else {
		display(&his_win, buf, nb);
	    }
	}
	
	if ( read_set & STDIN_MASK ) {

		/* we can't make the tty non_blocking, because
		   curses's output routines would screw up */

	    ioctl(0, FIONREAD, (struct sgttyb *) &nb);
	    nb = read(0, buf, nb);

	    display(&my_win, buf, nb);
	    write(sockt, buf, nb);	/* We might lose data here
					   because sockt is non-blocking
					 */

	}
    }
E 2
}

D 2
extern int	errno;
extern int	sys_nerr;
extern char	*sys_errlist[];
E 2
I 2
extern	int errno;
extern	int sys_nerr;
D 6
extern	char *sys_errlist[];
E 6
E 2

D 2
    /* p_error prints the system error message on the standard location
       on the screen and then exits. (i.e. a curses version of perror)
     */

E 2
I 2
/*
 * p_error prints the system error message on the standard location
 * on the screen and then exits. (i.e. a curses version of perror)
 */
E 2
p_error(string) 
D 2
char *string;
E 2
I 2
	char *string;
E 2
{
D 2
    char *sys;
E 2
I 2
D 6
	char *sys;
E 2

D 2
    sys = "Unknown error";
    if(errno < sys_nerr) {
	sys = sys_errlist[errno];
    }


    wmove(my_win.x_win, current_line%my_win.x_nlines, 0);
    wprintw(my_win.x_win, "[%s : %s (%d)]\n", string, sys, errno);
    wrefresh(my_win.x_win);
    move(LINES-1, 0);
    refresh();
    quit();
E 2
I 2
	sys = "Unknown error";
	if (errno < sys_nerr)
		sys = sys_errlist[errno];
E 6
	wmove(my_win.x_win, current_line%my_win.x_nlines, 0);
D 6
	wprintw(my_win.x_win, "[%s : %s (%d)]\n", string, sys, errno);
E 6
I 6
	wprintw(my_win.x_win, "[%s : %s (%d)]\n",
	    string, strerror(errno), errno);
E 6
	wrefresh(my_win.x_win);
	move(LINES-1, 0);
	refresh();
	quit();
E 2
}

D 2
    /* display string in the standard location */

E 2
I 2
/*
 * Display string in the standard location
 */
E 2
message(string)
D 2
char *string;
E 2
I 2
	char *string;
E 2
{
D 2
    wmove(my_win.x_win, current_line%my_win.x_nlines, 0);
    wprintw(my_win.x_win, "[%s]\n", string);
    wrefresh(my_win.x_win);
E 2
I 2
D 10

	wmove(my_win.x_win, current_line%my_win.x_nlines, 0);
	wprintw(my_win.x_win, "[%s]\n", string);
E 10
I 10
	wmove(my_win.x_win, current_line % my_win.x_nlines, 0);
	wprintw(my_win.x_win, "[%s]", string);
	wclrtoeol(my_win.x_win);
	current_line++;
	wmove(my_win.x_win, current_line % my_win.x_nlines, 0);
E 10
	wrefresh(my_win.x_win);
E 2
}
E 1
