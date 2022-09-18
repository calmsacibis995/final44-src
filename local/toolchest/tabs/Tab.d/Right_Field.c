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
 *	Right_Field (field_ptr)
 *
 *	The procedure right justifies the current value of the specified field.
 *
 *	RightString (Winner, x, y, fill_char, value)
 *
 *	The procedure right justifies the specified value at position (x,y)
 *	in the specified window.  fill_char is used as background text.
 *
 *	Left_Field (field_ptr)
 *
 *	The procedure left justifies the current value of the specified field.
 *
 *	LeftString (Winner, x, y, fill_char, value)
 *
 *	The procedure left justifies the specified value at position (x,y)
 *	in the specified window.  fill_char is used as background text.
 *
 *	Center_Field (field_ptr)
 *
 *	The procedure centers the current value of the specified field.
 *
 *	CenterString (Winner, x, y, fill_char, value)
 *
 *	The procedure centers the specified value at position (x,y)
 *	in the specified window.  fill_char is used as background text.
 *
 */

Right_Field (field_ptr)
register struct field_item      *field_ptr;
{
	F_Ok (field_ptr, "Right_Field");

	field_ptr -> cmflg |= CMTAMPR;

	if (!in_window (field_ptr))
			return;

	RightString (field_ptr -> window,
			field_ptr -> x_pos,
			field_ptr -> y_pos,
			field_ptr -> fill_char,
			field_ptr -> txbuf,
			field_ptr -> attribute);
}

RightString (Winner, x, y, fill_char, value, attribute)
struct window *Winner;
int x;
int y;
char *fill_char;
char *value;
{
	register int     len;
	int     len_fill;
	int	ret;

	len = f_length (y, value);
	len_fill = strlen (fill_char);
	len = len_fill - len;
	ret = TRUE;
	while (_just (Winner, len, len_fill, value, x, y, fill_char, ret, attribute) == FALSE)
	{
		len--;
		if (len <= 0)
		{
			ret = FALSE;
			len = 0;
		}
	}
}

Left_Field (field_ptr)
register struct field_item      *field_ptr;
{
	F_Ok (field_ptr, "Left_Field");

	field_ptr -> cmflg |= CMTAMPR;

	if (!in_window (field_ptr))
			return;

	LeftString (field_ptr -> window,
			field_ptr -> x_pos,
			field_ptr -> y_pos,
			field_ptr -> fill_char,
			field_ptr -> txbuf,
			field_ptr -> attribute);
}

LeftString (Winner, x, y, fill_char, value, attribute)
struct window *Winner;
int x;
int y;
char *fill_char;
char *value;
{
	int     len_fill;

	len_fill = strlen (fill_char);
	_just (Winner, 0, len_fill, value, x, y, fill_char, FALSE, attribute);
}

Center_Field (field_ptr)
register struct field_item      *field_ptr;
{
	F_Ok (field_ptr, "Center_Field");

	field_ptr -> cmflg |= CMTAMPR;

	if (!in_window (field_ptr))
			return;

	CenterString (field_ptr -> window,
			field_ptr -> x_pos,
			field_ptr -> y_pos,
			field_ptr -> fill_char,
			field_ptr -> txbuf,
			field_ptr -> attribute);
}

CenterString (Winner, x, y, fill_char, value, attribute)
struct window *Winner;
int x;
int y;
char *fill_char;
char *value;
{
	register int     len;
	int     len_fill;
	int	ret;

	len = f_length (y, value);
	len_fill = strlen (fill_char);
	len = (len_fill - len) / 2;
	ret = TRUE;
	while (_just (Winner, len, len_fill, value, x, y, fill_char, ret, attribute) == FALSE)
	{
		len--;
		if (len <= 0)
		{
			ret = FALSE;
			len = 0;
		}
	}
}

static int
_just (Winner, len, len_fill, value, x, y, fill_char, ret, attribute)
struct window *Winner;
register int len;
register int len_fill;
char *value;
int x;
int y;
char *fill_char;
boole ret;
int attribute;
{
	register char *ptr;
	char    string[FORM_BUF];
	int index;

	strcpy (string, fill_char);

	if (len < 0) len = 0;

	for (ptr = value; (*ptr) && (len < len_fill); len++, ptr++)
	{
		switch (ptype[*ptr])
		{
			case TAB:
				index = len;
				len = fc_length (y, *ptr, len);
				if (len > index) len--;
				if (len >= len_fill)
				{
					if (ret) return (FALSE);
					len = len_fill - 1;
				}
				for (; index <= len; index++)
					string[index] = ' ';
				break;
		
			case CONTRL:
			case BACKSP:
				string[len] = '^';
				len++;
				if (len < len_fill) string[len] = *ptr + 0100;
				else if (ret) return (FALSE);
				break;
		
			case PLAIN:
			case UL:
			default:
				string[len] = *ptr;
		}
	}
	if ((ret) && (*ptr)) return (FALSE);
	string[len_fill] = '\0';
	w_xgo (Winner, x, y);
	waxprintf (Winner, attribute | FAFIELD, "%s", string);
	return (TRUE);
}
