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

in_window (field_ptr)
register struct field_item *field_ptr;
{
	return ((field_ptr -> x_pos >= 0) &&
		(field_ptr -> x_pos < (field_ptr -> window -> _bot_x -
				field_ptr -> window -> _top_x)) &&
		(field_ptr -> y_pos >= 0) &&
		(field_ptr -> y_pos < (field_ptr -> window -> _bot_y -
				field_ptr -> window -> _top_y)));
}
