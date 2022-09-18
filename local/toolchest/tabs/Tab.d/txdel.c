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
 *	txdel (field_ptr)
 *
 *	This function is called to delete a character.  It handles
 *	the external appearance in the field.
 *
 */

txdel (field_ptr)
register struct field_item *field_ptr;
{
	register char  *ptr1;
	register char  *ptr2;
	char   sbuf[FORM_BUF];
	int x;
	int y;
	int count;
	int width;

	if (field_ptr -> txcursor > field_ptr -> txbuf)
	{
		(field_ptr -> txcursor)--;
		count = 1;
		if ((field_ptr -> txcursor > field_ptr -> txbuf) &&
			(*(field_ptr -> txcursor - 1) == '\\'))
		
		{
			(field_ptr -> txcursor)--;
			count++;
		}
		width = 0;
		for (ptr1 = sbuf, ptr2 = field_ptr -> txbuf;
			ptr2 < field_ptr -> txcursor; ptr1++, ptr2++)
		{
			*ptr1 = *ptr2;
			width = fc_length (field_ptr -> y_pos, *ptr1, width);
		}
		x = field_ptr -> x_pos;
		y = field_ptr -> y_pos + width;
		ptr2 = ptr2 + count;
		for (; ptr2 < field_ptr -> txptr; ptr1++, ptr2++)
		{
			*ptr1 = *ptr2;
			width = fc_length (field_ptr -> y_pos, *ptr1, width);
		}
		*ptr1 = '\0';
		(field_ptr -> txptr) -= count;
		for (ptr1 = field_ptr -> txbuf, ptr2 = sbuf;
			ptr1 < field_ptr -> txptr; ptr1++, ptr2++)
		{
			*ptr1 = *ptr2;
		}
		if (field_ptr -> txcursor != field_ptr -> txptr)
		{
			*ptr1++ = '\0';
			*ptr1 = '\0';
		}
		w_xgo (field_ptr -> window, field_ptr -> x_pos, field_ptr -> y_pos);
		waxprintf (field_ptr -> window,
			field_ptr -> attribute | FAFIELD,
			"%s", sbuf);
		waxprintf (field_ptr -> window,
			field_ptr -> attribute | FAFIELD,
			"%s", &(field_ptr -> fill_char[width]));
		w_xgo (field_ptr -> window, x, y);
	}
	else
	{
		beep ();
	}
}
