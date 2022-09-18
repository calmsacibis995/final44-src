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
 *	complete (field_ptr, string)
 *
 *	When one of the parsing functions (cm...) wishes to
 *	indicate that it has succeeded in matching the current
 *	field it calls complete.  The string that is passed is
 *	the full match for the field, which is used if the user
 *	typed <escape>.
 */

complete (field_ptr, string)
struct field_item     *field_ptr;
char    string[];
{
	register char  *ptr;
	register char  *s;
	char *f;
	register char   c;
	int length;
	int x;
	int y;

	if (field_ptr -> cmflg & CMCMP)
	{
		for (ptr = field_ptr -> txbuf, s = string, length = 0;
		    	 		*ptr && *s; ptr++, s++)
		{
			length = fc_length (field_ptr -> y_pos, *ptr, length);
			*ptr = *s;
		}

		c = *s++;
		while (c != '\0')
		{
			length = fc_length (field_ptr -> y_pos, c, length);
			if (length > field_ptr -> length)
			{
				field_ptr -> cmflg |= (CMNOP);
				field_ptr -> txptr = field_ptr -> txbuf;
				field_ptr -> txcursor = field_ptr -> txbuf;
				return;
			}

			*ptr++ = c;
			c = *s++;
		}

		*ptr = '\0';
		field_ptr -> txptr = ptr;
		field_ptr -> txcursor = ptr;

		w_xgo (field_ptr -> window,
			field_ptr -> x_pos,
			field_ptr -> y_pos);

		waxprintf (field_ptr -> window, field_ptr -> attribute | FAFIELD,
			"%s", field_ptr -> txbuf);
		x = field_ptr -> window -> _x_pos;
		y = field_ptr -> window -> _y_pos;
		waxprintf (field_ptr -> window, field_ptr -> attribute | FAFIELD,
			"%s", &field_ptr -> fill_char[length]);
		w_xgo (field_ptr -> window, x, y);
	}

	field_ptr -> cmflg &= ~(CMNOP);
}
