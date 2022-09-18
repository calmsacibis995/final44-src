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
 *	wstart (map, lines, cols)
 *
 *	This procedure clears (sets to ' ') the specified screen map.
 *
 */

void
wstart (map, lines, cols)
CHAR   *map[NSCRLIN];
int     lines;
int     cols;
{
	register CHAR  *ptr;
	register int    j,
	                i;

	for (i = 0; i < lines; i++)
	{
		for (j = 0, ptr = map[i];
				j < cols; j++, ptr++)
		{
			*ptr = ' ';
		}
		*ptr = '\0';
	}
}

/*
 *	_wclear (Winner)
 *
 *	Clear the specified window using firmware windowing in the
 *	terminal.
 *
 */
_wclear (Winner)
struct window *Winner;
{
	register int i;
	register int j;
	register CHAR *ptr;
	int topx;
	int topy;
	int botx;
	int boty;
	int x;
	int y;

	if ((!CWINDOW) || (!CLEAR))
		return (FALSE);

	if (	(Winner -> _v_x_top == -1) ||
		(Winner -> _v_y_top == -1) ||
		(Winner -> _v_x_bot == -1) ||
		(Winner -> _v_y_bot == -1))
		return (FALSE);

	x = Winner -> _x_pos;
	y = Winner -> _y_pos;

	if (Need_Set_Scroll)
		_fix_map ();

	topx = Winner -> _v_x_top;
	topy = Winner -> _v_y_top;
	botx = Winner -> _v_x_bot - Winner -> _v_x_top + 1;
	boty = Winner -> _v_y_bot - Winner -> _v_y_top + 1;

	if (Winner -> _box_h)
	{
		topx--;
		topy--;
		botx += 2;
		boty += 2;
	}

	vputch (0);

	if (	(topx == 0) &&
		(topy == 0) &&
		(botx >= (SCRNLIN - 1)) &&
		(boty >= SCRWID))
	{
		clear ();
		return (TRUE);
	}
	else
	{
		SREGION = botx;
		topx += XBASE;
		topy += YBASE;
		botx += XBASE;
		boty += YBASE;
		eprintf (CWINDOW, topx, topy, botx, boty);
		eprintf (CLEAR);
	}

	topx = Winner -> _v_x_top;
	topy = Winner -> _v_y_top;
	botx = Winner -> _v_x_bot + 1;
	boty = Winner -> _v_y_bot + 1;

	if (Winner -> _box_h)
	{
		topx--;
		topy--;
		botx += 1;
		boty += 1;
	}

	for (i = topx; i < botx; i++)
	{
		for (j = topy, ptr = &cmap[i][j];
				j < boty; j++, ptr++)
		{
			if (IN)
				*ptr = 0;
			else
				*ptr = ' ';
		}
	}

	eprintf (CWINDOW,
			0 + XBASE,
			0 + YBASE,
			SCRNLIN + XBASE,
			SCRWID + 1 + YBASE);

	scrlin = scrcol = -100;
	w_xgo (Winner, x, y);

	return (TRUE);
}
