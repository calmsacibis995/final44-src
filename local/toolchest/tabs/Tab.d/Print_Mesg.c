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

/*
 *	Print_Message (Winner, attribute, a, b, c, d, e, f, g, h)
 *
 *	The procedure prints a formated error or warning message on
 *	the last line of the specified window.
 *
 */

Print_Message (Winner, attribute, a, b, c, d, e, f, g, h)
struct window  *Winner;
int     attribute;
{
	register char   *ptr;
	register int     f_length;
	int     x;
	int     y;
	int     same_window;
	char    sbuf[FORM_BUF];

	W_Ok (Winner, "Print_Message");

	if (((Winner -> _top_x + Winner -> _x_pos) == mline) &&
		((Winner -> _top_y + Winner -> _y_pos) == mcol))
	{
		x = Winner -> _x_pos;
		y = Winner -> _y_pos;
		same_window = TRUE;
	}
	else
	{
		x = mline;
		y = mcol;
		same_window = FALSE;
	}

	sprintf (sbuf, a, b, c, d, e, f, g, h);

	f_length = Winner -> _top_y;
	ptr = sbuf;
	while (*ptr)
	{
		f_length = fc_length (0, *ptr, f_length);
		if (f_length >= Winner -> _bot_y)
		{
			*ptr = '\0';
			break;
		}

		ptr++;
	}

	w_xgo (Winner, Winner -> _bot_x - Winner -> _top_x - 1, 0);

	waxprintf (Winner, attribute, "%s", sbuf);

	wclrl (Winner);

	if (same_window)
		w_xgo (Winner, x, y);
	else
		xgo (x, y);

	fflush (stdout);
}
