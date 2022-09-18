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
 *	Un_Map (Winner)
 *
 *	This procedure is called internally to remove a window from
 *	the screen map.  No screen updating is performed.
 *
 */

void
Un_Map (Winner)
struct window  *Winner;
{
	register unsigned int  *ptr;
	register unsigned int   key;
	register int    i;
	int     top_x;
	int     top_y;
	int     bot_x;
	int     bot_y;

	W_Ok (Winner, "Un_Map");	/* Die on Illegal Window */

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
	for (; top_x < bot_x; top_x++)
	{
		ptr = &kmap[top_x][top_y];
		for (i = top_y;
				i < bot_y; i++, ptr++)
		{
			*ptr &= ~(key);
		}
	}
}
