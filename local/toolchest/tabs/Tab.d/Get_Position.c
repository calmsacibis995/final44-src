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
 *	Get_Position (Winner, X, Y, help_string)
 *
 *	This procedure collects an (x,y) address from the user.  The values
 *	are returned in X and Y.  Most of the common methods for moving in
 *	a window are accepted, including mouse and function keys.
 *
 */

extern int hlp_status;

Get_Position (Winner, X, Y, help_string)
register struct window *Winner;
int    *X;
int    *Y;
char *help_string;
{
	register int     x;
	register int     y;

	char	*Format;
	int     c;

	int     upper_x;
	int     upper_y;
	int	lower_x;
	int	lower_y;
	struct	field_item field;
	struct field_item *o_F_Field;
	struct field_item *o_L_Field;

	W_Ok (Winner, "Get_Position");

	o_F_Field = _F_Field;
	o_L_Field = _L_Field;
	_F_Field = &field;
	_L_Field = &field;
	field.x_pos = (Winner -> _bot_x - Winner -> _top_x) / 2 + Winner -> _top_x;
	field.y_pos = (Winner -> _bot_y - Winner -> _top_y) / 2 + Winner -> _top_y;
	field.length = 0;
	field.window = Winner;
	field.errwin = errwindow;
	field.fnflg = 0;
	field.cmflg = CMHLP;
	field._field_check = GOOD_FIELD;

	Format = "Move the cursor to the desired location and enter a \".\" - row:%2d  col:%2d";

	upper_x = Winner -> _top_x;
	upper_y = Winner -> _top_y;
	lower_x = Winner -> _bot_x;
	lower_y = Winner -> _bot_y;

	xgo (mline, mcol);
	x = mline;
	y = mcol;

	Print_Message (Winner, 0, Format, x - upper_x, y - upper_y);
	xgo (mline, mcol);

	while ((c = getachar (0)) != '.')
	{

		switch (c)
		{
			case '?':
				hlp_status = HLP_OPTIONS;
				if ((help_string != 0) &&
					(*help_string != '\0'))
				{
					prhlp (&field, help_string, FALSE, FALSE);
				}
				prhlp (&field, "Mark a location on the screen.  ", FALSE, TRUE);
				prhlp (&field, "To mark a location move the cursor to it and enter a \".\".  ", FALSE, TRUE);
				prhlp (&field, "The cursor can be moved by entering one of the letters \"hjkl\".  ", FALSE, TRUE);
				prhlp (&field, "Tab, backtab, cursor keys, and the return key also move the cursor.", FALSE, FALSE);
				break;
			case K_MOUSE:
				x = MOUSE_X - Winner -> _top_x;
				y = MOUSE_Y - Winner -> _top_y;
				if (Winner -> _box_h)
				{
					x++;
					y++;
				}
				if (y < upper_y)
					y = upper_y;
				if (y > (lower_y - 1))
					y = (lower_y - 1);
				if (x < upper_x)
					x = upper_x;
				if (x > (lower_x - 1))
					x = (lower_x - 1);
				break;
			case K_HOME:
			case CTRL(A):
				x = upper_x;
				y = upper_y;
				break;
			case K_BOTTOM:
			case CTRL(Z):
				x = lower_x - 1;
				y = lower_y - 1;
				break;
			case 'h': 
			case K_LEFT:
			case CTRL(L):
			case CTRL(T):
				y--;
				if (y < upper_y)
					y = upper_y;
				break;
			case CRET:
				y = upper_y;
			case 'j':
			case NL:
			case K_DOWN:
			case FTABC:		/* Control-N */
			case CTRL(G):
				x++;
				if (x > (lower_x - 1))
					x = (lower_x - 1);
				break;
			case 'k': 
			case K_UP:
			case BTABC:		/* Back Tab */
			case CTRL(^):
				x--;
				if (x < upper_x)
					x = upper_x;
				break;
			case 'l': 
			case K_RIGHT:
			case CTRL(R):
			case CTRL(Y):
				y++;
				if (y > (lower_y - 1))
					y = (lower_y - 1);
				break;
			case TABC:
				y += TABSTOP - ((y - upper_y) % TABSTOP);
				if (y > (lower_y - 1))
					y = (lower_y - 1);
				break;
			case K_BTAB:
				y--;
				y -= ((y - upper_y) % TABSTOP);
				if (y < upper_y)
					y = upper_y;
				break;
			case CLEARC:		/* Clear */
				Push_Window (field.errwin);
				break;
			case REFRESHC:		/* Quick Refresh */
				Refresh ();
				break;
			default: 
				beep ();
		}

		Print_Message (Winner, 0, Format, x - upper_x, y - upper_y);
		mgo (x, y);
	}

	_F_Field = o_F_Field;
	_L_Field = o_L_Field;
	*X = x - upper_x;
	*Y = y - upper_y;
	Push_Window (field.errwin);
	Print_Message (Winner, 0, "\0");
}
