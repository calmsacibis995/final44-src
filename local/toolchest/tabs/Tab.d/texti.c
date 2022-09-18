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
 *	texti (field_ptr)
 *
 *	This function reads input until the field is full or a break
 *	character is entered.
 *
 */

texti (field_ptr)
register struct field_item     *field_ptr;
{
	register int    flag;
	register int    rc;
	char    rchar;
	char   *FULL;
	char   *PROTECTED;
	char   *HELP;
	char    saved;
	int     old_x;
	int     old_y;
	int     width;

	FULL = "The current field is full";
	PROTECTED = "The current field is protected";

	field_ptr -> txflg &= ~(TXEOF | TXBRK | TXBLR);

	if (field_ptr -> txcursor > field_ptr -> txptr)
		field_ptr -> txcursor = field_ptr -> txptr;
	else if( field_ptr -> txcursor < field_ptr -> txbuf )
		field_ptr -> txcursor = field_ptr -> txbuf;

	w_xgo (field_ptr -> window, field_ptr -> x_pos, field_ptr -> y_pos);

	saved = *field_ptr -> txcursor;
	*field_ptr -> txcursor = '\0';
	waxprintf (field_ptr -> window,
		field_ptr -> attribute | FAFIELD,
		"%s", field_ptr -> txbuf);
	*field_ptr -> txcursor = saved;

	old_x = field_ptr -> window -> _x_pos;
	old_y = field_ptr -> window -> _y_pos;

	saved = *field_ptr -> txptr;
	*field_ptr -> txptr = '\0';
	waxprintf (field_ptr -> window,
		field_ptr -> attribute | FAFIELD,
		"%s", field_ptr -> txcursor);
	*field_ptr -> txptr = saved;

	width = _f_width (field_ptr);
	waxprintf (field_ptr -> window,
		field_ptr -> attribute | FAFIELD,
		"%s", &(field_ptr -> fill_char[width]));

	w_xgo (field_ptr -> window, old_x, old_y);

	while (field_ptr -> txptr < field_ptr -> txend)
	{
		rc = (*field_ptr -> read_routine) (field_ptr);
		rchar = rc;
		if (field_ptr -> cmflg & CMTAMPR)
		{
			width = _f_width (field_ptr);
			field_ptr -> cmflg &= ~(CMTAMPR);
		}

		if (*(field_ptr -> txcursor - 1) == '\\')
		{
			if (field_ptr -> txptr == field_ptr -> txcursor)
				width = fc_length (field_ptr -> y_pos,
						rchar, width);
			else
				width = _f_insert_width (field_ptr, rchar);

			if( width > field_ptr -> length )
			{
				beep ();
				Print_Message (field_ptr -> meswin, Mess_Attribute, "%s %s",
						FULL, Help_Help_String);
				if ((field_ptr -> txptr == field_ptr -> txcursor) &&
				   (*(field_ptr -> txptr - 1) == '\\'))
				{
					txdel (field_ptr);
				}
				width = _f_width (field_ptr);
				continue;
			}

			if (((rc & 0200) == 0) &&
					(rc != 0))
			{
				flag = regchar (field_ptr, rchar);
			}

			if (width >= field_ptr -> length)
			{
				if (field_ptr -> txflg & TXEXT && Glbl_Overflow_Action )
				{
					if((*Glbl_Overflow_Action) (field_ptr))
						continue;
				}

				if ((field_ptr -> txflg & TXAUTO) &&
					((_Editing_Type == INSERT) ||
				(field_ptr -> txcursor == field_ptr -> txptr)))
				{
					*((field_ptr -> txptr)++) = K_EOL;
					field_ptr -> txflg |= TXBRK;
					break;
				}
			}
			continue;
		}

		if ((field_ptr -> attribute & FAPROTECT) &&
			(chartyp[rc] != BREAK))
		{
			beep ();
			Print_Message (field_ptr -> meswin, Mess_Attribute,
				"%s%s", PROTECTED, Help_Help_String);
			continue;
		}

		switch (chartyp[rc])
		{
			case NORMAL: 
			case PUNC: 
				if (field_ptr -> txptr == field_ptr -> txcursor)
					width = fc_length (field_ptr -> y_pos,
							rchar, width);
				else
					width = _f_insert_width (field_ptr, rchar);

				if( width > field_ptr -> length )
				{
					beep ();
					Print_Message (field_ptr -> meswin, Mess_Attribute,
							"%s %s",
							FULL, Help_Help_String);
					width = _f_width (field_ptr);
					continue;
				}

				flag = (*f_chartyp[rc]) (field_ptr, rchar);

				if (width >= field_ptr -> length)
				{
					if (field_ptr -> txflg & TXEXT &&  (*Glbl_Overflow_Action) (field_ptr))
							break;

					if ((field_ptr -> txflg & TXAUTO) &&
						((_Editing_Type == INSERT) ||
					(field_ptr -> txcursor == field_ptr -> txptr)))
					{
						*((field_ptr -> txptr)++) = K_EOL;
						field_ptr -> txflg |= TXBRK;
						flag = TRUE;
					}
				}
				break;

			case BREAK: 
				flag = (*f_chartyp[rc]) (field_ptr, rchar);
				break;

			case CORRECT: 
				flag = (*f_chartyp[rc]) (field_ptr, rchar);
				width = _f_width (field_ptr);
				if (field_ptr -> txcursor > field_ptr -> txptr)
					field_ptr -> txcursor = field_ptr -> txptr;
				break;

			case DSCARD: 
				beep ();
				Print_Message (field_ptr -> meswin, Mess_Attribute, "Illegal character in the present context %s", Help_Help_String);
				flag = FALSE;
				break;
		}

		if (flag)
			break;
		else
		{
			w_xgo (field_ptr -> window, field_ptr -> x_pos, 
					field_ptr -> y_pos);

			saved = *field_ptr -> txcursor;
			*field_ptr -> txcursor = '\0';
			waxprintf (field_ptr -> window,
				field_ptr -> attribute | FAFIELD,
				"%s", field_ptr -> txbuf);
			*field_ptr -> txcursor = saved;
		}
	}
	*field_ptr -> txptr = '\0';
}

static int
_f_width (field_ptr)
register struct field_item     *field_ptr;
{
	register char  save;
	register int    width;

	save = *(field_ptr -> txptr);
	*(field_ptr -> txptr) = '\0';
	width = f_length (field_ptr -> y_pos, field_ptr -> txbuf);
	*(field_ptr -> txptr) = save;
	return (width);
}

static int
_f_insert_width (field_ptr, rchar)
register struct field_item *field_ptr;
char rchar;
{
	register char *ptr1;
	register int width;

	for (width = 0, ptr1 = field_ptr -> txbuf;
			ptr1 < field_ptr -> txcursor; ptr1++)
	{
		width = fc_length (field_ptr -> y_pos, *ptr1, width);
	}

	if (_Editing_Type == OVERLAY)
		ptr1++;

	width = fc_length (field_ptr -> y_pos, rchar, width);
	for (; ptr1 < field_ptr -> txptr; ptr1++)
	{
		width = fc_length (field_ptr -> y_pos, *ptr1, width);
	}
	return (width);
}
