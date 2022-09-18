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
 *	Scroll for simple forward and reverse scrolling in a window.
 *	This procedure is used internally.
 *
 */

void
wscroll (Winner, x)
struct window *Winner;
int     x;
{
	register int	index;
	register int    i;
	register int    j;
	register CHAR   *cpx1;
	CHAR   *tpx[NSCRLIN];
	int     Topy;
	int     Boty;
	int     lines;

	w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);

	Topy = Winner -> _top_y;
	Boty = Winner -> _bot_y;
	lines = Winner -> _bot_x - Winner -> _top_x;

	if (x < 0)
	{
		x = -x;
		for (index = 0; index < lines; index++)
			tpx[index] = Winner -> _map[index];

		for (index = 0, j = lines - 1; index < (lines - x); j--, index++)
		{
			Winner -> _map[j] = Winner -> _map[j - x];
		}

		for (index = 0, j = lines - x; x; index++, j++, x--)
		{
			cpx1 = Winner -> _map[index] = tpx[j];
			for (i = Topy; i < Boty; i++)
			{
				*cpx1++ = ' ';
			}
		}
		return;
	}

	if (x > 0)
	{
		for (index = 0; index < lines; index++)
			tpx[index] = Winner -> _map[index];

		for (index = 0; index < (lines - x) ; index++)
		{
			Winner -> _map[index] = Winner -> _map[index + x];
		}

		for (index = 0, j = lines - 1; x; index++, j--, x--)
		{
			cpx1 = Winner -> _map[j] = tpx[index];
			for (i = Topy; i < Boty; i++)
			{
				*cpx1++ = ' ';
			}
		}
	}
}
