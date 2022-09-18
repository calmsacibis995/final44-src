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
 *	Set_CMP_Default (field_ptr, string)
 *
 *	This procedure set the "completion default" for the specified
 *	field.  If the user enters a completion request (ESCAPE) in an
 *	empty field, the completion default is the value that will be
 *	completed.  It is an invisible sort of default value.  The
 *	procedure Show_Default_Field () is used to set visible default values.
 *
 */

Set_CMP_Default (field_ptr, string)
register struct field_item *field_ptr;
register char *string;
{
	F_Ok (field_ptr, "Set_CMP_Default");

	field_ptr -> fndfs = string;
	if ((string != 0) && (*string != '\0'))
		field_ptr -> fnflg |= FNDEF;
	else
		field_ptr -> fnflg &= ~(FNDEF);
}
