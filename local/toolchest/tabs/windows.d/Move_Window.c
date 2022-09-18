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
 *	Move_Window (Winner, topx, topy, depth)
 *
 *	This procedure moves the specified window to the indicated (x,y)
 *	and simulated depth.  Move_Window guarantees legal placement of
 *	the window.  No screen updating is performed to allow the user
 *	to move more than one window with only one screen update
 *	(Ref_All_Windows ()).
 *
 */

void
Move_Window (Winner, topx, topy, depth)
register struct window *Winner;
int     topx;
int     topy;
int     depth;
{
	int     lines;
	int     cols;
	int     old_depth;

	W_Ok (Winner, "Move_Window");	/* Die on Illegal Window */

	C_window = Winner;

	if ((Winner -> _top_x == topx) &&
		(Winner -> _top_y == topy) &&
		(Winner -> _depth == depth))
			return;

	if ((depth >= INVISIBLE) &&
		(Winner -> _depth < INVISIBLE))
		_wclear (Winner);

	old_depth = Winner -> _depth;
	Un_Map (Winner);

	lines = Winner -> _bot_x - Winner -> _top_x;
	cols = Winner -> _bot_y - Winner -> _top_y;
	Winner -> _top_x = topx;
	Winner -> _top_y = topy;
	if (Winner -> _box_h)
	{
		if (Winner -> _top_x < 1)
			Winner -> _top_x = 1;
		if (Winner -> _top_y < 1)
			Winner -> _top_y = 1;
		if ((Winner -> _top_x + lines) >= (SCRNLIN - 1))
			Winner -> _top_x = SCRNLIN - 1 - lines;
		if ((Winner -> _top_y + cols) > SCRWID - 1)
			Winner -> _top_y = SCRWID - 1 - cols;
	}
	else
	{
		if (Winner -> _top_x < 0)
			Winner -> _top_x = 0;
		if (Winner -> _top_y < 0)
			Winner -> _top_y = 0;
		if ((Winner -> _top_x + lines) >= (SCRNLIN - 0))
			Winner -> _top_x = SCRNLIN - 0 - lines;
		if ((Winner -> _top_y + cols) > SCRWID)
			Winner -> _top_y = SCRWID - cols;
	}
	Winner -> _bot_x = Winner -> _top_x + lines;
	Winner -> _bot_y = Winner -> _top_y + cols;
	Winner -> _depth = depth;

	Winner -> _scrollable = FALSE;

	if ((depth < INVISIBLE) || (old_depth < INVISIBLE))
	{
		Need_Set_Scroll = TRUE;

		Winner -> _clear_list.need = TRUE;
		Winner -> _clear_list.old_depth = old_depth;
		Winner -> _clear_list.old_x = Winner -> _v_x_top;
		Winner -> _clear_list.old_xb = Winner -> _v_x_bot;
		Winner -> _clear_list.old_y = Winner -> _v_y_top;
		Winner -> _clear_list.old_yb = Winner -> _v_y_bot;
	}
}
