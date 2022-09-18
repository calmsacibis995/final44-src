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
#include "windows.h"

/*
 *
 *	Window based shift - currently for Concepts and Blits/etty Only
 *	The routines wshift, wscroll, and xwscroll will eventually be combined.
 *	This procedure is only used internally.
 *
 */

void
wshift (top, ytop, bottom, ybot, x)
int     top;
int     ytop;
int     bottom;
int     ybot;
int     x;
{
	register int    i;
	register int    j;
	register CHAR   *cp1;
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
		cp1 = &cmap[i][ytop];
		cp2 = &cmap[i + x][ytop];
		for (j = ytop; j <= ybot; j++, cp1++, cp2++)
		{
			*cp1 = *cp2;
			if (IN) *cp2 = '\0';
			else *cp2 = ' ';
		}
	}
	while (i != stop)
	{
		cp1 = cmap[i];
		*jnkptr = 0;
		for (j = 0; j < SCRWID + 1; j++, cp1++)
		{
			if ((*cp1 != ' ') && (*cp1 != '\0'))
				*jnkptr = j + 1;
		}
		if (off > 0)
		{
			jnkptr++;
			i++;
		}
		else
		{
			jnkptr--;
			i--;
		}
	}
}
