h25696
s 00002/00002/00044
d D 8.1 93/05/31 17:23:08 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00043
d D 5.4 91/04/08 17:58:10 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00054
d D 5.3 90/01/02 14:09:07 bostic 3 2
c extract absolute pathnames
e
s 00011/00006/00045
d D 5.2 88/06/18 14:44:44 bostic 2 1
c install approved copyright notice
e
s 00051/00000/00000
d D 5.1 87/12/22 13:08:10 bostic 1 0
c date and time created 87/12/22 13:08:10 by bostic
e
u
U
t
T
I 1
D 4
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
E 2
I 2
 * Copyright (c) 1983 Regents of the University of California.
E 4
I 4
/*-
D 5
 * Copyright (c) 1983 The Regents of the University of California.
E 4
E 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"hangman.h"

/*
 * setup:
 *	Set up the strings on the screen.
 */
setup()
{
	register char		**sp;
	static struct stat	sbuf;

	noecho();
	crmode();

	mvaddstr(PROMPTY, PROMPTX, "Guess:");
	mvaddstr(GUESSY, GUESSX, "Guessed:");
	mvaddstr(NUMBERY, NUMBERX, "Word #:");
	mvaddstr(AVGY, AVGX, "Current Average:");
	mvaddstr(AVGY + 1, AVGX, "Overall Average:");
	mvaddstr(KNOWNY, KNOWNX, "Word: ");

	for (sp = Noose_pict; *sp != NULL; sp++) {
		move(sp - Noose_pict, 0);
		addstr(*sp);
	}

	srand(time(NULL) + getpid());
D 3
	if ((Dict = fopen(DICT, "r")) == NULL) {
		perror(DICT);
E 3
I 3
	if ((Dict = fopen(_PATH_DICT, "r")) == NULL) {
		perror(_PATH_DICT);
E 3
		endwin();
		exit(1);
	}
	fstat(fileno(Dict), &sbuf);
	Dict_size = sbuf.st_size;
}
E 1
