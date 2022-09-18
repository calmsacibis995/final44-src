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
 *	s_werase (Winner)
 *
 *	This procedure clears the virtual screen of the specified window.
 *
 *	No screen updating is performed.  See Wrefresh ().
 *
 */

void
s_werase (Winner)
register struct window *Winner;
{
	register CHAR  *xmap;
	register int    i;
	int     j;
	int     k;

	w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);

	for (i = Winner -> _top_x, j = 0; i < Winner -> _bot_x; i++, j++)
	{
		for (k = Winner -> _top_y, xmap = Winner -> _map[j];
				k < Winner -> _bot_y; k++, xmap++)
		{
			*xmap = (short) ' ';
		}
	}
}
