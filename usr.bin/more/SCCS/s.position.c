h43641
s 00002/00002/00135
d D 8.1 93/06/06 15:37:17 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00012/00136
d D 5.7 90/06/01 17:04:50 bostic 7 6
c new copyright notice
e
s 00002/00002/00146
d D 5.6 90/02/27 00:39:57 donn 6 5
c Purest laziness.
e
s 00011/00002/00137
d D 5.5 90/02/26 21:30:05 donn 5 4
c Support screens of more than 100 lines.  This fix stops the problem of
c more exiting after the first screen when the screen in 101 lines or longer.
e
s 00011/00000/00128
d D 5.4 88/12/13 21:58:37 bostic 4 3
c if a short file, don't move to lower-left corner of the screen,
c unless editing or movement attempted, including at exit.  Correct dumb
c mistake in window signal handling.  Add routine to copy portions of the table.
e
s 00008/00012/00120
d D 5.3 88/11/22 16:51:44 bostic 3 2
c less -> more
e
s 00002/00004/00130
d D 5.2 88/07/25 12:05:13 bostic 2 1
c update copyright notice
e
s 00134/00000/00000
d D 5.1 88/07/21 18:53:19 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 8
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 2
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 2
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 2
 * by the University of California, Berkeley.  The name of the
E 2
I 2
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 2
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Routines dealing with the "position" table.
 * This is a table which tells the position (in the input file) of the
 * first char on each currently displayed line.
 *
 * {{ The position table is scrolled by moving all the entries.
 *    Would be better to have a circular table 
 *    and just change a couple of pointers. }}
 */

D 3
#include "less.h"
#include "position.h"
E 3
I 3
#include <sys/types.h>
#include <less.h>
E 3

D 5
#define	NPOS	100		/* {{ sc_height must be less than NPOS }} */
D 3
static POSITION table[NPOS];	/* The position table */
E 3
I 3
static off_t table[NPOS];	/* The position table */
E 5
I 5
static off_t *table;		/* The position table */
static int tablesize;
E 5
E 3

D 3
extern int sc_width, sc_height;
E 3
I 3
extern int sc_height;
E 3

/*
 * Return the starting file position of a line displayed on the screen.
 * The line may be specified as a line number relative to the top
 * of the screen, but is usually one of these special cases:
 *	the top (first) line on the screen
 *	the second line on the screen
 *	the bottom line on the screen
 *	the line after the bottom line on the screen
 */
D 3
	public POSITION
E 3
I 3
off_t
E 3
position(where)
	int where;
{
	switch (where)
	{
	case BOTTOM:
		where = sc_height - 2;
		break;
	case BOTTOM_PLUS_ONE:
		where = sc_height - 1;
		break;
	case MIDDLE:
		where = sc_height / 2;
	}
	return (table[where]);
}

/*
 * Add a new file position to the bottom of the position table.
 */
D 3
	public void
E 3
add_forw_pos(pos)
D 3
	POSITION pos;
E 3
I 3
	off_t pos;
E 3
{
	register int i;

	/*
	 * Scroll the position table up.
	 */
	for (i = 1;  i < sc_height;  i++)
		table[i-1] = table[i];
	table[sc_height - 1] = pos;
}

/*
 * Add a new file position to the top of the position table.
 */
D 3
	public void
E 3
add_back_pos(pos)
D 3
	POSITION pos;
E 3
I 3
	off_t pos;
E 3
{
	register int i;

	/*
	 * Scroll the position table down.
	 */
	for (i = sc_height - 1;  i > 0;  i--)
		table[i] = table[i-1];
	table[0] = pos;
}

I 4
copytable()
{
	register int a, b;

	for (a = 0; a < sc_height && table[a] == NULL_POSITION; a++);
	for (b = 0; a < sc_height; a++, b++) {
		table[b] = table[a];
		table[a] = NULL_POSITION;
	}
}

E 4
/*
 * Initialize the position table, done whenever we clear the screen.
 */
D 3
	public void
E 3
pos_clear()
{
	register int i;
I 5
	extern char *malloc(), *realloc();

	if (table == 0) {
		tablesize = sc_height > 25 ? sc_height : 25;
D 6
		table = malloc(tablesize * sizeof *table);
E 6
I 6
		table = (off_t *)malloc(tablesize * sizeof *table);
E 6
	} else if (sc_height >= tablesize) {
		tablesize = sc_height;
D 6
		table = realloc(table, tablesize * sizeof *table);
E 6
I 6
		table = (off_t *)realloc(table, tablesize * sizeof *table);
E 6
	}
E 5

	for (i = 0;  i < sc_height;  i++)
		table[i] = NULL_POSITION;
}

/*
 * See if the byte at a specified position is currently on the screen.
 * Check the position table to see if the position falls within its range.
 * Return the position table entry if found, -1 if not.
 */
D 3
	public int
E 3
onscreen(pos)
D 3
	POSITION pos;
E 3
I 3
	off_t pos;
E 3
{
	register int i;

	if (pos < table[0])
		return (-1);
	for (i = 1;  i < sc_height;  i++)
		if (pos < table[i])
			return (i-1);
	return (-1);
}
E 1
