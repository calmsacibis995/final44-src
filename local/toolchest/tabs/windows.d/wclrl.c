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
 *	wclrl (Winner)
 *
 *	This procedure clears the rest of the current line in the specified
 *	window.
 *
 */

void
wclrl (Winner)
register struct window *Winner;
{
	register        i;
	register char  *bptr;
	register CHAR  *mptr;
	char	buffer[256];
	int     x;
	int     y;

	w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);

	x = Winner -> _x_pos;
	y = Winner -> _y_pos;

	if (Need_Set_Scroll)
	{
		_fix_map ();
		w_xgo (Winner, x, y);
	}

	mptr = &Winner -> _map[Winner -> _x_pos][Winner -> _y_pos];
	bptr = buffer;
	for (i = mcol; i < Winner -> _bot_y; i++, mptr++, bptr++)
	{
		*mptr = ' ';
		*bptr = ' ';
	}
	*mptr = 0;
	*bptr = '\0';

	wxputl (Winner, buffer, 0, FALSE);
	w_xgo (Winner, x, y);
}
