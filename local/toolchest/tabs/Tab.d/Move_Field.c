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
 *	Move_Field (field_ptr, x, y, Winner)
 *
 *	The procedure moves the specified field to the (x,y) position in
 *	the specified window.  The old position is deleted.  If no window
 *	is specified the old window is assumed.
 *
 */

Move_Field (field_ptr, x, y, Winner)
register struct field_item      *field_ptr;
register int     x;
register int     y;
struct window *Winner;
{
	struct field_item **f;
	int depth;

	F_Ok (field_ptr, "Move_Field");

	if (field_ptr -> type == CMREGN)
	{
		if (Winner)
			field_ptr -> window = Winner;
	
		field_ptr -> x_pos = x;
		field_ptr -> y_pos = y;

		f = (struct field_item **) field_ptr -> fnalt;

		Move_Window (f[0] -> window,
			field_ptr -> window -> _top_x + x,
			field_ptr -> window -> _top_y + y,
			field_ptr -> window -> _depth - 1);

		Ref_All_Windows ();

		return;
	}

	if (in_window (field_ptr))
		Del_Field (field_ptr);

	if (Winner)
		field_ptr -> window = Winner;

	field_ptr -> x_pos = x;
	field_ptr -> y_pos = y;

	if (in_window (field_ptr))
	{
		if (field_ptr -> label)
			Show_Label (field_ptr, field_ptr -> label);

		if (field_ptr -> attribute & FARIGHT)
			Right_Field (field_ptr);
		else if (field_ptr -> attribute & FACENTER)
			Center_Field (field_ptr);
		else
			Left_Field (field_ptr);
	}
}
