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
 *	Unlink_Fields (field1_ptr, field2_ptr)
 *
 *	This procedure unlinks to previously linked fields.
 *
 */

Unlink_Fields (field1_ptr, field2_ptr)
register struct field_item *field1_ptr;
register struct field_item *field2_ptr;
{
	extern char    *malloc ();
	register int count;

	F_Ok (field1_ptr, "Link_Fields");

	F_Ok (field2_ptr, "Link_Fields");

	if (field1_ptr -> type == CMNUM)
		field1_ptr -> read_routine = read_num;
	if (field2_ptr -> type == CMNUM)
		field2_ptr -> read_routine = read_num;
	field1_ptr -> fnflg &= ~(FNALT);
	if ((count = ((field2_ptr -> fnflg) >> FNLNSZ) - 1) <= 0)
	{
		field2_ptr -> fnflg = field2_ptr -> fnflg & FNLNMSK;
		field2_ptr -> fnflg &= ~(FNLINK);
		field2_ptr -> txbuf = malloc (field2_ptr -> length + 2 + MXTRA);
		if (field2_ptr -> txbuf == 0)
		{
			Print_Message (field2_ptr -> meswin, Mess_Attribute,
					"Cannot allocate field space.");
			return;
		}
	
		field2_ptr -> txend = &(field2_ptr -> txbuf[field2_ptr -> length + 1]);
	}
	else
		field2_ptr -> fnflg = (count << FNLNSZ) | (field2_ptr -> fnflg & FNLNMSK);
}
