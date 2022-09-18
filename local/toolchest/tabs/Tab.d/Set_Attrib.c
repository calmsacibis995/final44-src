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
 *	Set_Attributes (field_ptr, flags)
 *
 *	This procedure sets the attribute flags associated with the specified
 *	field.  Attributes include left, right, and center for formatting,
 *	and the visual attributes.  The visual attributes are as yet
 *	implemented.
 *
 */

Set_Attributes (field_ptr, flags)
register struct field_item *field_ptr;
register int flags;
{
	F_Ok (field_ptr, "Set_Attributes");

	field_ptr -> attribute = flags;

	if (field_ptr -> fnflg & FNALT)
		Set_Attributes (field_ptr -> fnalt, flags);
}
