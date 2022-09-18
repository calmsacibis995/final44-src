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

F_Ok (field_ptr, message)
register struct field_item *field_ptr;
char *message;
{
	if ((field_ptr >= _F_Field) &&
		(field_ptr <= _L_Field))
	{
		if (field_ptr -> _field_check == GOOD_FIELD)
			return;		/* Not checking the return */
	}

	_illegal_pointer (message, ": Illegal field pointer.");
}

L_Ok (label_ptr, message)
register struct label_item *label_ptr;
char *message;
{
	if ((label_ptr >= _F_Label) &&
		(label_ptr <= _L_Label))
	{
		if (label_ptr -> _label_check == GOOD_FIELD)
			return;		/* Not checking the return */
	}

	_illegal_pointer (message, ": Illegal label pointer.");
}
