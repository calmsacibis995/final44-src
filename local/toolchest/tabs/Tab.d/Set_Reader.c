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

Set_Reader (field_ptr, function)
register struct field_item *field_ptr;
int     (*function) ();
{
	F_Ok (field_ptr, "Set_Reader");

	field_ptr -> read_routine = function;
}
