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
 *	Show_Default_Field (field_ptr, string)
 *
 *	The procedure sets the default value of the specified field to
 *	the value in string.  This procedure will cause the field to be
 *	displayed (like Show_Field () ).  No type checking is done on the
 *	default value.
 *
 */

Show_Default_Field (field_ptr, string)
register struct field_item      *field_ptr;
register char   *string;
{
	F_Ok (field_ptr, "Show_Default_Field");

	if (field_ptr -> label) Show_Label (field_ptr, field_ptr -> label);

	cmini (field_ptr, FALSE);

	/* Initialize the field */

	if (f_length (field_ptr -> y_pos, string) > field_ptr -> length)
	{
		Print_Message (field_ptr -> meswin, Mess_Attribute,
				"Default value longer than field: %s", string);
		w_xgo (field_ptr -> window,
				field_ptr -> x_pos,
				field_ptr -> y_pos);
		return;
	}

	if (field_ptr -> txbuf != string)
		strcpy (field_ptr -> txbuf, string);
	field_ptr -> txptr = &(field_ptr ->
			txbuf[strlen (field_ptr -> txbuf)]);
	if (_Entry_Type == FAR_LEFT)
		field_ptr -> txcursor = field_ptr -> txbuf;
	else
		field_ptr -> txcursor = field_ptr -> txptr;

	if (field_ptr -> type == CMKEY_LIST)
	{
		field_ptr -> cmflg |= CMEOL;
		cmkey_list (field_ptr);
		cmini (field_ptr, FALSE);
	}

	if (!in_window (field_ptr))
			return;

	if (field_ptr -> attribute & FARIGHT)
		Right_Field (field_ptr);
	else if (field_ptr -> attribute & FACENTER)
		Center_Field (field_ptr);
	else
		Left_Field (field_ptr);
}
