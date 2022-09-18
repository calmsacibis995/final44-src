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
 *	wc_erase (Winner, count)
 *
 *	This procedure erases count characters in a window.
 *
 */

void
wc_erase (Winner, count)
struct window  *Winner;
int     count;
{
	int     x;
	int     y;

	W_Ok (Winner, "wc_erase");	/* Die on Illegal Window */

	if (Need_Set_Scroll)
		_fix_map ();

	while (count--)
	{
		if (mcol <= Winner -> _top_y)
		{
			if (mline <= 0)
			{
				return;
			}
			mline--;
			mcol = Winner -> _bot_y;
		}

		mcol--;
		Winner -> _y_pos = mcol - Winner -> _top_y;
		Winner -> _x_pos = mline - Winner -> _top_x;

		x = mline;
		y = mcol;

		if (kmap[mline][mcol] & Winner -> _key)
		{
			mgo (mline, mcol);
			wxprintf (Winner, "%c", ' ');
			mgo (x, y);
		}
		else
		{
			w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);
			wxprintf (Winner, "%c", ' ');
			mcol--;
		}

		mline = x;
		mcol = y;
		Winner -> _y_pos = mcol - Winner -> _top_y;
		Winner -> _x_pos = mline - Winner -> _top_x;
	}
}
