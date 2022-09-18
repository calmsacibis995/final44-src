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
 *	cmcfm (field_ptr)
 *
 *	This function matches an end of line - signified by CMEOL.
 *
 */

cmcfm (field_ptr)
register struct field_item    *field_ptr;
{
	_cmcfm (field_ptr, TRUE);
}

cmcfm2 (field_ptr)
register struct field_item    *field_ptr;
{
	_cmcfm (field_ptr, FALSE);
}

_cmcfm (field_ptr, cfm_type)
register struct field_item    *field_ptr;
boole cfm_type;
{
	char *error;

	error = "Confirmation field";

	if ((field_ptr -> cmflg & CMHLP) &&
			((field_ptr -> fnflg & FNHLP) == 0) &&
			((field_ptr -> fnflg & FNSDH) == 0))
	{
		prhlp (field_ptr, "Press the return key.", FALSE, FALSE);
		field_ptr -> cmflg |= CMNOP;
		return;
	}

	if (field_ptr -> cmflg & CMCMP)		
	{
		field_ptr -> cmflg |= CMNOP;
		error_fields = error;
		return;
	}

	if (field_ptr -> cmflg & CMEOL)		
	{
		if ((cfm_type) &&
			(*(field_ptr -> txbuf)))
		{
			field_ptr -> cmflg |= CMNOP;
			error_fields = error;
			return;
		}
		else
		{
			complete (field_ptr, field_ptr -> txbuf);
			if (field_ptr -> cmflg & CMCMP)
			{
				field_ptr -> cmflg |= CMREP;
				field_ptr -> cmflg &= ~CMEOL;
			}
			return;
		}
	}

	field_ptr -> cmflg |= CMNOP;
	error_fields = error;
}
