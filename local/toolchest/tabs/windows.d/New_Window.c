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
 *	New_Window (NewWinner)
 *
 *	This function allocates space for the specified window.
 *	New_Window guarantees legal placement of the new window.
 *	No screen updating is performed to allow the user
 *	to create more than one window with only one screen update
 *	(Ref_All_Windows ()).
 *
 *	struct SWindow			User setup structure
 *	{
 *		int top_x;
 *		int top_y;
 *		int lines;
 *		int cols;
 *		int depth;
 *		char box_h;
 *		char box_v;
 *		char type_scroll;
 *	};
 *
 *	The value returned is a pointer to the new window.  If a new
 *	window cannot be allocated -1 is returned.
 *
 */

struct window  *
New_Window (NewWinner)
struct SWindow  NewWinner;
{
	register struct window *Winner;
	register int    shift;
	register int    index;
	extern CHAR    *malloc ();

	for (shift = 0; shift < TOTAL_WINDOWS; shift++)
	{
		Winner = &_Windows[shift];

		if (Winner -> _bot_x == 0)
		{
			Winner -> _top_x = NewWinner.top_x;
			Winner -> _top_y = NewWinner.top_y;

			Need_Set_Scroll = TRUE;
			Winner -> _clear_list.old_x = 0;
			Winner -> _clear_list.old_xb = 0;
			Winner -> _clear_list.old_y = 0;
			Winner -> _clear_list.old_yb = 0;
			Winner -> _clear_list.old_depth = 0;
			Winner -> _clear_list.need = FALSE;

			if (NewWinner.box_h)
			{
				if (NewWinner.lines > SCRNLIN - 2)
					NewWinner.lines = SCRNLIN - 2;
				if (NewWinner.cols > SCRWID - 2)
					NewWinner.cols = SCRWID - 2;
				if (Winner -> _top_x < 1)
					Winner -> _top_x = 1;
				if (Winner -> _top_y < 1)
					Winner -> _top_y = 1;
				if ((Winner -> _top_x + NewWinner.lines)
						>= (SCRNLIN - 1))
					Winner -> _top_x = SCRNLIN - 1
						- NewWinner.lines;
				if ((Winner -> _top_y + NewWinner.cols)
						> SCRWID - 1)
					Winner -> _top_y = SCRWID - 1
						- NewWinner.cols;
				Winner -> _box_attribute = NewWinner.box_attribute;

			}
			else
			{
				if (NewWinner.lines > SCRNLIN - 0)
					NewWinner.lines = SCRNLIN - 0;
				if (NewWinner.cols > SCRWID)
					NewWinner.cols = SCRWID;
				if (Winner -> _top_x < 0)
					Winner -> _top_x = 0;
				if (Winner -> _top_y < 0)
					Winner -> _top_y = 0;
				if ((Winner -> _top_x + NewWinner.lines)
						>= (SCRNLIN - 0))
					Winner -> _top_x = SCRNLIN - 0
						- NewWinner.lines;
				if ((Winner -> _top_y + NewWinner.cols)
						> SCRWID)
					Winner -> _top_y = SCRWID
						- NewWinner.cols;
				Winner -> _box_attribute = 0;
			}
			Winner -> _x_pos = 0;
			Winner -> _y_pos = 0;
			Winner -> _bot_x = Winner -> _top_x + NewWinner.lines;
			Winner -> _bot_y = Winner -> _top_y + NewWinner.cols;
			Winner -> _type_scroll = NewWinner.type_scroll;
			Winner -> _depth = NewWinner.depth;
			Winner -> _key = 1 << shift;
			if (NewWinner.box_h)
			{
				if ((Winner -> _box_h = NewWinner.box_h) < ' ')
					Winner -> _box_h = ' ';
				if ((Winner -> _box_v = NewWinner.box_v) < ' ')
					Winner -> _box_v = ' ';
			}
			else
			{
				Winner -> _box_h = 0;
				Winner -> _box_v = 0;
			}
			for (index = 0; index < NewWinner.lines; index++)
			{
				Winner -> _map[index] =
					malloc ((NewWinner.cols * sizeof (CHAR)) + MXTRA);
				if (Winner -> _map[index] == 0)
					return ((struct window *) (-1));
			}

			wstart (Winner -> _map,
					NewWinner.lines, NewWinner.cols);
			Total_Windows++;

			w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);

#ifdef WHIPANY
			Winner -> _user_flag = getpid ();
#else
			Winner -> _user_flag = 0;
#endif
			return (Winner);
		}
	}

	return ((struct window *) (-1));
}
