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
 *	w_mgo (Winner, x, y)
 *
 *	This procedure moves the (real and virtual) cursor to the
 *	(x,y) position in the specified window.
 *
 */

void
w_mgo (Winner, x, y)
register struct window *Winner;
register int    x;
register int    y;
{
	W_Ok (Winner, "w_mgo");	/* Die on Illegal Window */

	C_window = Winner;

	if ((x <= (Winner -> _bot_x - Winner -> _top_x)) && (x >= 0))
	{
		mline = x + Winner -> _top_x;
	}
	else
		mline = Winner -> _top_x;

	if ((y <= (Winner -> _bot_y - Winner -> _top_y)) && (y >= 0))
	{
		mcol = y + Winner -> _top_y;
	}
	else
		mcol = Winner -> _top_y;

	sgo (mline, mcol);
	Winner -> _x_pos = mline - Winner -> _top_x;
	Winner -> _y_pos = mcol - Winner -> _top_y;
}
