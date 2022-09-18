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
 *	w_xgo (Winner, x, y)
 *
 *	This procedure moves the virtual cursor to the
 *	(x,y) position in the specified window.
 *
 */

void
w_xgo (Winner, x, y)
register struct window *Winner;
{
/*	W_Ok (Winner, "w_xgo");	/* Die on Illegal Window */

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

	Winner -> _x_pos = mline - Winner -> _top_x;
	Winner -> _y_pos = mcol - Winner -> _top_y;
}
