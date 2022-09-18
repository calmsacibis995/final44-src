h12851
s 00002/00002/00057
d D 8.1 93/05/31 17:22:35 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00001/00046
d D 5.4 93/02/03 17:30:05 elan 4 3
c Do not do addstr("\n\n\n") rather 3 deleteln
e
s 00001/00011/00046
d D 5.3 90/06/01 13:06:48 bostic 3 2
c new copyright notice
e
s 00011/00006/00046
d D 5.2 88/06/18 14:44:32 bostic 2 1
c install approved copyright notice
e
s 00052/00000/00000
d D 5.1 87/12/22 13:08:05 bostic 1 0
c date and time created 87/12/22 13:08:05 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
E 2
I 2
D 5
 * Copyright (c) 1983 Regents of the University of California.
E 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"hangman.h"

/*
 * endgame:
 *	Do what's necessary at the end of the game
 */
endgame()
{
	register char	ch;

	prman();
	if (Errors >= MAXERRS)
		Errors = MAXERRS + 2;
	prword();
	prdata();
	move(MESGY, MESGX);
	if (Errors > MAXERRS)
		printw("Sorry, the word was \"%s\"\n", Word);
	else
		printw("You got it!\n");

	for (;;) {
		mvaddstr(MESGY + 1, MESGX, "Another word? ");
		leaveok(stdscr, FALSE);
		refresh();
		if ((ch = readch()) == 'n')
			die();
		else if (ch == 'y')
			break;
		mvaddstr(MESGY + 2, MESGX, "Please type 'y' or 'n'");
	}

	leaveok(stdscr, TRUE);
	move(MESGY, MESGX);
D 4
	addstr("\n\n\n");
E 4
I 4
	deleteln();
	deleteln();
	deleteln();
E 4
}
I 4










E 4
E 1
