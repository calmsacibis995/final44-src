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
 *	Ref_All_Windows ()
 *
 *	This procedure updates all of the windows.  Assumes that windows
 *	at depth >= INVISIBLE are assumed to be not visible.  The update includes
 *	boxing the window.
 *
 */

void
Ref_All_Windows ()
{
	register int    i;
	struct window  *Save_win;

	Save_win = C_window;

	if (Need_Set_Scroll)
		_fix_map ();

	for (i = 0; i < TOTAL_WINDOWS; i++)
	{
		if (_Windows[i]._bot_x)
		{
			if (_Windows[i]._depth >= INVISIBLE) continue;
			box (&_Windows[i]);
			Wrefresh (&_Windows[i]);
		}
	}

	if (Save_win)
		w_xgo (Save_win, Save_win -> _x_pos, Save_win -> _y_pos);
}

_fix_map ()
{
	register int i;
	int x;
	int y;
	int first;

	x = mline;
	y = mcol;

	Need_Set_Scroll = FALSE;

	for (i = 0, first = 0; i < TOTAL_WINDOWS; i++)
	{
		if ((_Windows[i]._bot_x) && (_Windows[i]._depth < INVISIBLE))
		{
			Key_Map (&_Windows[i], first);
			first++;
		}
	}

	Set_Scroll_Type ();

	for (i = 0; i < TOTAL_WINDOWS; i++)
	{
		if (_Windows[i]._clear_list.need)
		{
			_Windows[i]._clear_list.need = FALSE;
			if (_Windows[i]._bot_x == 0)
				continue;
			if ((_Windows[i]._clear_list.old_x != _Windows[i]._v_x_top) ||
			   (_Windows[i]._clear_list.old_xb != _Windows[i]._v_x_bot) ||
			   (_Windows[i]._clear_list.old_y != _Windows[i]._v_y_top) ||
			   (_Windows[i]._clear_list.old_yb != _Windows[i]._v_y_bot) ||
			   (_Windows[i]._clear_list.old_depth >= INVISIBLE))
				_wclear (&_Windows[i]);
		}
	}
	xgo (x, y);
}
