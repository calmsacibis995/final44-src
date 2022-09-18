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
 *	cvadjust (Winner, xtop, ytop, xbot, ybot, ad_type, x)
 *
 *	This procedure adjusts (e.g. scrolls) the specified window.
 *	The adjustment is in the vertical position of line -- open
 *	(or close) lines on the screen.  The argument is the number
 *	of lines to add (or drop).
 *
 *	This routine is called internally.
 *
 *	The procedure currently assumes that you are using a
 *	Concept 100 terminal.  It tries to make affective use of
 *	windowing.  Note the little bit of virtualization in the
 *	escape lead in character.
 *
 */

cvadjust (Winner, xtop, ytop, xbot, ybot, ad_type, x)
struct window  *Winner;
int     xtop;
int     ytop;
int     xbot;
int     ybot;
int     ad_type;
int     x;
{
	register        i;
	int     oldx;

	if ((xtop == -1) ||
			(ytop == -1) ||
			((xbot - xtop) < 1) ||
			((ybot - ytop) < 1))
	{
		return (0);
	}

	xbot += 1;
	ybot += 1;

	eprintf (CWINDOW,
		xtop + XBASE,
		ytop + YBASE,
		xbot - xtop + XBASE,
		ybot - ytop + YBASE);

	scrlin = -100;
	scrcol = -100;
	oldx = xtop;

	if (x < 0)
	{
		x = -x;
		i = 1;
	}
	else
	{
		i = 0;
	}

	SREGION = xbot - xtop;
	if (i)
	{
		scrlin = scrcol = -100;

		mgo (xbot - xtop - 1, 0);

		for (i = 0; i < x; i++)
		{
			eprintf (SSCROLL);
		}

		wshift (xtop, ytop, xbot - 1, ybot - 1, x);
	}
	else
	{
		scrlin = scrcol = -100;
		mgo (0, 0);
		for (i = 0; i < x; i++)
		{
			eprintf (LOPEN);
		}

		wshift (xtop, ytop, xbot - 1, ybot - 1, -x);
	}

	eprintf (CWINDOW,
			0 + XBASE,
			0 + YBASE,
			SCRNLIN + XBASE,
			SCRWID + 1 + YBASE);

	scrlin = scrcol = -100;

	if (oldx != -1)
	{
		xgo (oldx, 0);
	}

	return (1);
}
