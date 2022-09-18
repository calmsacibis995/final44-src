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

/* vshift -- shift the display image from top to bottom (inclusive) by x */

vshift (top, bottom, x)
int     top;
int     bottom;
int     x;
{
	register int    i;
	register int    j;
	CHAR   *cp1;
	CHAR   *cp2;
	int    *jnkptr;
	int     start;
	int     stop;
	register int    off;

	if (x > 0)
	{
		off = 1;
		start = top;
		stop = bottom + 1;
	}
	else
	{
		off = -1;
		start = bottom;
		stop = top - 1;
	}
	for (i = start, jnkptr = scrjnk + i;
			i != stop - x;
			i += off, jnkptr += off)
	{
		*jnkptr = *(jnkptr + x);
		cp1 = cmap[i];
		cp2 = cmap[i + x];
		for (j = 0; j < *jnkptr; j++)
		{
			*cp1++ = *cp2++;
		}
	}
	while (i != stop)
	{
		if (off > 0)
		{
			*jnkptr++ = 0;
			i++;
		}
		else
		{
			*jnkptr-- = 0;
			i--;
		}
	}
}
