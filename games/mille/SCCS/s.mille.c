h35940
s 00005/00005/00132
d D 8.1 93/05/31 17:25:20 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00007/00137
d D 5.7 93/01/11 10:54:23 bostic 7 6
c doesn't even *use* CA, just checks for its existence!
e
s 00004/00004/00140
d D 5.6 92/03/08 10:01:30 torek 6 5
c exit with sensible code
e
s 00002/00001/00142
d D 5.5 91/02/28 14:11:22 bostic 5 4
c ANSI
e
s 00001/00011/00142
d D 5.4 90/06/01 13:07:52 bostic 4 3
c new copyright notice
e
s 00010/00005/00143
d D 5.3 88/06/18 19:38:23 bostic 3 2
c install approved copyright notice
e
s 00022/00021/00126
d D 5.2 87/12/29 17:12:31 bostic 2 1
c Berkeley header; comment out debugging code; remove setbuf call; 
c remove load average check; add setuid(getuid()) so save file permissions are 
c correct; minor lint cleanups
e
s 00147/00000/00000
d D 5.1 86/11/26 13:35:07 bostic 1 0
c date and time created 86/11/26 13:35:07 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
D 8
 * Copyright (c) 1982 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
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
I 2
D 8
char copyright[] =
"%Z% Copyright (c) 1982 Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1982, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */

#ifndef lint
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

# include	"mille.h"
# include	<signal.h>
# ifdef attron
#	include	<term.h>
# endif	attron

/*
 * @(#)mille.c	1.3 (Berkeley) 5/10/83
 */

D 5
int	rub();
E 5
I 5
void	rub();
E 5

D 2
char	_sobuf[BUFSIZ];

E 2
main(ac, av)
reg int		ac;
reg char	*av[]; {

	reg bool	restore;
D 2
	double		avs[3];
E 2

I 2
	/* run as the user */
	setuid(getuid());

E 2
	if (strcmp(av[0], "a.out") == 0) {
		outf = fopen("q", "w");
		setbuf(outf, (char *)NULL);
		Debug = TRUE;
	}
	restore = FALSE;
D 2
# ifdef LOADAV
	if (geteuid() != ARNOLD) {
		loadav(avs);
		if (avs[2] > 9.0) {
			printf("Sorry.  The load average is too high.\n");
			printf("Please try again later\n");
			exit(1);
		}
	}
# endif
E 2
	switch (ac) {
	  case 2:
		rest_f(av[1]);
		restore = TRUE;
	  case 1:
		break;
	  default:
		printf("usage: milles [ restore_file ]\n");
		exit(-1);
		/* NOTREACHED */
	}
D 2
	setbuf(stdout, _sobuf);
E 2
	Play = PLAYER;
	initscr();
D 7
# ifdef attron
#	define	CA	cursor_address
# endif
	if (!CA) {
		printf("Sorry.  Need cursor addressing to play mille\n");
		exit(-1);
	}
E 7
	delwin(stdscr);
	stdscr = Board = newwin(BOARD_Y, BOARD_X, 0, 0);
	Score = newwin(SCORE_Y, SCORE_X, 0, 40);
	Miles = newwin(MILES_Y, MILES_X, 17, 0);
#ifdef attron
	idlok(Board, TRUE);
	idlok(Score, TRUE);
	idlok(Miles, TRUE);
#endif
	leaveok(Score, TRUE);
	leaveok(Miles, TRUE);
	clearok(curscr, TRUE);
# ifndef PROF
	srandom(getpid());
# else
	srandom(0);
# endif
	crmode();
	noecho();
	signal(SIGINT, rub);
	for (;;) {
		if (!restore || (Player[PLAYER].total >= 5000
		    || Player[COMP].total >= 5000)) {
			if (Player[COMP].total < Player[PLAYER].total)
				Player[PLAYER].games++;
			else if (Player[COMP].total > Player[PLAYER].total)
				Player[COMP].games++;
			Player[COMP].total = 0;
			Player[PLAYER].total = 0;
		}
		do {
			if (!restore)
				Handstart = Play = other(Handstart);
			if (!restore || On_exit) {
				shuffle();
				init();
			}
			newboard();
			if (restore)
				mvwaddstr(Score, ERR_Y, ERR_X, Initstr);
			prboard();
			do {
				domove();
				if (Finished)
					newscore();
				prboard();
			} while (!Finished);
			check_more();
			restore = On_exit = FALSE;
		} while (Player[COMP].total < 5000
		    && Player[PLAYER].total < 5000);
	}
}

/*
 *	Routine to trap rubouts, and make sure they really want to
 * quit.
 */
I 5
void
E 5
rub() {

D 2
	signal(SIGINT, SIG_IGN);
E 2
I 2
	(void)signal(SIGINT, SIG_IGN);
E 2
	if (getyn(REALLYPROMPT))
D 6
		die();
E 6
I 6
		die(0);
E 6
D 2
	signal(SIGINT, rub);
E 2
I 2
	(void)signal(SIGINT, rub);
E 2
}

/*
 *	Time to go beddy-by
 */
D 6
die() {
E 6
I 6
die(code)
int code; {
E 6

D 2
	signal(SIGINT, SIG_IGN);
E 2
I 2
	(void)signal(SIGINT, SIG_IGN);
E 2
	if (outf)
		fflush(outf);
	mvcur(0, COLS - 1, LINES - 1, 0);
	endwin();
D 6
	exit(1);
E 6
I 6
	exit(code);
E 6
}
D 6

E 6
E 1
