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
 *	wvadjust (Winner, xt, yt, xb, yb, ad_type, xlines)
 *
 *	This procedure adjusts the vertical position of a line with in a
 *	window -- open (or close) lines on the screen.  The argument
 *	xlines is the number of lines to add (or drop).
 *
 */

void
wvadjust (Winner, xt, yt, xb, yb, ad_type, xlines)
struct window  *Winner;
int     xt;
int     yt;
int     xb;
int     yb;
int     ad_type;
int     xlines;
{
	register unsigned int  *pk;
	register CHAR  *p1;
	register CHAR  *p2;
	register CHAR  *xmap;
	int     k;
	CHAR    pbuf[NSCRCOL];
	int     i;
	int     j;
	int     x;
	int     y;

	W_Ok (Winner, "wvadjust");	/* Die on Illegal Window */

	if ((xt == (-1)) ||
		(xb == (-1)) ||
		(yt == (-1)) ||
		(yb == (-1)) )
	{
		wscroll (Winner, -xlines);
		Wrefresh (Winner);
		return;
	}

	w_xgo (Winner, Winner -> _x_pos, Winner -> _y_pos);

	x = Winner -> _x_pos;
	y = Winner -> _y_pos;

	for (i = xt; i <= xb; i++)
	{
		p1 = cmap[i];
		p2 = cmap2[i];
		for (j = 0; j < SCRWID + 1; j++)
		{
			*p2++ = *p1++;
		}
	}

	if (CWINDOW)
	{
		cvadjust (Winner, xt, yt, xb, yb, ad_type, xlines);

	}
	else
	{
		vadjust (xt, xb, xlines);
	}
	if (ad_type)
		wscroll (Winner, -xlines);
	else
		xwscroll (Winner, xt, -xlines);


	for (i = xt; i <= xb; i++)
	{
		j = Winner -> _top_y;
		p1 = Winner -> _map[i - Winner -> _top_x];
		p2 = &cmap2[i][j];
		pk = &kmap[i][j];
		for (; j < Winner -> _bot_y; j++, p1++, p2++, pk++)
		{
			if (Winner -> _key & *pk)
				*p2 = *p1;
		}
	}

	for (i = xt, j = 0; i <= xb; i++, j++)
	{
		p1 = pbuf;
		p2 = cmap[i];
		xmap = cmap2[i];
		for (k = 0; k < SCRWID + 1; k++, xmap++, p1++, p2++)
		{
			*p1 = *xmap;

			if (*p1 == 0)
				*p1 = ' ';
		}
		*p1 = 0;
		mline = i;
		mcol = 0;

		wcflush (pbuf, k, k);
	}

	w_xgo (Winner, x, y);
}
