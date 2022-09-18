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
#include "fields.h"

/*
 *	cmstr (field_ptr)
 *
 *	This function matches an arbitrary string.  The only thing
 *	it does not match is the null string.  Stings may contain
 *	embedded blanks.
 */

cmstr (field_ptr)
register struct field_item     *field_ptr;
{
	char *error;

	error = "Cannot match or complete strings";

	if (!cm_start (field_ptr, error, error)) return;

	if (field_ptr -> cmflg & CMHLP)
	{
		field_ptr -> cmflg |= CMNOP;

		if (field_ptr -> fnflg & FNHLP)
			return;

		prhlp (field_ptr, "Enter some letters.", FALSE, FALSE);

		return;
	}

	if (field_ptr -> cmflg & CMCMP)
	{
		complete (field_ptr, field_ptr -> txbuf);
		field_ptr -> cmflg |= CMREP;
	}
	return;
}
