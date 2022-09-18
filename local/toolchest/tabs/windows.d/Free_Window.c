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
 *	Free_Window (winner)
 *
 *	This function deletes the specified window.  The storage associated
 *	with the window is freed.  The map of the screen is also updated.
 *	No screen updating is performed.  This allows more than one window
 *	to be deleted with one screen update (Ref_All_Windows ()).
 *
 *	The value returned is the new total number of active windows.  If
 *	the window is not one of the list of windows -1 is returned.
 *
 */

int
Free_Window (Winner)
struct window  *Winner;
{
	register int    line;

	if (Winner -> _bot_x == 0)	/* Already Freed */
		return (-1);

	W_Ok (Winner, "Free_Window");

	Un_Map (Winner);
	for (line = 0; line < (Winner -> _bot_x - Winner -> _top_x);
			line++)
	{
		if (Winner -> _map[line])
		{
			free (Winner -> _map[line]);
			Winner -> _map[line] = 0;
		}
	}
	Winner -> _x_pos = 0;
	Winner -> _y_pos = 0;
	Winner -> _top_x = 0;
	Winner -> _top_y = 0;
	Winner -> _bot_x = 0;
	Winner -> _bot_y = 0;
	Winner -> _key = 0;
	Winner -> _box_h = 0;
	Winner -> _box_v = 0;
	Winner -> _type_scroll = 0;
	Winner -> _depth = 0;
	Total_Windows--;
	Need_Set_Scroll = TRUE;
	Winner -> _clear_list.old_x = 0;
	Winner -> _clear_list.old_xb = 0;
	Winner -> _clear_list.old_y = 0;
	Winner -> _clear_list.old_yb = 0;
	Winner -> _clear_list.old_depth = 0;
	Winner -> _clear_list.need = FALSE;
	C_window = 0;
	return (Total_Windows);
}
