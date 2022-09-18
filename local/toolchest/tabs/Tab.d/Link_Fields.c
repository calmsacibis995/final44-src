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
 *	Link_Fields (field1_ptr, field2_ptr)
 *
 *	This procedure links field2 to field1.  When getting input to
 *	field1, field2 will be used as an alternate.  This provides a
 *	mechanism to reading two types from the same field.
 *
 *	Many of the functions and procedures look for alternates.
 *
 */

Link_Fields (field1_ptr, field2_ptr)
register struct field_item *field1_ptr;
register struct field_item *field2_ptr;
{
	register int count;

	F_Ok (field1_ptr, "Link_Fields");

	F_Ok (field2_ptr, "Link_Fields");

	if (field2_ptr -> type == CMREGN)
	{
		beep ();
		Print_Message (stdwindow, FANORMAL,
			"Cannot link CMREGN fields!");
		return;
	}

	if (field2_ptr -> type != CMCFM)
		field1_ptr -> read_routine = getachar;
	field2_ptr -> read_routine = getachar;

	field1_ptr -> fnalt = field2_ptr;
	field1_ptr -> fnflg |= FNALT;
	if ((field2_ptr -> fnflg & FNLINK) == 0)
	{
		if (field2_ptr -> txbuf)
			free (field2_ptr -> txbuf);
		field2_ptr -> fnflg = (field2_ptr -> fnflg & FNLNMSK) | FNLINK;
	}
	count = ((field2_ptr -> fnflg) >> FNLNSZ) + 1;
	field2_ptr -> fnflg = (count << FNLNSZ) | (field2_ptr -> fnflg & FNLNMSK);
	field2_ptr -> txflg = field1_ptr -> txflg;
	field2_ptr -> txbuf = 0;
	field2_ptr -> txptr = field1_ptr -> txptr;
	field2_ptr -> txcursor = field1_ptr -> txcursor;
	field2_ptr -> txend = field1_ptr -> txend;
	field2_ptr -> cmflg = field1_ptr -> cmflg;

	field2_ptr -> window = field1_ptr -> window;
	field2_ptr -> errwin = field1_ptr -> errwin;
	field2_ptr -> meswin = field1_ptr -> meswin;
	field2_ptr -> x_pos = field1_ptr -> x_pos;
	field2_ptr -> y_pos = field1_ptr -> y_pos;
}
