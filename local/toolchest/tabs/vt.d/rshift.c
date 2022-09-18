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

/* rshift -- right shift the screen to account for insert character */

rshift (line, col, x)
int     line;				/* effected line */
int     col;				/* column to start in */
register        x;			/* displaced character */
					/* that goes in col */
{
	int     y;
	int     jnk;
	register CHAR  *stop;
	register CHAR  *lp;

	lp = cmap[line];
	jnk = scrjnk[line];
	if (jnk <= SCRWID)
		lp[jnk] = 0;

	stop = lp + SCRWID;
	lp += col;

	while (x && (lp <= stop))
	{
		y = *lp;
		*lp++ = x;
		x = y;
	}
	if (IN)
	{
		y = lp - cmap[line];
		if (y > jnk)
			jnk = y;
		if (x)
			rshift (line + 1, 0, x);
	}
	else
	{
		if (jnk < SCRWID)
			jnk++;
	}
	scrjnk[line] = jnk;
	return (jnk);
}
