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
 *	Partial window scoll for line insert and delete from a subprocess
 *	This currently does use yt, xb, yb args.  The routines wshift,
 *	wscroll, and xwscroll will eventually be combined.
 *	This procedure is only used internally.
 *
 */
xwscroll (Winner, xt, x)
register struct window *Winner;
int     xt;
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
	int     diff;
	extern struct window   *C_window;

	w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);
	C_window = Winner;

	lines = Winner -> _bot_x - xt;
	diff = xt - Winner -> _top_x;
	Topy = Winner -> _top_y;
	Boty = Winner -> _bot_y;

	if (x < 0)
	{
		x = -x;
		for (index = 0; index < (lines + diff); index++)
			tpx[index] = Winner -> _map[index];

		for (index = 0, j = diff + lines - 1; index < (lines - x); j--, index++)
		{
			Winner -> _map[j] = Winner -> _map[j - x];
		}

		for (index = xt - Winner -> _top_x, j = diff + lines - x; x; index++, j++, x--)
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
		for (index = 0; index < (diff + lines); index++)
			tpx[index] = Winner -> _map[index];

		for (index = xt - Winner -> _top_x; index < (diff + lines - x); index++)
		{
			Winner -> _map[index] = Winner -> _map[index + x];
		}

		for (index = xt - Winner -> _top_x, j = diff + lines - 1; x; index++, j--, x--)
		{
			cpx1 = Winner -> _map[j] = tpx[index];
			for (i = Topy; i < Boty; i++)
			{
				*cpx1++ = ' ';
			}
		}
	}

}
