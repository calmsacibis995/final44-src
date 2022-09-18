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
 *	Set_An_Attribute (field_ptr, flags)
 *
 *	This procedure sets the attribute flags associated with the specified
 *	field.  Attributes include left, right, and center for formatting,
 *	and the visual attributes. The attributes can be set one at a time
 *	or in one call.
 *
 *	Un_Set_An_Attribute (field_ptr, flags)
 *
 *	This procedure deletes an attribute.
 */

Set_An_Attribute (field_ptr, flags)
register struct field_item *field_ptr;
register int flags;
{
	F_Ok (field_ptr, "Set_An_Attribute");

	field_ptr -> attribute = field_ptr -> attribute | flags;

	if (field_ptr -> fnflg & FNALT)
		Set_An_Attribute (field_ptr -> fnalt, flags);
}

Un_Set_An_Attribute (field_ptr, flags)
register struct field_item *field_ptr;
register int flags;
{
	F_Ok (field_ptr, "Un_Set_An_Attribute");

	field_ptr -> attribute = field_ptr -> attribute & (~flags);

	if (field_ptr -> fnflg & FNALT)
		Un_Set_An_Attribute (field_ptr -> fnalt, flags);
}
