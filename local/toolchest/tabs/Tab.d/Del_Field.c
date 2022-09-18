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
 *	Del_Field (field_ptr)
 *
 *	This procedure deletes the specified field.  This only removes the
 *	field from the display.  It does not free any memory.  The field
 *	may be moved back into the display after it has been deleted.
 *
 *	Del_Label (field_ptr, label_ptr)
 *
 *	This procedure deletes the specified label.  This only removes the
 *	label from the display.  It does not free any memory.
 *
 */

Del_Field (field_ptr)
register struct field_item      *field_ptr;
{
	char    string[FORM_BUF];
	register char  *ptr;
	register char  *sptr;

	F_Ok (field_ptr, "Del_Field");

	if (field_ptr -> type == CMREGN)
	{
		Push_Window (((struct field_item **)field_ptr -> fnalt)[0] -> window, INVISIBLE);
		return;
	}

	if (!in_window (field_ptr))
			return;

	for (ptr = field_ptr -> fill_char, sptr = string; *ptr; ptr++)
	{
		*sptr++ = ' ';
	}
	*sptr = '\0';

	w_xgo (field_ptr -> window,
			field_ptr -> x_pos,
			field_ptr -> y_pos);

	wxprintf (field_ptr -> window, string);

	if (field_ptr -> label) Del_Label (field_ptr, field_ptr -> label);
}

Del_Label (field_ptr, label_ptr)
register struct field_item      *field_ptr;
register struct label_item      *label_ptr;
{
	register char  *ptr;
	register char  *sptr;
	char    string[FORM_BUF];
	int x;
	int y;
	int length;

	F_Ok (field_ptr, "Del_Field");

	L_Ok (label_ptr, "Del_Field");

	if (!in_window (field_ptr))
			return;

	x = field_ptr -> x_pos;
	y = field_ptr -> y_pos;

	length = f_length (y, field_ptr -> fill_char);

	for (ptr = label_ptr -> string, sptr = string; *ptr; ptr++)
	{
		*sptr++ = ' ';
	}
	*sptr = '\0';

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
		if (label_ptr -> next) Del_Label (field_ptr, label_ptr -> next);
		return;
	}

	if ((x < 0) ||
		(x > (field_ptr -> window -> _bot_x -
			field_ptr -> window -> _top_x)) )
	{
		if (label_ptr -> next)
			Del_Label (field_ptr, label_ptr -> next);
		return;
	}

	if ((y < 0) ||
		(y > (field_ptr -> window -> _bot_y -
			field_ptr -> window -> _top_y)) )
	{
		if (label_ptr -> next) Del_Label (field_ptr, label_ptr -> next);
		return;
	}

	w_xgo (field_ptr -> window, x, y);
	wxprintf (field_ptr -> window, string);

	if (label_ptr -> next) Del_Label (field_ptr, label_ptr -> next);
}
