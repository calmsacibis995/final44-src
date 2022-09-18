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
 *	Show_Label (field_ptr, label_ptr)
 *
 *	The procedure attaches the specified label item to the specified
 *	field.  Labels may appear in 4 directions around the field.
 *
 */

Show_Label (field_ptr, label_ptr)
register struct field_item      *field_ptr;
register struct label_item      *label_ptr;
{
	int x;
	int y;
	int length;

	if (!in_window (field_ptr))
			return;

	L_Ok (label_ptr, "Show_Label");

	x = field_ptr -> x_pos;
	y = field_ptr -> y_pos;

	length = f_length (y, field_ptr -> fill_char);

	switch (label_ptr -> where)
	{
	case 'a':		/* Above */
		x = field_ptr -> x_pos - 1;
		y += length / 2;
		y -= f_length (0, label_ptr -> string) / 2;
		if (y < 0) y = 0;
		break;

	case 'l':		/* Left */
		y = field_ptr -> y_pos - f_length (field_ptr -> y_pos, label_ptr -> string);
		break;

	case 'r':		/* Right */
		y = field_ptr -> y_pos + length;
		break;

	case 'b':		/* Below */
		x = field_ptr -> x_pos + 1;
		y += length / 2;
		y -= f_length (0, label_ptr -> string) / 2;
		if (y < 0) y = 0;
		break;

	default:
		if (label_ptr -> next) Show_Label (field_ptr, label_ptr -> next);
		return;
	}

	if (label_ptr -> next) Show_Label (field_ptr, label_ptr -> next);

	if ((x < 0) ||
		(x > (field_ptr -> window -> _bot_x -
			field_ptr -> window -> _top_x - 1)) )
	{
		return;
	}

	if ((y < 0) ||
		(y > (field_ptr -> window -> _bot_y -
			field_ptr -> window -> _top_y - 1)) )
	{
		return;
	}

	w_xgo (field_ptr -> window, x, y);
	waxprintf (field_ptr -> window, label_ptr -> attribute,
		"%s", label_ptr -> string);
}
