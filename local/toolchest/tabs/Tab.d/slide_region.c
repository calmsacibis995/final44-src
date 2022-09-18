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
#include <setjmp.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

slide_region (fregion, count, lines)
struct field_item      *fregion[];
int     count;
int     lines;
{
	register struct window  *winner;
	register int     index;
	register int     x;

	winner = fregion[0] -> window;

	if (lines)
	{
		if (((lines < 0) ? -lines : lines) >=
			(winner -> _bot_x - winner -> _top_x - 2))
		{
			s_werase (winner);
		}
		else
		{
			w_xgo (winner, winner -> _bot_x - winner -> _top_x - 1, 0);
			wclrl (winner);
			if ((LOPEN) &&
				(winner -> _scrollable))
			{
				wvadjust (winner,
						winner -> _v_x_top,
						winner -> _v_y_top,
						winner -> _v_x_bot, /* - 1 ? */
						winner -> _v_y_bot,
						TRUE,
						lines);
			}
			else
			{
				wscroll (winner, -lines);
			}
		}
	}
	w_xgo (winner, winner -> _bot_x - winner -> _top_x - 1, 0);
	wclrl (winner);

	for (index = 0; index < count; index++)
	{
		x = fregion[index] -> x_pos;
		if (x >= 512)
			x -= 512;
		x += lines;

		if (x < 0)
		{
			fregion[index] -> x_pos = x;
			continue;
		}

		if (x >= (winner -> _bot_x - winner -> _top_x - 1))
		{
			fregion[index] -> x_pos = 512 + x;
			continue;
		}

		fregion[index] -> x_pos = -1;
		Move_Field (fregion[index], x, fregion[index] -> y_pos, 0);
	}

	Wrefresh (winner);
}
