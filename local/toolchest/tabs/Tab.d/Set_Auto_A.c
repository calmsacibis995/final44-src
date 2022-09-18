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
 *	Set_Auto_Advance (field_ptr, state)
 *
 *	The procedure sets the auto advance (advance when complete) flag
 *	for the specified field.
 *
 */

Set_Auto_Advance (field_ptr, state)
register struct field_item      *field_ptr;
register boole state;
{
	F_Ok (field_ptr, "Set_Auto_Advance");

	if (state)
	{
		field_ptr -> txflg |= TXAUTO;
	}
	else
	{
		field_ptr -> txflg &= ~(TXAUTO);
	}
	if (field_ptr -> fnflg & FNALT)
		Set_Auto_Advance (field_ptr -> fnalt, state);
}
