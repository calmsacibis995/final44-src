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
 *	Field_Value (field_ptr, string)
 *
 *	This procedure places the value of the specified field in "string".
 *	This is hardly necessary from C, but a required procedure from
 *	most interpreted languages.
 *
 */

Field_Value (field_ptr, string)
register struct field_item     *field_ptr;
char   *string;
{
	F_Ok (field_ptr, "Field_Value");

	strcpy (string, field_ptr -> txbuf);
}
