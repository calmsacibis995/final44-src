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
 *	Set_EOF (field_ptr, eof_state, eof_verify)
 *
 *	The procedure sets state flag for enabling EOF exit from the
 *	specified field.
 *
 */

Set_EOF (field_ptr, eof_state, eof_verify)
register struct field_item      *field_ptr;
boole eof_state;
boole eof_verify;
{
	F_Ok (field_ptr, "Set_EOF");

	if (eof_state)
		field_ptr -> txflg |= (TXSEOF);
	else
		field_ptr -> txflg &= ~(TXSEOF);

	if (eof_verify)
		field_ptr -> txflg |= (TXEFVFY);
	else
		field_ptr -> txflg &= ~(TXEFVFY);

	if (field_ptr -> fnflg & FNALT)
		Set_EOF (field_ptr -> fnalt, eof_state, eof_verify);
}
