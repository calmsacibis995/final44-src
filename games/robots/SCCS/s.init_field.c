h58384
s 00002/00002/00089
d D 8.1 93/05/31 17:45:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00090
d D 5.4 90/06/01 13:14:34 bostic 4 3
c new copyright notice
e
s 00010/00005/00091
d D 5.3 88/06/18 20:04:39 bostic 3 2
c install approved copyright notice
e
s 00009/00003/00087
d D 5.2 88/03/09 11:18:37 bostic 2 1
c Written by Ken Arnold; add Berkeley specific copyright
e
s 00090/00000/00000
d D 5.1 85/05/30 18:33:55 mckusick 1 0
c date and time created 85/05/30 18:33:55 by mckusick
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1980 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

# include	"robots.h"

/*
 * init_field:
 *	Lay down the initial pattern whih is constant across all levels,
 *	and initialize all the global variables.
 */
init_field()
{
	register int	i;
	register WINDOW	*wp;
	register int	j;
	static bool	first = TRUE;
	static char	*desc[] = {
				"Directions:",
				"",
				"y k u",
				" \\|/",
				"h- -l",
				" /|\\",
				"b j n",
				"",
				"Commands:",
				"",
				"w:  wait for end",
				"t:  teleport",
				"q:  quit",
				"^L: redraw screen",
				"",
				"Legend:",
				"",
				"+:  robot",
				"*:  junk heap",
				"@:  you",
				"",
				"Score: 0",
				NULL
	};

	Dead = FALSE;
	Waiting = FALSE;
	flushok(stdscr, TRUE);
	Score = 0;

	erase();
	move(0, 0);
	addch('+');
	for (i = 1; i < Y_FIELDSIZE; i++) {
		move(i, 0);
		addch('|');
	}
	move(Y_FIELDSIZE, 0);
	addch('+');
	for (i = 1; i < X_FIELDSIZE; i++)
		addch('-');
	addch('+');
	if (first)
		refresh();
	move(0, 1);
	for (i = 1; i < X_FIELDSIZE; i++)
		addch('-');
	addch('+');
	for (i = 1; i < Y_FIELDSIZE; i++) {
		move(i, X_FIELDSIZE);
		addch('|');
	}
	if (first)
		refresh();
	for (i = 0; desc[i] != NULL; i++) {
		move(i, X_FIELDSIZE + 2);
		addstr(desc[i]);
	}
	if (first)
		refresh();
	first = FALSE;
#ifdef	FANCY
	if (Pattern_roll)
		Next_move = &Move_list[-1];
#endif
}
E 1
