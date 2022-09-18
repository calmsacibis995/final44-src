h03932
s 00002/00002/00032
d D 8.1 93/05/31 17:45:48 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00033
d D 5.4 90/06/01 13:15:22 bostic 4 3
c new copyright notice
e
s 00010/00005/00034
d D 5.3 88/06/18 20:04:48 bostic 3 2
c install approved copyright notice
e
s 00009/00003/00030
d D 5.2 88/03/09 11:18:45 bostic 2 1
c Written by Ken Arnold; add Berkeley specific copyright
e
s 00033/00000/00000
d D 5.1 85/05/30 18:35:43 mckusick 1 0
c date and time created 85/05/30 18:35:43 by mckusick
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
 * query:
 *	Ask a question and get a yes or no answer.  Default is "no".
 */
query(prompt)
char	*prompt;
{
	register int	c, retval;
	register int	y, x;

	getyx(stdscr, y, x);
	move(Y_PROMPT, X_PROMPT);
	addstr(prompt);
	clrtoeol();
	refresh();
	retval = ((c = getchar()) == 'y' || c == 'Y');
	move(Y_PROMPT, X_PROMPT);
	clrtoeol();
	move(y, x);
	return retval;
}
E 1
