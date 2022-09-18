h65080
s 00002/00002/00080
d D 8.1 93/05/31 17:22:41 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00081
d D 5.6 92/11/16 12:11:10 elan 6 5
c Changed to new data structures.
e
s 00002/00001/00080
d D 5.5 92/08/31 10:13:09 elan 5 4
c Added appropriate header files.
e
s 00001/00011/00080
d D 5.4 90/06/01 13:07:00 bostic 4 3
c new copyright notice
e
s 00011/00006/00080
d D 5.3 88/06/18 14:44:34 bostic 3 2
c install approved copyright notice
e
s 00002/00002/00084
d D 5.2 87/12/22 13:11:49 bostic 2 1
c ANSI C compatible
e
s 00086/00000/00000
d D 5.1 87/12/22 13:08:07 bostic 1 0
c date and time created 87/12/22 13:08:07 by bostic
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1987 Regents of the University of California.
E 3
I 3
D 7
 * Copyright (c) 1983 Regents of the University of California.
E 3
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
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
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 5
# include	"hangman.h"
E 5
I 5
#include <sys/ttydefaults.h>
#include "hangman.h"
E 5

/*
 * getguess:
 *	Get another guess
 */
getguess()
{
	register int	i;
	register int	ch;
	register bool	correct;

	leaveok(stdscr, FALSE);
	for (;;) {
		move(PROMPTY, PROMPTX + sizeof "Guess: ");
		refresh();
		ch = readch();
		if (isalpha(ch)) {
			if (isupper(ch))
				ch = tolower(ch);
			if (Guessed[ch - 'a'])
				mvprintw(MESGY, MESGX, "Already guessed '%c'", ch);
			else
				break;
		}
D 2
		else if (ch == CTRL(D))
E 2
I 2
		else if (ch == CTRL('D'))
E 2
			die();
		else
			mvprintw(MESGY, MESGX, "Not a valid guess: '%s'",
				unctrl(ch));
	}
	leaveok(stdscr, TRUE);
	move(MESGY, MESGX);
	clrtoeol();

	Guessed[ch - 'a'] = TRUE;
	correct = FALSE;
	for (i = 0; Word[i] != '\0'; i++)
		if (Word[i] == ch) {
			Known[i] = ch;
			correct = TRUE;
		}
	if (!correct)
		Errors++;
}

/*
 * readch;
 *	Read a character from the input
 */
readch()
{
	register int	cnt, r;
	auto char	ch;

	cnt = 0;
	for (;;) {
		if (read(0, &ch, sizeof ch) <= 0)
		{
			if (++cnt > 100)
				die();
		}
D 2
		else if (ch == CTRL(L)) {
E 2
I 2
		else if (ch == CTRL('L')) {
E 2
			wrefresh(curscr);
D 6
			mvcur(0, 0, curscr->_cury, curscr->_curx);
E 6
I 6
			mvcur(0, 0, curscr->cury, curscr->curx);
E 6
		}
		else
			return ch;
	}
}
E 1
