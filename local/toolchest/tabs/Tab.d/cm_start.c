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

cm_start (field_ptr, error1, error2)
register struct field_item *field_ptr;
register char *error1;
register char *error2;
{
	F_Ok (field_ptr, "cm_start");

	if ((field_ptr -> cmflg & CMHLP) && (field_ptr -> fnflg & FNSDH))
	{
		field_ptr -> cmflg |= CMNOP;
		return (FALSE);
	}

	if (*(field_ptr -> txbuf) == '\0')
	{
		if (field_ptr -> cmflg & CMCMP)
		{
			if (field_ptr -> fnflg & FNDEF)
			{
				deflt (field_ptr);
				field_ptr -> cmflg |= CMREP;
				return (FALSE);
			}
			else
			{
				field_ptr -> cmflg |= CMNOP | CMNUQ;
				error_fields = error1;
				return (FALSE);
			}
		}
		if (field_ptr -> cmflg & CMEOL)
		{
			field_ptr -> cmflg |= CMNOP;
			error_fields = error2;
			return (FALSE);
		}
	}
	return (TRUE);
}
