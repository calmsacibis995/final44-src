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
 *	Show_Field (field_ptr)
 *
 *	The procedure initializes the specified field.  This includes
 *	placing the field in its window.
 *
 */

Show_Field (field_ptr)
register struct field_item      *field_ptr;
{
	F_Ok (field_ptr, "Show_Field");

	if (field_ptr -> label) Show_Label (field_ptr, field_ptr -> label);

	cmini (field_ptr, TRUE);

	/* Initialize the field */

	if (!in_window (field_ptr))
			return;

	w_xgo (field_ptr -> window, field_ptr -> x_pos, field_ptr -> y_pos);

	waxprintf (field_ptr -> window, field_ptr -> attribute | FAFIELD,
			 "%s", field_ptr -> fill_char);
}
