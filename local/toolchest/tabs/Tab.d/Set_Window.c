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
#include <termio.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	Set_Window (field_ptr, Winner1, Winner2, Winner3)
 *
 *	The procedure sets the standard window, error window, and message
 *	window for the specified field.
 *
 */

Set_Window (field_ptr, Winner1, Winner2, Winner3)
register struct field_item *field_ptr;
register struct window *Winner1;
register struct window *Winner2;
struct window *Winner3;
{
	F_Ok (field_ptr, "Set_Window");

	if (field_ptr -> type == CMREGN)
		return;

	if (Winner1)
	{
		W_Ok (Winner1, "Set_Window");
		field_ptr -> window = Winner1;
	}

	if (Winner2)
	{
		W_Ok (Winner2, "Set_Window");
		field_ptr -> errwin = Winner2;
	}

	if (Winner3)
	{
		W_Ok (Winner3, "Set_Window");
		field_ptr -> meswin = Winner3;
	}

	if (field_ptr -> fnflg & FNALT)
		Set_Window (field_ptr -> fnalt, Winner1, Winner2, Winner3);
}
