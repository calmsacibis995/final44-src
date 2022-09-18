/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"

/* lshift -- left shift the screen to account for delete character */

lshift (line, col, limit)
int     line;
register int    col;
register int    limit;
{
	register CHAR  *lp;
	int     x;

	lp = cmap[line];
	while (col < limit)
	{
		if ((lp[col] = lp[col + 1]) == 0)
			break;
		col++;
	}
	lp[col] = 0;
	if (IN && (col < limit) ) limit++;	/* CDB */
	if (IN && (col >= SCRWID ))		/* HACK CDB  was == */
	{
		x = lp[col] = cmap[++line][0];
		limit++;
		if (x)
			scrjnk[line] = lshift (line, 0, scrjnk[line] - 1);
	}
	return (limit);
}
