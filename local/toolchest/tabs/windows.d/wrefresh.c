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
 *	Wrefresh (Winner)
 *
 *	This procedure updates the specified window.  Assumes that windows
 *	at depth >= INVISIBLE are assumed to be not visible.
 *
 */

void
Wrefresh (Winner)
register struct window *Winner;
{
	char    pbuf[NSCRCOL];
	register CHAR  *xmap;
	register CHAR  *omap;
	register char  *p;
	register int    k;
	int     mode;
	int     i;
	int     j;
	int     x;
	int     y;
	int	changed;

	W_Ok (Winner, "wrefresh");	/* Die on Illegal Window */

	if (Winner -> _depth >= INVISIBLE) return;

	w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);
	x = Winner -> _x_pos;
	y = Winner -> _y_pos;

	if (Need_Set_Scroll)
		_fix_map ();

	for (i = Winner -> _top_x, j = 0; i < Winner -> _bot_x; i++, j++)
	{
		p = pbuf;
		xmap = Winner -> _map[j];
		mode = *xmap & VT_VIDEO;
		omap = &cmap[i][Winner -> _top_y];
		changed = 0;
		w_xgo (Winner, j, 0);
		for (k = Winner -> _top_y; k < Winner -> _bot_y;
				k++, xmap++, omap++)
		{
			if (mode != (*xmap & VT_VIDEO))
			{
				if (changed)
				{
					*p = '\0';
					wxputl (Winner, pbuf, mode, FALSE);
				}
				else
					w_xgo (Winner, j, k - Winner -> _top_y);
				mode = *xmap & VT_VIDEO;
				p = pbuf;
			}
			*p = *xmap & VT_CHAR;
			if (*p == '\0')
				*p = ' ';
			p++;
			if (*xmap != *omap)
				changed++;

		}
		if (changed)
		{
			*p = '\0';
			wxputl (Winner, pbuf, mode, FALSE);
		}
	}

	w_xgo (Winner, x, y);
}
