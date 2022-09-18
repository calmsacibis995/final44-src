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
 *	regchar (field_ptr, c)
 *
 *	This function handles regular characters as input.  This routine
 *	should probably be converted to wxputl() - lacks purity.
 *
 */

regchar (field_ptr, c)
register struct field_item  *field_ptr;
char   c;
{
	char save;
	register char *ptr1;
	register char *ptr2;
	int x;
	int y;

	if (field_ptr -> txptr == field_ptr -> txcursor)
	{
		*((field_ptr -> txptr)++) = c;
		field_ptr -> txcursor++;
		waxprintf (field_ptr -> window,
			field_ptr -> attribute | FAFIELD,
			"%c", c);
	}
	else
	{
		waxprintf (field_ptr -> window,
			field_ptr -> attribute | FAFIELD,
			"%c", c);	/* location */

		if (_Editing_Type == OVERLAY)
			*(field_ptr -> txcursor)++ = c;

		x = field_ptr -> window -> _x_pos;
		y = field_ptr -> window -> _y_pos;
		save = *(field_ptr -> txptr);
		*(field_ptr -> txptr) = '\0';
		waxprintf (field_ptr -> window,
			field_ptr -> attribute | FAFIELD,
			"%s", field_ptr -> txcursor);
		*(field_ptr -> txptr) = save;

		if (_Editing_Type == INSERT)
		{
			for (ptr1 = (field_ptr -> txptr + 1), ptr2 = field_ptr ->txptr;
					ptr1 > field_ptr -> txcursor; ptr1--, ptr2--)
			{
				*ptr1 = *ptr2;
			}
			*(field_ptr -> txcursor)++ = c;
			(field_ptr -> txptr)++;
		}

		w_xgo (field_ptr -> window, x, y);
	}

	return (FALSE);
}
