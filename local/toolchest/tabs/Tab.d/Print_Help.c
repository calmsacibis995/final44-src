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
 *	Print_Help_Window (field_ptr, attribute, a, b, c, d, e, f, g, h)
 *
 *	This procedure prints to the error window of the specified field.
 *	If the error window is not at level 0 it is moved into place.
 *	Argument "a" is the formating string.
 *
 */

Print_Help_Window (field_ptr, attribute, a, b, c, d, e, f, g, h)
register struct field_item      *field_ptr;
int     attribute;
{
	int     y;
	int     x;

	F_Ok (field_ptr, "Print_Help_Window");

	W_Ok (field_ptr -> errwin, "Print_Help_Window");

	if (field_ptr -> errwin -> _depth != 0)
	{
		if (field_ptr -> errwin == errwindow)
		{
			y = (field_ptr -> y_pos + field_ptr -> window -> _top_y) -
				(field_ptr -> errwin -> _bot_y -
					field_ptr -> errwin -> _top_y) / 2;
	
			x = field_ptr -> x_pos + field_ptr -> window -> _top_x + 3;
			if ((x + (field_ptr -> errwin -> _bot_x -
					field_ptr -> errwin -> _top_x))
							>= (SCRNLIN - 3))
			{
				x = field_ptr -> x_pos + field_ptr -> window -> _top_x
					- 2 - (field_ptr -> errwin -> _bot_x -
						field_ptr -> errwin -> _top_x);
			}
		}
		else
		{
			x = field_ptr -> errwin -> _top_x;
			y = field_ptr -> errwin -> _top_y;
		}
		s_werase (field_ptr -> errwin);
		w_xgo (field_ptr -> errwin, 0, 0);
		Move_Window (field_ptr -> errwin, x, y, 0);
		if (!CWINDOW)	/* Clear then Box */
			Wrefresh (field_ptr -> errwin);
		Ref_All_Windows ();
	}

	waxprintf (field_ptr -> errwin, attribute, a, b, c, d, e, f, g, h);
}
