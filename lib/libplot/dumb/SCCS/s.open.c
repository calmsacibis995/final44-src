h43713
s 00002/00002/00058
d D 8.1 93/06/04 17:31:43 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00054
d D 5.3 91/04/22 14:59:37 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00058
d D 5.2 91/02/24 15:44:10 bostic 3 2
c Add include files to get prototype declarations, and fix bugs found.
e
s 00007/00001/00052
d D 5.1 85/05/07 11:40:08 dist 2 1
c Add copyright notice
e
s 00053/00000/00000
d D 4.1 83/11/10 11:54:43 ralph 1 0
c date and time created 83/11/10 11:54:43 by ralph
e
u
U
t
T
I 2
D 4
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
/*-
D 5
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
E 4
 */

E 2
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif
E 2
I 2
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 2

/*
 * This accepts plot file formats and produces the appropriate plots
 * for dumb terminals.  It can also be used for printing terminals and
 * lineprinter listings, although there is no way to specify number of
 * lines and columns different from your terminal.  This would be easy
 * to change, and is left as an exercise for the reader.
 */

#include <signal.h>
#include "dumb.h"

int minX, rangeX;	/* min and range of x */
int minY, rangeY;	/* min and range of y */
int currentx,currenty;
int COLS,LINES;

/* A very large screen! (probably should use malloc) */
char screenmat[MAXCOLS][MAXLINES];

openpl()
{
D 3
	int closepl();
E 3
I 3
	void closepl();
E 3
	int i, j;
	char *term, *getenv();
	char bp[1024];

	term = getenv("TERM");
	tgetent(bp, term);

	COLS = tgetnum("co");
	if (COLS > MAXCOLS)
		COLS = MAXCOLS;
	if (COLS < 0)
		COLS = 48;	/* lower bound on # of cols? */
	COLS--;				/* prevent auto wrap */

	LINES = tgetnum("li");
	if (LINES > MAXLINES)
		LINES = MAXLINES;
	if (LINES < 0)
		LINES = 20;	/* lower bound on # of lines? */

	for(i=0; i<COLS; i++)
		for(j=0; j<LINES; j++)
			screenmat[i][j] = ' ';

	signal(SIGINT, closepl);
	currentx = currenty = 0;
}
E 1
