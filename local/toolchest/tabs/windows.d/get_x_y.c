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
 *	get_x_y (ret_window, X, Y, omline, omcol, windowp)
 *
 *	This procedure gets and (x,y) postion from the end user.
 *	Movement on the screen is restricted to points below and to the
 *	left of (omline, omcol).  If windowp is TRUE window names
 *	(A,B,C,...) may also be used to specify the location.
 *
 *	A pointer to the window located at the specified position is
 *	returned in ret_window.
 *
 */

void
get_x_y (ret_window, X, Y, omline, omcol, windowp)
struct window **ret_window;
int    *X;
int    *Y;
int     omline;
int     omcol;
int     windowp;
{
	char    c;
	int     x;
	int     y;
	int     j;
	unsigned int    key;

	mgo (mline, mcol);
	x = mline;
	y = mcol;
	while ((c = mgetchar ()) != '.')
	{
		if ((windowp) &&
				(c >= 'A') && (c <= ('A' + TOTAL_WINDOWS)))
		{
			j = c - 'A' + 1;
			if (_Windows[j]._bot_x > 0)
			{
				x = _Windows[j]._top_x;
				y = _Windows[j]._top_y;
				*ret_window = &_Windows[j];
				mgo (x, y);
				*X = x;
				*Y = y;
				return;
			}
			beep ();
			continue;
		}

		switch (c)
		{
			case 'h': 
				y--;
				if (y < omcol)
					y = omcol;
				break;
			case 'j': 
				x++;
				if (x > SCRNLIN - 2)
					x = SCRNLIN - 2;
				break;
			case 'k': 
				x--;
				if (x < omline)
					x = omline;
				break;
			case 'l': 
				y++;
				if (y > SCRWID)
					y = SCRWID;
				break;
			default: 
				beep ();
		}
		mgo (x, y);
	}

	key = kmap[x][y];
	for (j = 0; j < TOTAL_WINDOWS; j++)
	{
		if ((_Windows[j]._bot_x) &&
				(key & _Windows[j]._key))
		{
			*ret_window = &_Windows[j];
			break;
		}
	}

	*X = x;
	*Y = y;
}
