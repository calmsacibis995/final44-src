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
 *	Free_Field (field_ptr)
 *
 *	This procedure frees the space associated with the specified field.
 *	If the field has label, the labels are also freed.  This routine
 *	does not delete the fields or labels from the window display.
 *
 *
 *	Free_Label (label_ptr)
 *
 *	This procedure frees the space associated with the specified label.
 *	This routine does not delete the fields or labels from the window
 *	display.
 *
 */

Free_Field (field_ptr)
register struct field_item      *field_ptr;
{
	if (field_ptr == 0)	/* Already Freed */
		return;

	F_Ok (field_ptr, "Free_Field");

	if (field_ptr -> label)
		Free_Label (field_ptr -> label);

	if (field_ptr -> txbuf != 0)
		free (field_ptr -> txbuf);

	if ((field_ptr -> type == CMNUM) &&
		(field_ptr -> keywords != 0))
		free(field_ptr -> keywords);

	if ((field_ptr -> txflg & TXEXT) &&
		(field_ptr -> fill_char != 0))
		free (field_ptr -> fill_char);

	field_ptr -> _field_check = 0;

	free (field_ptr);
}

Free_Label (label_ptr)
register struct label_item *label_ptr;
{
	if (label_ptr == 0)	/* Already Freed */
		return;

	L_Ok (label_ptr, "Free_Label");

	if (label_ptr -> next)
		Free_Label (label_ptr -> next);

	label_ptr -> _label_check = 0;

	free (label_ptr);
}
