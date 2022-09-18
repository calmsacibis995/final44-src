h18142
s 00002/00002/00099
d D 8.1 93/06/11 14:48:12 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00009/00079
d D 5.2 93/06/11 14:43:59 bostic 2 1
c integrate into 4.4BSD
e
s 00088/00000/00000
d D 5.1 93/06/10 11:09:51 bostic 1 0
c date and time created 93/06/10 11:09:51 by bostic
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
D 3
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Barry Brachman.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2

#include <curses.h>

I 2
#include "extern.h"

E 2
#define NCOLS	5

D 2
static int get_maxlen();
E 2
I 2
static int	get_maxlen __P((char *[], int, int (*)(char **, int)));
E 2

/*
 * Routine to print a table
 * Modified from 'ls.c' mods (BJB/83)
 * Arguments:
 *	base	- address of first entry
 *	num     - number of entries
 *	d_cols  - number of columns to use if > 0, "best" size if == 0
 *	width	- max line width if not zero
 *	prentry - address of the routine to call to print the string
 *	length  - address of the routine to call to determine the length
 *		  of string to be printed 
 *
 * prtable and length are called with the the address of the base and
 * an index
 */
I 2
void
E 2
prtable(base, num, d_cols, width, prentry, length)
D 2
char *base;
int num, d_cols;
int (*prentry)(), (*length)();
E 2
I 2
	char *base[];
	int num, d_cols, width;
	void (*prentry) __P((char *[], int));
	int (*length) __P((char *[], int));
E 2
{
        register int c, j;
        register int a, b, cols, loc, maxlen, nrows, z;
	int col, row;

        if (num == 0)
                return;
	maxlen = get_maxlen(base, num, length) + 1;
	if (d_cols > 0)
		cols = d_cols;
	else
		cols = width / maxlen;
	if (cols == 0)
		cols = NCOLS;
        nrows = (num - 1) / cols + 1;
        for (a = 1; a <= nrows; a++) {
                b = c = z = loc = 0;
                for (j = 0; j < num; j++) {
                        c++;
                        if (c >= a + b)
                                break;
                }
                while (j < num) {
                        (*prentry)(base, j);
			loc += (*length)(base, j);
                        z++;
                        b += nrows;
                        for (j++; j < num; j++) {
                                c++;
                                if (c >= a + b)
                                        break;
                        }
                        if (j < num) {
                                while (loc < z * maxlen) {
					addch(' ');
                                        loc++;
                                }
			}
                }
		getyx(stdscr, row, col);
		move(row + 1, 0);
        }
	refresh();
}

static int
get_maxlen(base, num, length)
D 2
char *base;
int num;
int (*length)();
E 2
I 2
	char *base[];
	int num;
	int (*length) __P((char **, int));
E 2
{
	register int i, len, max;

	max = (*length)(base, 0);
	for (i = 0; i < num; i++) {
		if ((len = (*length)(base, i)) > max)
			max = len;
	}
	return(max);
}
D 2

E 2
E 1
