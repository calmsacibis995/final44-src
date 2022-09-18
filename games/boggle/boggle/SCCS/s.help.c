h34001
s 00002/00002/00073
d D 8.1 93/06/11 14:47:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00075
d D 5.3 93/06/11 14:47:39 bostic 4 2
c fix the keywords
e
s 00030/00004/00071
d R 8.1 93/06/11 14:45:30 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00008/00056
d D 5.2 93/06/11 14:43:56 bostic 2 1
c integrate into 4.4BSD
e
s 00064/00000/00000
d D 5.1 93/06/10 11:09:46 bostic 1 0
c date and time created 93/06/10 11:09:46 by bostic
e
u
U
t
T
I 1
D 2
/* vi: set tabstop=4 : */
E 2
I 2
/*-
D 5
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Barry Brachman.
 *
 * %sccs.include.redist.c%
 */
E 2

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
#include <curses.h>
#include <stdio.h>

#include "bog.h"
I 2
#include "extern.h"
E 2

I 2
int
E 2
help()
{
I 2
	extern int nlines;
E 2
	int eof, i;
	FILE *fp;
	WINDOW *win;
	char buf[BUFSIZ];
D 2
	extern int ncols, nlines;
E 2

D 2
	if ((fp = fopen(HELPFILE, "r")) == (FILE *) NULL)
E 2
I 2
	if ((fp = fopen(HELPFILE, "r")) == NULL)
E 2
		return(-1);
	win = newwin(0, 0, 0, 0);
	clearok(win, 1);

	eof = 0;
	if (ungetc(getc(fp), fp) == EOF) {
		wprintw(win, "There doesn't seem to be any help.");
		eof = 1;			/* Nothing there... */
	}

	while (!eof) {
		for (i = 0; i < nlines - 3; i++) {
			if (fgets(buf, sizeof(buf), fp) == (char *) NULL) {
				eof = 1;
				break;
			}
			if (buf[0] == '.' && buf[1] == '\n')
				break;
			wprintw(win, "%s", buf);
		}
		if (eof || ungetc(getc(fp), fp) == EOF) {
			eof = 1;
			break;
		}
		wmove(win, nlines - 1, 0);
D 2
		wprintw(win, "Type <space> to continue, anything else to quit...");
E 2
I 2
		wprintw(win,
		    "Type <space> to continue, anything else to quit...");
E 2
		wrefresh(win);
		if ((inputch() & 0177) != ' ')
			break;
		wclear(win);
	}

	fclose(fp);
	if (eof) {
D 2
		extern char *version;

		wprintw(win, "%s", version);
E 2
		wmove(win, nlines - 1, 0);
		wprintw(win, "Hit any key to continue...");
		wrefresh(win);
		inputch();
	}
	delwin(win);
	clearok(stdscr, 1);
	refresh();
	return(0);
}
D 2

E 2
E 1
