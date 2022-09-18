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
 *	Set_Error (field_ptr, message)
 *
 *	This procedure sets the error message associated with the specified
 *	field.
 *
 */

Set_Error (field_ptr, message)
register struct field_item *field_ptr;
register char *message;
{
	F_Ok (field_ptr, "Set_Error");

	if ((message) && (*message == '\0'))
		field_ptr -> fnerr = 0;
	else
		field_ptr -> fnerr = message;
}
