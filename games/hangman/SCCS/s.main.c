h17820
s 00005/00005/00044
d D 8.1 93/05/31 17:22:51 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00046
d D 5.4 91/02/28 13:14:11 bostic 4 3
c ANSI
e
s 00001/00011/00045
d D 5.3 90/06/01 13:07:20 bostic 3 2
c new copyright notice
e
s 00012/00007/00044
d D 5.2 88/06/18 14:44:38 bostic 2 1
c install approved copyright notice
e
s 00051/00000/00000
d D 5.1 87/12/22 13:08:08 bostic 1 0
c date and time created 87/12/22 13:08:08 by bostic
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
D 5
char copyright[] =
D 2
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 2
I 2
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 2
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"hangman.h"

/*
 * This game written by Ken Arnold.
 */
main()
{
I 4
	void die();

E 4
	initscr();
	signal(SIGINT, die);
	setup();
	for (;;) {
		Wordnum++;
		playgame();
		Average = (Average * (Wordnum - 1) + Errors) / Wordnum;
	}
	/* NOTREACHED */
}

/*
 * die:
 *	Die properly.
 */
I 4
void
E 4
die()
{
	mvcur(0, COLS - 1, LINES - 1, 0);
	endwin();
	putchar('\n');
	exit(0);
}
E 1
