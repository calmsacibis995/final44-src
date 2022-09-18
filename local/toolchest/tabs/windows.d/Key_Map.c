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
 *	Key_Map (Winner)
 *
 *	This procedure adds the specified window to the screen map.  This
 *	procedure is used internally for creating, moving, and deleting
 *	windows.
 *
 */

void
Key_Map (Winner, First)
struct window  *Winner;
int First;
{
	register int i;
	register unsigned int    *kmap_ptr;
	register unsigned int     above_keys;
	unsigned int same_keys;
	unsigned int key;
	int     top_x;
	int     top_y;
	int     bot_x;
	int     bot_y;

	W_Ok (Winner, "Key_Map");	/* Die on Illegal Window */

	if (Winner -> _depth >= INVISIBLE)
		return;

	if (Winner -> _box_h)
	{
		top_x = Winner -> _top_x - 1;
		top_y = Winner -> _top_y - 1;
		bot_x = Winner -> _bot_x + 1;
		bot_y = Winner -> _bot_y + 1;
	}
	else
	{
		top_x = Winner -> _top_x;
		top_y = Winner -> _top_y;
		bot_x = Winner -> _bot_x;
		bot_y = Winner -> _bot_y;
	}

	key = Winner -> _key;
	above_keys = 0;
	same_keys = 0;
	if (First)
	{
		for (i = 0; i < TOTAL_WINDOWS; i++)
		{
			if ((_Windows[i]._bot_x) &&
				(_Windows[i]._key != key) &&
				(_Windows[i]._depth <= Winner -> _depth))
			{
				if (_over_lap (Winner, &_Windows[i]) == FALSE)
					continue;

				if (_Windows[i]._depth == Winner -> _depth)
					same_keys |= _Windows[i]._key;
				else
					above_keys |= _Windows[i]._key;
			}
		}
	}

	if (above_keys == 0)
	{
		for (; top_x < bot_x; top_x++)
		{
			kmap_ptr = &kmap[top_x][top_y];
			for (i = top_y; i < bot_y; i++)
			{	/* zero test slightly faster */
				if ((same_keys) && (*kmap_ptr & same_keys))
					*kmap_ptr++ = (key | same_keys);
				else
					*kmap_ptr++ = key;
			}
		}
		return;
	}

	for (; top_x < bot_x; top_x++)
	{
		kmap_ptr = &kmap[top_x][top_y];
		for (i = top_y; i < bot_y; i++, kmap_ptr++)
		{
			if ((*kmap_ptr & above_keys) == 0)
			{
				if ((same_keys) && (*kmap_ptr & same_keys))
					*kmap_ptr = (key | same_keys);
				else
					*kmap_ptr = key;
			}
		}
	}
}

/*
 *	Check if window1 is overlapped by window2
 *
 */
_over_lap(window1, window2)
struct window *window1;
struct window *window2;
{
	int     top1_x;
	int     top1_y;
	int     bot1_x;
	int     bot1_y;

	int     top2_x;
	int     top2_y;
	int     bot2_x;
	int     bot2_y;

	if (window1 -> _box_h)
	{
		top1_x = window1 -> _top_x - 1;
		top1_y = window1 -> _top_y - 1;
		bot1_x = window1 -> _bot_x + 1;
		bot1_y = window1 -> _bot_y + 1;
	}
	else
	{
		top1_x = window1 -> _top_x;
		top1_y = window1 -> _top_y;
		bot1_x = window1 -> _bot_x;
		bot1_y = window1 -> _bot_y;
	}

	if (window2 -> _box_h)
	{
		top2_x = window2 -> _top_x - 1;
		top2_y = window2 -> _top_y - 1;
		bot2_x = window2 -> _bot_x + 1;
		bot2_y = window2 -> _bot_y + 1;
	}
	else
	{
		top2_x = window2 -> _top_x;
		top2_y = window2 -> _top_y;
		bot2_x = window2 -> _bot_x;
		bot2_y = window2 -> _bot_y;
	}

	if (top2_x < top1_x)
		top2_x = top1_x;
	if (top2_x > bot2_x)
		return (FALSE);
	if (top2_y < top1_y)
		top2_y = top1_y;
	if (top2_y > bot2_y)
		return (FALSE);
	if (bot2_x > bot1_x)
		bot2_x = bot1_x;
	if ((bot2_x < window2 -> _top_x) || (bot2_x < top2_x))
		return (FALSE);
	if (bot2_y > bot1_y)
		bot2_y = bot1_y;
	if ((bot2_y < window2 -> _top_y) || (bot2_y < top2_y))
		return (FALSE);

	if (((top2_x >= top1_x) && (top2_y >= top1_y)) &&
		((bot2_x <= bot1_x) && (bot2_y <= bot1_y)))
		return (TRUE);

	return (FALSE);
}
