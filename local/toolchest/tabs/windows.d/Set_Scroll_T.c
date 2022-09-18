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
 *	Set_Scroll_Type ()
 *
 *	This procedure calculates which scrolling strategy to use for
 *	all of the active windows.  The number of characters visible
 *	in the window versus the number of characters that will have
 *	to be moved on the screen are the two parameters of interest.
 *	Scrolling strategies use line insert/delete or repaint.
 *
 *	This procedure is called internally when ever a window is
 *	created, deleted, or moved.  It is not called with every
 *	scroll operation.  Windows at depth >= INVISIBLE are assumed to be
 *	not visible.
 *
 */

struct rect
{
	struct rect	*next;
	short	top_x;
	short	bot_x;
	short	top_y;
	short	bot_y;
};
struct rect *First_Vis_Rect;
struct rect *Last_Vis_Rect;

Set_Scroll_Type ()
{
	struct window *Winner;
	int     index;
	int     lines;
	int     cols;
	struct rect	rect;
	int	_max_rect();
	int	vis_size;
	int	old_vis_size;
	int	total;

	for (index = 0; index < TOTAL_WINDOWS; index++)
	{
		Winner = &_Windows[index];

		Winner -> _scrollable = FALSE;

		Winner -> _v_x_top = -1;
		Winner -> _v_x_bot = -1;
		Winner -> _v_y_top = -1;
		Winner -> _v_y_bot = -1;

		if (Winner -> _bot_x == 0)
			continue;

		if (Winner -> _depth >= INVISIBLE)
			continue;

		if ((CWINDOW == 0) &&
			 (Winner -> _type_scroll == FALSE))
			continue;

		rect.top_y = Winner -> _top_y;
		rect.bot_y = Winner -> _bot_y;
		rect.top_x = Winner -> _top_x;
		rect.bot_x = Winner -> _bot_x - 1;

		/* find the largest visible rectangle in Winner */
		find_vis_rects (Winner, &rect, 0);
		vis_size = _largest_rect (First_Vis_Rect, &rect);

		if (vis_size)
		{
			Winner -> _v_y_top = rect.top_y;
			Winner -> _v_y_bot = rect.bot_y;
			Winner -> _v_x_top = rect.top_x;
			Winner -> _v_x_bot = rect.bot_x;
		}
		else
			Winner -> _v_x_bot = -1;

		if (CWINDOW)
			vis_size = _tot_vis_area (First_Vis_Rect, &rect);
/*		Print_Message (Winner, 0, "total = %d",vis_size); */

		free_vis_rects (First_Vis_Rect);

		cols = rect.bot_y - rect.top_y;
		lines = rect.bot_x - rect.top_x;


		if ((lines > 2) && (cols > 2))
		{
			if (CWINDOW)
			{
				total = lines * cols;
				if (total < (vis_size * 2))
					Winner -> _scrollable = TRUE;
				else
					Winner -> _scrollable = FALSE;
			}
			else
			{
				total = SCRWID * lines;
				if (total < (vis_size * 2))
					Winner -> _scrollable = TRUE;
				else
					Winner -> _scrollable = FALSE;
			}
		}
	}
}

static int
find_vis_rects (Winner, rect, index)
struct window	*Winner;
register struct rect	*rect;
int	index;
{
	struct rect	new_rect;
	register struct window	*window;

	/* ignore dead and more distant windows */
	while (TRUE)
	{
		if (index == TOTAL_WINDOWS)
		{
			add_vis_rect (rect);
			return;
		}

		window = &_Windows[index];
		index++;
		if ((window -> _bot_x == 0) ||
				(window -> _key == Winner -> _key) ||
				(window -> _depth > Winner -> _depth))
			continue;

		if (window -> _top_x <= rect -> top_x &&
				window -> _top_y <= rect -> top_y &&
				window -> _bot_x >= rect -> bot_x &&
				window -> _bot_y >= rect -> bot_y)
		{
			/* entire window covered */
			free_vis_rects (First_Vis_Rect);
			First_Vis_Rect = 0;
			return;
		}
	
		/* only recurse if side of interest inside window */

		new_rect.bot_x = -2;
		/* area below? */
		if (rect -> top_x < window -> _bot_x &&
				rect -> bot_x > window -> _bot_x)
		{
			new_rect = *rect;
			new_rect.top_x = window -> _bot_x + 1;
/*			if (window -> _box_h)
				new_rect.top_x++;
*/
			find_vis_rects (Winner, &new_rect, index);
		}

		/* area to right? */
		if (rect -> top_y < window -> _bot_y &&
				rect -> bot_y > window -> _bot_y)
		{
			new_rect = *rect;
			new_rect.top_y = window -> _bot_y + 1;
/*
			if (window -> _box_v)
				new_rect.top_y++;
*/
			find_vis_rects (Winner, &new_rect, index);
		}

		/* area above? */
		if (rect -> bot_x > window -> _top_x &&
				rect -> top_x < window -> _top_x)
		{
			new_rect = *rect;
			new_rect.bot_x = window -> _top_x - 1;
/*
			if (window -> _box_h)
				new_rect.bot_x--;
*/
			find_vis_rects (Winner, &new_rect, index);
		}

		/* area to left? */
		if (rect -> bot_y > window -> _top_y &&
				rect -> top_y < window -> _top_y)
		{
			new_rect = *rect;
			new_rect.bot_y = window -> _top_y - 1;
/*
			if (window -> _box_v)
				new_rect.bot_y--;
*/
			find_vis_rects (Winner, &new_rect, index);
		}
		if (new_rect.bot_x != -2)
			return;
	}
}
_largest_rect (rect, ret_rect)
register struct rect *rect;
struct rect	*ret_rect;
{
	register int	size = 0;
	int		largest = 0;
	struct rect 	*max_rect = 0;

	while (rect)
	{
		size = ((rect -> bot_x - rect -> top_x) *
				(rect -> bot_y - rect -> top_y));
		if (size > largest)
		{
			largest = size;
			max_rect = rect;
		}
		rect = rect -> next;
	}
	if (max_rect)
		*ret_rect = *max_rect;
	else
		ret_rect -> bot_x = 0;
	return (largest);
}

free_vis_rects (rect)
register struct rect	*rect;
{
	register struct rect	*free_rect;

	while (rect)
	{
		free_rect = rect;
		rect = rect -> next;
		free (free_rect);
	}
	First_Vis_Rect = 0;
}

_tot_vis_area (rect)
register struct rect *rect;
{
	register struct rect *test_rect;
	register int size = 0;

	while (rect)
	{
		/* if x_bot = -1 skip */
		/* if bottoms egual, make bottom = test_top */
		/* if tops eaual, make top = test_bot */
		for (test_rect = rect -> next; test_rect; test_rect = test_rect -> next)
		{
			if (rect -> bot_x == -1 )
				continue;
			if (rect -> bot_x == test_rect -> bot_x &&
					rect -> bot_y <= test_rect -> bot_y &&
					rect -> top_y >= test_rect -> top_y)
				rect -> bot_x = test_rect -> top_x - 1;
			if (rect -> top_x == test_rect -> top_x &&
					rect -> bot_y <= test_rect -> bot_y &&
					rect -> top_y >= test_rect -> top_y)
				rect -> top_x = test_rect -> bot_x + 1;
			if (rect -> bot_y == test_rect -> bot_y &&
					rect -> bot_x <= test_rect -> bot_x &&
					rect -> top_x >= test_rect -> top_x)
				rect -> bot_y = test_rect -> top_y - 1;
			if (rect -> top_y == test_rect -> top_y &&
					rect -> bot_x <= test_rect -> bot_x &&
					rect -> top_x >= test_rect -> top_x)
				rect -> top_y = test_rect -> bot_y + 1;
		}
		if (rect -> bot_x <= rect -> top_x ||
					rect -> bot_y <= rect -> top_y)
		{
			rect -> bot_x = -1;
			rect -> bot_y = -1;
			rect -> top_x = -1;
			rect -> top_y = -1;
		}
		else
			size += ((rect -> bot_x - rect -> top_x) *
					(rect -> bot_y - rect -> top_y));
		rect = rect -> next;
	}
	return (size);
}

add_vis_rect (rect)
struct rect	*rect;
{
	struct rect	*next_rect;

	/* add to visible list */
	next_rect = (struct rect *) malloc (sizeof (struct rect));
	*next_rect = *rect;
	next_rect -> next = 0;
	if (First_Vis_Rect)
		Last_Vis_Rect -> next = next_rect;
	else
		First_Vis_Rect = next_rect;
	Last_Vis_Rect = next_rect;
}
