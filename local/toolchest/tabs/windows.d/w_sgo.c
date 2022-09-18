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
 *	w_sgo (Winner, x, y)
 *
 *	This procedure moves the real cursor to the
 *	(x,y) position in the specified window.
 *
 */

void
w_sgo (Winner, x, y)
register struct window *Winner;
register int    x,
                y;
{
	W_Ok (Winner, "w_sgo");	/* Die on Illegal Window */

	C_window = Winner;

	sgo (x + Winner -> _top_x, y + Winner -> _top_y);
}
