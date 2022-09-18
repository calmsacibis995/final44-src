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
 *	box (Winner)
 *
 *	This procedure updates the box around the specified window.
 *	This procedure assumes that windows at depth >= INVISIBLE are assumed
 *	to be not visible.
 *
 */

void
box (Winner)
struct window  *Winner;
{
	register int    i;
	register int    j;
	char    hor[NSCRCOL];
	char    vert[2];
	struct window   Box;
	CHAR	one_line[NSCRCOL];

	W_Ok (Winner, "box");	/* Die on Illegal Window */

	if (!Winner -> _box_h)
		return;

	if (Winner -> _depth >= INVISIBLE)
		return;

	if (Need_Set_Scroll)
		_fix_map ();

	if (JQTYPE)
	{
		JQBox (Winner);
		return;
	}

	Winner -> _box_attribute &= VT_VIDEO;

	for (i = 0; i < NSCRLIN; i++)
	{
		Box._map[i] = one_line;
	}

	wstart (Box._map, 1, NSCRCOL);
	Box._top_x = Winner -> _top_x - 1;
	Box._top_y = Winner -> _top_y - 1;
	Box._x_pos = 0;
	Box._y_pos = 0;
	Box._bot_x = Winner -> _bot_x + 1;
	Box._bot_y = Winner -> _bot_y + 1;
	Box._key = Winner -> _key;
	Box._type_scroll = Winner -> _type_scroll;
	Box._depth = Winner -> _depth;

	for (j = 0, i = Box._top_y; i < Box._bot_y; i++, j++)
	{
		hor[j] = Winner -> _box_h;
	}

	hor[j] = 0;
	vert[0] = Winner -> _box_v;
	vert[1] = 0;

	w_xgo (&Box, 0, 0);
	wxputl (&Box, hor, Winner -> _box_attribute, FALSE);

	for (i--, j = Box._top_x + 1; j < (Box._bot_x - 1); j++)
	{
		w_xgo (&Box, j - Box._top_x, i - Box._top_y);
		wxputl (&Box, vert, Winner -> _box_attribute, FALSE);
	}

/* Window Name Stuff
	for (j = 0; j < TOTAL_WINDOWS; j++)
	{
		if (Winner == &_Windows[j])
		{
			break;
		}
	}

	hor[0] = 'A' + j - 1;
	hor[2] = '0' + Winner -> _depth;
/* */
	w_xgo (&Box, Box._bot_x - 1 - Box._top_x, 0);
	wxputl (&Box, hor, Winner -> _box_attribute, FALSE);

	for (i = Box._top_y, j = Box._bot_x - 2; j > Box._top_x; j--)
	{
		w_xgo (&Box, j - Box._top_x, i - Box._top_y);
		wxputl (&Box, vert, Winner -> _box_attribute, FALSE);
	}

	w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);
}

static int istart;
static int jstart;

static int
JQBox (Winner)
register struct window *Winner;
{
	register int i;
	register int j;
	char sbuf[16];

	vputch (0);

	istart = -1;

/* Upper left */
	i = Winner -> _top_x - 1;
	j = Winner -> _top_y;
 	if (Winner -> _key & kmap[i][j - 1])
 	{
		sprintf (sbuf, "\033B%c%c%c%c",
			98 + 040,
			040,
			j - 1 + 040,
			i + 040);
		JQ_puts (sbuf);
		cmap[i][j - 1] = UPLEFT;
 	}
	for (; j < Winner -> _bot_y; j++)
	{
		JQ_check (Winner, i, j, HORIX);
	}
	if (istart != -1)
		JQ_print (i, j);

/* Upper right */
	i = Winner -> _top_x;
	j = Winner -> _top_y - 1;
 	if (Winner -> _key & kmap[i - 1][Winner -> _bot_y])
 	{
		sprintf (sbuf, "\033B%c%c%c%c",
			99 + 040,
			040,
			Winner -> _bot_y + 040,
			i - 1 + 040);
		JQ_puts (sbuf);
		cmap[i - 1][Winner -> _bot_y] = UPRIGHT;
 	}
	for (; i < Winner -> _bot_x; i++)
	{
		JQ_check (Winner, i, j, VERTX);
	}
	if (istart != -1)
		JQ_print (i, j);

/* Lower right */
	i = Winner -> _bot_x;
	j = Winner -> _top_y;
	if (Winner -> _key & kmap[i][Winner -> _bot_y])
	{
		sprintf (sbuf, "\033B%c%c%c%c",
			100 + 040,
			040,
			Winner -> _bot_y + 040,
			i + 040);
		JQ_puts (sbuf);
		cmap[i][Winner -> _bot_y] = LORIGHT;
	}
	for (; j < Winner -> _bot_y; j++)
	{
		JQ_check (Winner, i, j, HORIX);
	}
	if (istart != -1)
		JQ_print (i, j);

/* Lower left */
	i = Winner -> _top_x;
	j = Winner -> _bot_y;
 	if (Winner -> _key & kmap[Winner -> _bot_x][Winner -> _top_y - 1])
 	{
		sprintf (sbuf, "\033B%c%c%c%c",
			101 + 040,
			040,
			Winner -> _top_y - 1 + 040,
			Winner -> _bot_x + 040);
		JQ_puts (sbuf);
		cmap[Winner -> _bot_x][Winner -> _top_y - 1] = LOLEFT;
 	}
	for (; i < Winner -> _bot_x; i++)
	{
		JQ_check (Winner, i, j, VERTX);
	}
	if (istart != -1)
		JQ_print (i, j);
}

static int
JQ_check(Winner, i, j, fill)
register struct window *Winner;
register int i;
register int j;
int fill;
{
 	if (Winner -> _key & kmap[i][j])
	{
		if (istart == -1)
		{
			istart = i;
			jstart = j;
		}
		if (scrjnk[i] <= j) scrjnk[i] = j + 1;
		cmap[i][j] = fill;
	}
	else
	{
		JQ_print (i, j);
	}
}

static int
JQ_print (i, j)
register int i;
register int j;
{
	char sbuf[16];

	if (istart != -1)
	{
		sprintf (sbuf, "\033B%c%c%c%c",
			jstart + 040,
			istart + 040,
			j + 040,
			i + 040);
		JQ_puts (sbuf);
	}
	istart = -1;
}

static int
JQ_puts (cp)
register char  *cp;
{
	while (*cp)
	{
		putchar (*cp++);
	}
}
